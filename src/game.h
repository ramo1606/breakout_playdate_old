#pragma once
#include "pd_api.h"

#include <stdbool.h>

#define EPSILON 0.0001

typedef struct Breakout Breakout;

/*
* 
*/
void create_game(PlaydateAPI * p);
int update();

/*
* Update functions
*/
//void update_logo();
//void update_start();
//void update_game();
//void update_game_over();
//void update_game_over_wait();
//void update_level_over();
//void update_level_over_wait();
//void update_winner();
//void update_winner_wait();

/*
* Draw functions
*/
//void draw_logo();
//void draw_start();
//void draw_game();
//void draw_game_over();
//void draw_game_over_wait();
//void draw_level_over();
//void draw_level_over_wait();
//void draw_winner();
//void draw_winner_wait();

//void process_input();
//void go_to_start();

LCDSprite* create_paddle(int x, int y);
LCDSprite* create_ball(int x, int y);

/*
* UTILS
*/

inline bool AreSame(float a, float b)
{
    return fabs(a - b) < EPSILON;
}