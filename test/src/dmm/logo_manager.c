
#include "logo_manager.h"

void status_logo_pool_init(struct status_logo_pool_t * pool)
{
    memset(pool->buf, 0, sizeof(pool->buf));
    pool->phead = 0;
    pool->ptail = 0;
}

unsigned char status_logo_pool_empty(struct status_logo_pool_t * pool)
{
    if (pool->phead == pool->ptail)
        return true;
    else
        return false;
}

unsigned char status_logo_pool_full(struct status_logo_pool_t * pool)
{
    if (((pool->ptail + 1) % MAX_LOGO_NUM) == pool->phead)
        return true;
    else
        return false;
}

unsigned char status_logo_input_pool(struct status_logo_pool_t * pool, unsigned char name, unsigned char status)
{
    if (status_logo_pool_full(pool))
        return false;

    pool->buf[pool->ptail].name = name;
    pool->buf[pool->ptail].status = status;
    pool->ptail += 1;

    pool->ptail = pool->ptail % MAX_LOGO_NUM;
    return true;
}

unsigned char status_logo_output_pool(struct status_logo_pool_t * pool, struct status_logo_t * message_logo)
{
    if (status_logo_pool_empty(pool))
        return false;

    *message_logo = pool->buf[pool->phead];
    pool->phead += 1;

    pool->phead = pool->phead % MAX_LOGO_NUM;
    return true;
}
