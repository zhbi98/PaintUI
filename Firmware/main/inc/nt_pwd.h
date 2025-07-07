/**
 * @file nt_pwd.h
 *
 */

#ifndef __NT_PWD_H__
#define __NT_PWD_H__

/*********************
 *      INCLUDES
 *********************/

#include <string.h>
#include <stdbool.h>
#include <stdint.h>

/*********************
 *      DEFINES
 *********************/

#define NT_PWDLEN 16U

/**********************
 *      TYPEDEFS
 **********************/

typedef void (*nt_pwd_hande_cb_t)(void *);

/*Construct a password type*/
typedef struct {
    const uint8_t auth_data[NT_PWDLEN]; /**< The preset password content*/
    const uint8_t auth_len;             /**< The preset password content length*/
    const nt_pwd_hande_cb_t auth_cb;    /**< Auth success excuete callback*/
    uint8_t auth_state;                 /**< Auth state success or fail*/
    uint8_t in_data[NT_PWDLEN];         /**< Cache inputting passwords*/
    uint8_t in_len;                     /**< Inputting word length*/
} nt_pwd_auth_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Define corresponding validation instances for different functions.
 * nt_pwd_auth_t auth1 = {0};
 * nt_pwd_auth_t auth2 = {0};
 * Direct the input to the appropriate validation instance
 * nt_pwd_read(&auth1, button_num);
 * nt_pwd_read(&auth2, button_num);
 */
void nt_pwd_read(nt_pwd_auth_t * auth, uint8_t pwd);

#endif /*__NT_PWD_H__*/
