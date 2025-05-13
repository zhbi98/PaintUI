
#ifndef __KEY_CONTEOLLER_H__
#define __KEY_CONTEOLLER_H__

#include "key.h"
#include "display_string.h"
#include "display_controller.h"

enum dmm_function {
	DMM_VOLTAGE_V,
	DMM_SETTING,
    DMM_FUNCTION_MAX
};

struct password_auth_t {
    unsigned char password_data[16];
    unsigned char password_buf[16];

    unsigned char password_length;
    unsigned char lock_status;
};

extern struct password_auth_t param_setting_auth;
extern struct password_auth_t test_function_auth;

extern void key_event_doing();
extern void key_function_init();

extern unsigned char pwd_auth(struct password_auth_t * auth);
extern unsigned char get_lock_status(struct password_auth_t * auth);
extern void read_password(struct password_auth_t * auth, unsigned char key);

#endif
