/**
 * @file _power.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "_power.h"

/*********************
 *      DEFINES
 *********************/

#define VOLT_MIN 3500U /*mV*/
#define VOLT_MAX 4000U /*mV*/

#define KN 1.5f 

/**********************
 *      TYPEDEFS
 **********************/

nt_liocv_t liocv = {
    .idx = 0,
    .noft = 5,
    .ret = 4.5,
    .end = 0,
};

nt_lisox_t lisox = {0};

/**********************
 *  STATIC VARIABLES
 **********************/

static km_filte_t km_filte_volt = {.K_gain = 0.3, 
    .last_est = 4.5, .cur_est = 4.5};
static float km_filted_volt;

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void nt_bat_set_ori_val(float val);
static void nt_bat_move(float data_p[], 
    uint32_t len);
static void nt_bat_chrg_start();
static void nt_bat_chrg_end();
static void nt_bat_chrg_est();
static void nt_bat_chrg_refer();

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Emmerich Kalman estimates the current value based on historical 
 * values using an iterative method.
 */
float kalman_filte(km_filte_t * km, float Y_meas)
{
    km->Y = Y_meas;
    /*Updates the current estimate*/
    km->cur_est = km->last_est + km->K_gain * 
        (km->Y - km->last_est);
    /*Updates the last estimate*/
    km->last_est = km->cur_est;
    return km->cur_est;
}

/**
 * The raw open circuit voltage data of the battery 
 * is read in real time from the hardware module.
 */
void nt_bat_set_ori_val(float val)
{
    liocv.idx = LV_MIN(liocv.idx, DATA_NR - 1);
    liocv.pbuffer[liocv.idx] = val;
    liocv.idx++; 
}

/**
 * Collate data to exclude the collection of unstable data, 
 * so as not to affect the accuracy of estimates.
 */
void nt_bat_move(float data_p[], 
    uint32_t len)
{
    int16_t i = 0, j = 0;
    float fval, bval;

    float * pfv, * pbv;

    for (i = 0; i < len; i++) {
        for (j = 0; j < len - 1; 
            j++) {

            pfv = &data_p[j];
            pbv = &data_p[j + 1];
            fval = *pfv;
            bval = *pbv;

            if (fval > bval) {
                *pbv = fval;
                *pfv = bval;
            }
        }
    }
}

/**
 * Collate data to exclude the collection of unstable data, 
 * so as not to affect the accuracy of estimates.
 */
void nt_bat_ocv_est_val()
{
    float * data_p = liocv.pbuffer;

    hal_bat_data_t bat_data = {0};
    hal_bat_read_data(&bat_data);

    /*info("ori volt:%f", bat_data.volt);*/

    km_filted_volt = kalman_filte(
        &km_filte_volt, 
        bat_data.volt
    );

    if (!liocv.end) nt_bat_set_ori_val(
        km_filted_volt);

    if (liocv.idx >= liocv.noft) {
        nt_bat_move(data_p, 
            liocv.noft);
        liocv.end = true;
        liocv.idx = 0;
    }

    uint8_t valid_nr = 0;
    uint8_t vofs = 0;

    if (liocv.end) {
        valid_nr = (int32_t)(
            liocv.noft / 5);
        valid_nr = LV_MAX(valid_nr, 1);

        vofs = (int32_t)(
            (liocv.noft - 
                valid_nr) / 2);

        float rt_dyn_sum = 0.0;
        float rt_dyn_avg = 0.0;

        for (uint8_t i = 0; 
            i < valid_nr; i++)
            rt_dyn_sum += \
                data_p[vofs + i];
        
        rt_dyn_avg = (float)(
            rt_dyn_sum / valid_nr);

        float  En = 0.0;
        float  S2 = 0.0;
        float  dv = 0.0;
        double X2 = 0.0;

        for (uint8_t j = 0; 
            j < valid_nr; j++) {
            dv = data_p[vofs + j] - \
                rt_dyn_avg;
            X2 = pow(dv, 2);
            En += X2;
        }

        S2 = (float)En / (float)valid_nr;

        liocv.end = false;
        /*Data acquisition number dynamic 
        transformation*/
        liocv.noft = liocv.noft + 10;
        liocv.noft = LV_MIN(
            liocv.noft, 
            DATA_NR - 1
        );

        /*Updates valid and stable data 
        to the user*/
        if (S2 <= KN)
            liocv.ret = rt_dyn_avg;
    }
}

/**
 * The curve of battery open circuit voltage and battery 
 * capacity is fitted, and the state of 
 * charge is estimated.
 */
int16_t nt_bat_ocv_fit_soc()
{
    uint16_t volt = (uint16_t)(liocv.ret * 1000);

    volt = LV_MAX(volt, VOLT_MIN);

    uint16_t cur = volt - VOLT_MIN;
    uint16_t range = VOLT_MAX - VOLT_MIN; /*OCV-SOC curve-fitting*/
    uint32_t soc = (int32_t)(cur * 100.0 / range);

    soc = LV_MIN(soc, 100);

    return soc;
}

/**
 * The curve of battery open circuit voltage and battery 
 * capacity is fitted, and the state of 
 * charge is estimated.
 */
int16_t nt_bat_ocv_fit2_soc(float volt)
{
    if (volt < 3.385) volt = 3.385;

    float part1 = -119 * pow(volt, 2);
    float part2 =  1026.4 * volt;
    float part3 = -2110.3;

    /*OCV-SOC curve-fitting*/
    int16_t Y = (int16_t)(
        part1 + part2 + part3
    );

    Y = LV_MIN(Y, 100);

    return Y;
}

/**
 * Battery capacity data processing and accurate 
 * estimation of battery capacity.
 */
int16_t nt_bat_get_qval()
{
    int16_t _fit = 0;
    int16_t fit = 0;

    fit = nt_bat_ocv_fit2_soc(liocv.ret);
    _fit = nt_bat_ocv_fit_soc();

    lisox.soc = (int16_t)(
        _fit * 0.7 + 
        fit * 0.3
    );

    nt_bat_chrg_refer();

    return lisox.soc;
}

/**
 * Battery capacity data processing and accurate 
 * estimation of battery capacity.
 */
float nt_bat_get_volt()
{
    return liocv.ret;
}

nt_lichrg_t lichrg = {0};

/**
 * Battery capacity data processing and accurate 
 * estimation of battery capacity.
 */
void nt_bat_chrg_start()
{
    lichrg.prev_tick = 0;
    lichrg.act_tick = 0;
    lichrg.soc_prev = lisox.soc;
    lichrg.soc_chrg = 0.0;
}

/**
 * Battery capacity data processing and accurate 
 * estimation of battery capacity.
 */
void nt_bat_chrg_end()
{
    lichrg.prev_tick = 0;
    lichrg.act_tick = 0;
    lichrg.soc_prev = 0;
    lichrg.soc_chrg = 0.0;
}

/**
 * Battery capacity data processing and accurate 
 * estimation of battery capacity.
 */
void nt_bat_chrg_refer()
{
    hal_bat_data_t bat_data = {0};
    hal_bat_read_data(&bat_data);

    switch (lichrg.inited) {
    case 0:
        if (!bat_data.chrg) break;
        if (liocv.noft < 20) break;
        lichrg.inited = 1;
        break;
    case 1:
        lichrg.inited = 2;
        nt_bat_chrg_start();
        break;
    case 2:
        nt_bat_chrg_est();
        if (bat_data.chrg) break;
        lichrg.inited = 3;
        break;
    case 3:
        lichrg.inited = 0;
        nt_bat_chrg_end();
        break;
    }
}

/**
 * Battery capacity data processing and accurate 
 * estimation of battery capacity.
 */
float nt_bat_chrg_fit()
{
    float tick = STMS_TICKS(1, 500);

    uint32_t elaps = lichrg.act_tick - \
        lichrg.prev_tick;

    float es = elaps / tick;
    float eh = es / 3600.0;
    float mah = 800.0 * eh;

    float dp = (
        mah * 100.0 / 
        2200.0);

    lichrg.prev_tick = \
        lichrg.act_tick;

    return dp;
}

/**
 * Battery capacity data processing and accurate 
 * estimation of battery capacity.
 */
void nt_bat_chrg_est()
{
    float est_val = nt_bat_chrg_fit();
    int16_t _soc_chrg;

    lichrg.soc_chrg += est_val;

    _soc_chrg = (int16_t)lichrg.soc_chrg;

    lisox.soc = lichrg.soc_prev + _soc_chrg;
}

/**
 * Battery capacity data processing and accurate 
 * estimation of battery capacity.
 */
void nt_bat_chrg_act_tick()
{
    lichrg.act_tick++;
}
