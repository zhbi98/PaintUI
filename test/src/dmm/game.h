
#ifndef __GAME_H__
#define __GAME_H__

#include <stdio.h>

struct snake_game_t {	
    char key_dir;
    char dir;

    unsigned int food_x;
	unsigned int food_y;

	unsigned int snake_x[300];
	unsigned int snake_y[300];	

    unsigned int head_x;			
	unsigned int head_y;

	unsigned int length;
	unsigned char life;
	unsigned char status;
};

extern struct snake_game_t snake_game;

extern void created_food();
extern void snake_init(unsigned char * vm);
extern void set_game_status(char incr);
extern void snake_running(char dir, unsigned char * vm);
extern void refresh(unsigned char * vm);
extern unsigned char snake_cover_food(unsigned int snake_x[], unsigned int snake_y[], unsigned int food_x, unsigned int food_y);
extern unsigned char touch_itself();
extern void dead(unsigned char * vm);
extern void set_direction(char dir);
extern char check_direction();

#endif
