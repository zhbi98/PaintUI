
#include "game.h"
#include <stdbool.h>

struct snake_game_t snake_game;

void created_food()
{
    unsigned int speed;
    speed = rand() % 30; // Active area (10 < x < 300), random 1 - 30
    snake_game.food_x = (speed * 10) + 10;  

    speed = rand() % 20; // Active area (10 < y < 200), random 1 - 20
    snake_game.food_y = (speed * 10) + 10;

    while (snake_cover_food(snake_game.snake_x, snake_game.snake_y, snake_game.food_x, snake_game.food_y) == true) {
        speed = rand() % 30;
        snake_game.food_x = (speed * 10) + 10;
        speed = rand() % 20;
        snake_game.food_y = (speed * 10) + 10;
    }
}

void snake_init(unsigned char * vm)
{   
    snake_game.dir     = 1;
    snake_game.key_dir = 1;

    snake_game.snake_x[0] = 150;
    snake_game.snake_y[0] = 120; // original head

    snake_game.snake_x[1] = 150;
    snake_game.snake_y[1] = 130; // original first body
    
    snake_game.snake_x[2] = 150;
    snake_game.snake_y[2] = 140; // original second body

    snake_game.head_x = snake_game.snake_x[0]; 
    snake_game.head_y = snake_game.snake_y[0];
    
    snake_game.length = 3;
    snake_game.life   = true;
    snake_game.status = 1;

    created_food();
    refresh(vm);
}

void set_game_status(char incr)
{
    if (act_bar_get_func() != DMM_GAME)
        return; 
    snake_game.status += incr;
    if (snake_game.status > 1)
        snake_game.status = 0;

    if (snake_game.status < 0)
        snake_game.status = 1;
}

void snake_running(char dir, unsigned char * vm)
{
    unsigned char i;

    if ((snake_game.life == true) && (snake_game.status == 1)) {
        if (abs(dir) != abs(snake_game.dir)) // 如果按下的方向不是和运动的方向相同或相反
            snake_game.dir = dir; // 将蛇运动的方向改变为按下的方向
        else
            dir = snake_game.dir;    //keep going
        // info("snake_game.dir:%d", snake_game.dir);
        switch (dir) {
            case 1:
                snake_game.head_y -= 10;  //up:size of snake = 10,running unit = 10
                break;
            case -1:
                snake_game.head_y += 10;  //down
                break;
            case -2:
                snake_game.head_x -= 10;  //left
                break;
            case 2:
                snake_game.head_x += 10;  //right
                break;
        }
        
        if ((snake_game.head_x == snake_game.food_x) && (snake_game.head_y == snake_game.food_y)) {
            snake_game.length++;
            
            for (i = 1; i < snake_game.length; i++) { // 除头部以外的坐标前移
                snake_game.snake_x[snake_game.length - i] = snake_game.snake_x[snake_game.length - i - 1];
                snake_game.snake_y[snake_game.length - i] = snake_game.snake_y[snake_game.length - i - 1];
            }
            snake_game.snake_x[0] = snake_game.food_x; 
            snake_game.snake_y[0] = snake_game.food_y;  
            created_food();
        } else {
            for (i = 1; i < snake_game.length; i++) {
                snake_game.snake_x[snake_game.length - i] = snake_game.snake_x[snake_game.length - i - 1];
                snake_game.snake_y[snake_game.length - i] = snake_game.snake_y[snake_game.length - i - 1];
            }
            snake_game.snake_x[0] = snake_game.head_x;
            snake_game.snake_y[0] = snake_game.head_y;          
        }   
    }

    if ((snake_game.head_y <= 200) && (snake_game.head_y >= 10) && (snake_game.head_x <= 300) && (snake_game.head_x >= 10) && (touch_itself() == false))
        snake_game.life = true;
    else
        dead(vm);
}

void refresh(unsigned char * vm)
{
    unsigned char length;

    if (snake_game.life == true) {
        for (length = 0; length < snake_game.length; length++)
            display_bevel_rect(snake_game.snake_y[length], snake_game.snake_x[length], 10, 10, WHITE, 2, vm);
        display_bevel_rect(snake_game.food_y, snake_game.food_x, 10, 10, WHITE, 2, vm);
    }
}

unsigned char snake_cover_food(unsigned int snake_x[], unsigned int snake_y[], unsigned int food_x, unsigned int food_y)
{
    unsigned char length;

    for (length = 0; length < snake_game.length; length++) {
        if ((snake_x[length] == food_x) && (snake_y[length] == food_y))
            return true;
    }
    return false;
}

unsigned char touch_itself()
{
    unsigned char length;

    for (length = 1; length < snake_game.length; length++) {
        if ((snake_game.snake_x[length] == snake_game.head_x) && (snake_game.snake_y[length] == snake_game.head_y))     
            return true;    
    }
    return false;
}

void dead(unsigned char * vm)
{
    snake_game.length = 0;
    
    snake_game.snake_x[0] = 0;
    snake_game.snake_y[0] = 0;

    snake_game.snake_x[1] = 0;
    snake_game.snake_y[1] = 0;
    
    snake_game.snake_x[2] = 0;
    snake_game.snake_y[2] = 0;

    snake_game.head_x = snake_game.snake_x[0];
    snake_game.head_y = snake_game.snake_y[0];

    snake_game.dir  = 0;  
    snake_game.life = false;
}

void set_direction(char dir)
{
    snake_game.key_dir = dir;
}

char check_direction()
{
    return snake_game.key_dir;
}
