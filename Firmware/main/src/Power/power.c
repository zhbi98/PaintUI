/**
 * @file power.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "bsp.h"
#include "power.h"
#include "log.h"

/*********************
 *      DEFINES
 *********************/

#define VOLT_MIN 2800U /*mV*/
#define VOLT_MAX 4200U /*mV*/

#define DIV 4096U /*12Bit*/
#define VREF 280U /*2.8V, 2800mV, Magnify 100x*/
#define RP 40U /*R(Total):R(1)=4.0(M):1(M), Magnify 10x*/

#define KN 1.5f 

/**********************
 *      TYPEDEFS
 **********************/

nt_liocv_t liocv = {
  .idx = 0,
  .noft = 5,
  .ret = DIV,
  .end = 0,
};

nt_lisox_t lisox = {0};

/**********************
 *  STATIC VARIABLES
 **********************/

static km_filte_t km_filte_volt = {.K_gain = 0.3, 
  .last_est = VOLT_MAX, .cur_est = VOLT_MAX};
static int16_t km_filted_volt;

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void nt_bat_set_ori_val(int16_t val);
static void nt_bat_move(int16_t data_p[], 
  uint32_t len);

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Emmerich Kalman estimates the current value based on historical 
 * values using an iterative method.
 */
static float kalman_filte(km_filte_t * km, float Y_meas)
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
static void nt_bat_set_ori_val(int16_t val)
{
  liocv.idx = MAT_MIN(liocv.idx, DATA_NR - 1);
  liocv.pbuffer[liocv.idx] = val;
  liocv.idx++;
}

/**
 * Collate data to exclude the collection of unstable data, 
 * so as not to affect the accuracy of estimates.
 */
static void nt_bat_move(int16_t data_p[], 
  uint32_t len)
{
  int16_t i = 0, j = 0;
  int16_t fval, bval;

  int16_t * pfv, * pbv;

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
  int16_t * data_p = liocv.pbuffer;

  km_filted_volt = kalman_filte(
    &km_filte_volt, 
    get_dev_adc()
  );

  if (!liocv.end) nt_bat_set_ori_val(km_filted_volt);

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
    valid_nr = MAT_MAX(valid_nr, 1);

    vofs = (int32_t)(
      (liocv.noft - 
        valid_nr) / 2);

    int32_t rt_dyn_sum = 0;
    int32_t rt_dyn_avg = 0;

    for (uint8_t i = 0; 
      i < valid_nr; i++)
      rt_dyn_sum += \
        data_p[vofs + i];
    
    rt_dyn_avg = (int32_t)(
      rt_dyn_sum / valid_nr);

    int32_t En = 0;
    float S2 = 0.0f;
    int32_t dv = 0;
    double X2 = 0.0f;

    for (uint8_t j = 0; 
      j < valid_nr; j++) {
      dv = data_p[vofs + j] - \
        rt_dyn_avg;
      X2 = (int32_t)pow(dv, 2);
      En += X2;
    }

    S2 = (float)En / (float)valid_nr;

    liocv.end = false;
    /*Data acquisition number dynamic 
    transformation*/
    liocv.noft = liocv.noft + 10;
    liocv.noft = MAT_MIN(
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
int32_t nt_bat_ocv_fit_soc()
{
  uint32_t volt = 0;
  uint32_t soc = 0;

  /*x = Ref-Volt * (Adc-Val / Adc-Max-Val) / (1 / RP)*/
  volt = (int32_t)(VREF * liocv.ret * RP / DIV);
  volt = MAT_MAX(volt, VOLT_MIN);

  soc = (int32_t)((volt - VOLT_MIN) * 100.0f / 
    (VOLT_MAX - VOLT_MIN)); /*OCV-SOC curve-fitting*/
  soc = MAT_MIN(soc, 100);

  return soc;
}

/**
 * The curve of battery open circuit voltage and battery 
 * capacity is fitted, and the state of 
 * charge is estimated.
 */
int16_t nt_bat_ocv_fit2_soc(float volt)
{
  if (volt < 3.385f) volt = 3.385f;

  float B1 = -119.0f * pow(volt, 2);
  float B2 =  1026.4f * volt;
  float B3 = -2110.3f;

  /*OCV-SOC curve-fitting*/
  int16_t Y = (int16_t)(
    B1 + B2 + B3);

  Y = MAT_MIN(Y, 100);
  Y = MAT_MAX(Y, 10);

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

  int32_t mV = (int32_t)(VREF * liocv.ret * RP / DIV);

  fit = nt_bat_ocv_fit2_soc(mV / 1000.0f);
  _fit = nt_bat_ocv_fit_soc();

  lisox.soc = _fit;

  lisox.soc = (int16_t)(
    _fit * 0.7f + fit * 0.3f);

  return lisox.soc;
}
