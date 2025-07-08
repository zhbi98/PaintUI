/**
 * @file nt_pwd.c
 *
 */
/*********************
 *      INCLUDES
 *********************/

#include <string.h>
#include "nt_pwd.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void nt_pwd_normalized(nt_pwd_auth_t * auth);
static void nt_pwd_cache_data(nt_pwd_auth_t * auth, uint8_t pwd);
static void nt_pwd_clean_data(nt_pwd_auth_t * auth);
static uint8_t nt_pwd_auth(nt_pwd_auth_t * auth);

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * Serializes the entered password string.
 */
static void nt_pwd_normalized(nt_pwd_auth_t * auth)
{
    uint16_t len = auth->auth_len - 1;

    for (uint16_t i = 0; i < len; i++) {
        auth->in_data[i] = \
            auth->in_data[i + 1];
    }
}

/**
 * The input password string is cached for 
 * subsequent validation.
 */
static void nt_pwd_cache_data(nt_pwd_auth_t * auth, uint8_t pwd)
{
    uint16_t ofs = auth->auth_len - 1;

    auth->in_data[ofs] = pwd;
}

/**
 * Clear the cached password after verification 
 * to prevent re-use.
 */
static void nt_pwd_clean_data(nt_pwd_auth_t * auth)
{
    memset(auth->in_data, 0x00, NT_PWDLEN);
}

/**
 * Wait for input to complete, the implementation 
 * of the password string validation.
 */
static uint8_t nt_pwd_auth(nt_pwd_auth_t * auth)
{
    uint8_t i = 0;

    for (i = 0; i < auth->auth_len; i++) {
        if (auth->in_data[i] != 
            auth->auth_data[i]) {
            return false;
        }
    }
    return true;
}

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Reads a numeric value and buffers it, validating the 
 * input data after the input is complete.
 */
void nt_pwd_read(nt_pwd_auth_t * auth, uint8_t pwd)
{
    if (auth->in_len < NT_PWDLEN) {
        nt_pwd_normalized(auth);
        nt_pwd_cache_data(auth, pwd);
    }

    auth->auth_state = nt_pwd_auth(auth);

    if (auth->auth_state == true) {
        auth->auth_cb(&auth->auth_state);
        nt_pwd_clean_data(auth);
        auth->auth_state = false;
    }
}
