#pragma once

typedef struct Paddle
{
	LCDSprite* sprite;
	int dx;
} Paddle;

//void init_paddle(PlaydateAPI* pd, Paddle* paddle, int x, int y);
//void update_paddle(Paddle* paddle);
//void paddle_update_sprite(LCDSprite* sprite);