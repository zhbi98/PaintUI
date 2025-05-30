
#include "key_controller.h"

void key_event_doing()
{
    static unsigned char release = true;
    unsigned char event = read_key_event();

    if ((_Area[DMM_F1_BTN].valid == true) && 
        (F1_KEY_STATUS() == 1)
    ){
        actbar_btn_pressed(F1_KEY_EVT);
        release = true;
    }
    if ((_Area[DMM_F2_BTN].valid == true) && 
        (F2_KEY_STATUS() == 0)
    ) {
        actbar_btn_pressed(F2_KEY_EVT);
        release = true;
    }
    if ((_Area[DMM_F3_BTN].valid == true) && 
        (F3_KEY_STATUS() == 0)
    ){
        actbar_btn_pressed(F3_KEY_EVT);
        release = true;
    }
    if ((_Area[DMM_F4_BTN].valid == true) && 
        (F4_KEY_STATUS() == 0)
    ){
        actbar_btn_pressed(F4_KEY_EVT);
        release = true;
    }

    if (
        (F1_KEY_STATUS() == 0) && 
        (F2_KEY_STATUS() == 1) && 
        (F3_KEY_STATUS() == 1) && 
        (F4_KEY_STATUS() == 1)
    ) {
        if (release == true) {
            actbar_btn_pressed(RELEASE);
            release = false;
        }
    }

    if (event != RELEASE) {
        read_password(&param_setting_auth, event);
        if (get_lock_status(&param_setting_auth) == true) {
            if (act_bar_get_func(&_dmm_actbar) == DMM_VOLTAGE_V) {
							  load_activity(NT_ACT_CTL);
                dev_topbar_cont_flush_enable();
                dmm_zone_cont_flush_enable();
                dmm_ret_cont_flush_enable();
                dmm_bcht_cont_flush_enable();
            } else {
                act_bar_set_func(&_dmm_actbar, DMM_VOLTAGE_V);
                dev_topbar_cont_flush_enable();
                dmm_zone_cont_flush_enable();
                dmm_ret_cont_flush_enable();
                dmm_bcht_cont_flush_enable();
            }
        }
    }

    switch (event) {
        case F1_KEY_EVT:
            if (_Area[DMM_ACTBAR_CONT].valid) {
                if (_Area[DMM_F1_BTN].valid) {
                    dmm_actbar_cont_flush_enable();

                    // key released to display the effect
                    actbar_btn_pressed(RELEASE);

                    act_bar_set_pressed(&_dmm_actbar, F1_KEY_EVT);
                    dmm_function_key_event(F1_KEY_EVT);
                }
            } else {
                dmm_function_key_event_enable(F1_KEY_EVT);
            }
            break;

        case F2_KEY_EVT:
            if (_Area[DMM_ACTBAR_CONT].valid) {
                if (_Area[DMM_F2_BTN].valid) {
                    dmm_actbar_cont_flush_enable();
                    
                    // key released to display the effect
                    actbar_btn_pressed(RELEASE);
 
                    act_bar_set_pressed(&_dmm_actbar, F2_KEY_EVT);
                    dmm_function_key_event(F2_KEY_EVT);
                }
            } else {
                dmm_function_key_event_enable(F2_KEY_EVT);
            }
            break;

        case F3_KEY_EVT:
            if (_Area[DMM_ACTBAR_CONT].valid) {
                if (_Area[DMM_F3_BTN].valid) {
                    dmm_actbar_cont_flush_enable();
                    
                    // key released to display the effect
                    actbar_btn_pressed(RELEASE);

                    act_bar_set_pressed(&_dmm_actbar, F3_KEY_EVT);
                    dmm_function_key_event(F3_KEY_EVT);
                }
            } else {
                dmm_function_key_event_enable(F3_KEY_EVT);
            }
            break;

        case F4_KEY_EVT:
            if (_Area[DMM_ACTBAR_CONT].valid) {
                if (_Area[DMM_F4_BTN].valid) {
                    dmm_actbar_cont_flush_enable();

                    // key released to display the effect
                    actbar_btn_pressed(RELEASE);

                    act_bar_set_pressed(&_dmm_actbar, F4_KEY_EVT);
                    dmm_function_key_event(F4_KEY_EVT);
                }
            } else {
                dmm_function_key_event_enable(F4_KEY_EVT);
            }
            break;

        case PREV_KEY_EVT:
            if (_Area[DMM_ACTBAR_CONT].valid) {
                if (_Area[DMM_F4_BTN].valid) {
                    dmm_actbar_cont_flush_enable();

                    // key released to display the effect
                    actbar_btn_pressed(RELEASE);

                    act_bar_set_pressed(&_dmm_actbar, PREV_KEY_EVT);
                    dmm_function_key_event(PREV_KEY_EVT);
                }
            } else {
                dmm_function_key_event_enable(PREV_KEY_EVT);
            }
            break;

        case NEXT_KEY_EVT:
            if (_Area[DMM_ACTBAR_CONT].valid) {
                if (_Area[DMM_F4_BTN].valid) {
                    dmm_actbar_cont_flush_enable();

                    // key released to display the effect
                    actbar_btn_pressed(RELEASE);

                    act_bar_set_pressed(&_dmm_actbar, NEXT_KEY_EVT);
                    dmm_function_key_event(NEXT_KEY_EVT);
                }
            } else {
                dmm_function_key_event_enable(NEXT_KEY_EVT);
            }
            break;
    }
}

void key_function_init()
{
    act_bar_set_func(&_dmm_actbar, DMM_VOLTAGE_V);
}

struct password_auth_t param_setting_auth = {
    .password_data   = {F1_KEY_EVT, F2_KEY_EVT, F2_KEY_EVT, F1_KEY_EVT, F1_KEY_EVT, F1_KEY_EVT, F2_KEY_EVT, F2_KEY_EVT},
    .password_buf    = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff},
    .password_length = 8,
    .lock_status     = false,
};

struct password_auth_t test_function_auth = {
    .password_data   = {F1_KEY_EVT, F2_KEY_EVT, F2_KEY_EVT, F1_KEY_EVT},
    .password_buf    = {0xff, 0xff, 0xff, 0xff},
    .password_length = 4,
    .lock_status     = false,
};

unsigned char pwd_auth(struct password_auth_t * auth)
{
    for (unsigned char i = 0; i < auth->password_length; i++)
        if (auth->password_buf[i] != auth->password_data[i])
            return false;
    return true;
}

unsigned char get_lock_status(struct password_auth_t * auth)
{
    return auth->lock_status;
}

void read_password(struct password_auth_t * auth, unsigned char key)
{
    auth->lock_status = false;

    if (auth->lock_status == false) {
        for (unsigned char bits = 0; bits < auth->password_length - 1; bits++)
            auth->password_buf[bits] = auth->password_buf[bits + 1];
        auth->password_buf[auth->password_length - 1] = key;
    }
    // info("w0:%c", auth->password_buf[0]);
    // info("w1:%c", auth->password_buf[1]);
    // info("w2:%c", auth->password_buf[2]);
    // info("w3:%c", auth->password_buf[3]);

    if (pwd_auth(auth) == false) {
        auth->lock_status = false;
        return;
    }

    // password auth success
    memset(auth->password_buf, 0xff, auth->password_length);
    // info("memset");
    auth->lock_status = true;
}

void unlock_doing(struct password_auth_t * auth)
{
    static unsigned char i = 0;

    if (get_lock_status(&test_function_auth)) {
        // info("Unlock success");
    }
}
