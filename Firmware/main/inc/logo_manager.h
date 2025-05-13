
#ifndef __LOGO_MANAGER__
#define __LOGO_MANAGER__

#include <stdbool.h>

#define MAX_LOGO_NUM 5

struct status_logo_t {
    unsigned char status;
    unsigned char name;
};

struct status_logo_pool_t {
    unsigned char phead;
    unsigned char ptail;
    struct status_logo_t buf[MAX_LOGO_NUM];
};

extern void status_logo_pool_init(struct status_logo_pool_t * pool);
extern unsigned char status_logo_pool_empty(struct status_logo_pool_t * pool);
extern unsigned char status_logo_pool_full(struct status_logo_pool_t * pool);
extern unsigned char status_logo_input_pool(struct status_logo_pool_t * pool, unsigned char name, unsigned char status);
extern unsigned char status_logo_output_pool(struct status_logo_pool_t * pool, struct status_logo_t * message_logo);

#endif
