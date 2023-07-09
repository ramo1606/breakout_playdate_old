#include "game.h"
#include "pd_memory_tools.h"
#include "resource_manager.h"
#include "ball.h"
#include "paddle.h"

#include <stdlib.h>
#include <math.h>

#define TEXT_WIDTH 86
#define TEXT_HEIGHT 16

#define MAX_BALLS 3

// Enums
typedef enum
{
	LOGO,
	START,
	GAME,
	GAME_OVER,
	GAME_OVER_WAIT,
	LEVEL_OVER,
	LEVEL_OVER_WAIT,
	WINNER,
	WINNER_WAIT
}EMode;

typedef enum
{
	PADDLE = 0,
	BALL = 1,
	BLOCK = 2,
} SpriteType;

struct Breakout
{
	// API
	PlaydateAPI* pd;

	//Font
	const char* fontpath;
	LCDFont* font;

	//Resources
	Resources* resources;

	//Mode
	EMode mode;

	//Effects

	// Game objects
	Paddle paddle;
	Ball ball[MAX_BALLS];

	//VFX

	//Levels
	char* current_level;
};

static Breakout game;

void create_game(PlaydateAPI* p)
{
	initializeMemoryTools(p);

	//API
	game.pd = p;

	game.resources = load_resources(game.pd);

	//Fonts
	game.fontpath = "/System/Fonts/Asheville-Sans-14-Bold.pft";
	const char* err;
	game.font = game.pd->graphics->loadFont(game.fontpath, &err);

	if (game.font == NULL)
		game.pd->system->error("%s:%i Couldn't load font %s: %s", __FILE__, __LINE__, game.fontpath, err);

	//Mode
	game.mode = LOGO;
	
	//Effects

	// Game objects
	init_paddle(&game.paddle, 200, 300);
	game.paddle = create_paddle(200, 230);

	//VFX

	//Levels
	game.current_level = "";
	//ball = create_ball();
}

void update_logo()
{
}

void update_start()
{
}

void update_game()
{
	game.pd->sprite->updateAndDrawSprites();
}

void update_game_over()
{
}

void draw_logo()
{
	int x = (400 - TEXT_WIDTH) / 2;
	int y = (240 - TEXT_HEIGHT) / 2;
	game.pd->graphics->setFont(game.font);
	game.pd->graphics->drawText("LOGO!", strlen("LOGO!"), kASCIIEncoding, x, y);
}

void draw_start()
{
	int x = (400 - TEXT_WIDTH) / 2;
	int y = (240 - TEXT_HEIGHT) / 2;
	game.pd->graphics->setFont(game.font);
	game.pd->graphics->drawText("START!", strlen("START!"), kASCIIEncoding, x, y);
}

void draw_game()
{
}

void draw_game_over()
{
	int x = (400 - TEXT_WIDTH) / 2;
	int y = (240 - TEXT_HEIGHT) / 2;
	game.pd->graphics->setFont(game.font);
	game.pd->graphics->drawText("GAME OVER!", strlen("GAME OVER!"), kASCIIEncoding, x, y);
}

void process_input()
{
	PDButtons pushed;
	game.pd->system->getButtonState(NULL, &pushed, NULL);

	switch (game.mode)
	{
	case LOGO:
		if (pushed & kButtonA)
		{
			game.mode = START;
		}
		break;
	case START:
		if (pushed & kButtonA)
		{
			game.mode = GAME;
		}
		break;
	case GAME:
		if (pushed & kButtonA)
		{
			game.mode = GAME_OVER;
		}
		break;
	case GAME_OVER:
		if (pushed & kButtonA)
		{
			game.mode = START;
		}
		break;
	case GAME_OVER_WAIT:
		break;
	case LEVEL_OVER:
		break;
	case LEVEL_OVER_WAIT:
		break;
	case WINNER:
		break;
	case WINNER_WAIT:
		break;
	default:
		break;
	}
}

int update()
{
	process_input();
	//doblink()
	//doshake()
	//updateparts()
	//update_sash()

	game.pd->graphics->clear(kColorWhite);
	switch (game.mode)
	{
		case LOGO:
			update_logo();
			draw_logo();
			break;
		case START:
			update_start();
			draw_start();
			break;
		case GAME:
			update_game();
			draw_game();
			break;
		case GAME_OVER:
			draw_game_over();
			break;
		case GAME_OVER_WAIT:
			break;
		case LEVEL_OVER:
			break;
		case LEVEL_OVER_WAIT:
			break;
		case WINNER:
			break;
		case WINNER_WAIT:
			break;
		default:
			break;
	}

	return 1;
}

void go_to_start()
{
	game.mode = START;
}

static SpriteCollisionResponseType paddle_collision_response(LCDSprite* sprite, LCDSprite* other)
{
	return kCollisionTypeOverlap;
}

void update_paddle(LCDSprite* player)
{
	PDButtons current;
	game.pd->system->getButtonState(&current, NULL, NULL);

	bool button_pressed = false;

	if (current & kButtonLeft) {
		//game.dx = -6.f;
		button_pressed = true;
	}
	else if (current & kButtonRight) {
		//game.dx = 6.f;
		button_pressed = true;
	}

	if (!button_pressed) 
	{
		//game.dx /= 1.3;
	}

	//game.pd->sprite->moveBy(player, (float)game.dx, 0.f);
	//int len;
	//SpriteCollisionInfo* cInfo = pd->sprite->moveWithCollisions(player, x + dx, y + dy, NULL, NULL, &len);
	//
	//int i;
	//for (i = 0; i < len; i++)
	//{
	//	SpriteCollisionInfo info = cInfo[i];
	//
	//	if (pd->sprite->getTag(info.other) == BALL) 
	//	{
	//		//pd->system->logToConsole("Score: %d", score);
	//	}
	//}
	//
	//pd->system->realloc(cInfo, 0); // caller is responsible for freeing memory of array returned by moveWithCollisions()
}

LCDSprite* create_paddle(int x, int y)
{
	LCDSprite* paddle = game.pd->sprite->newSprite();

	game.pd->sprite->setUpdateFunction(paddle, update_paddle);

	LCDBitmap* paddleImage = get_image(game.resources, "paddle");
	int w, h;
	game.pd->graphics->getBitmapData(paddleImage, &w, &h, NULL, NULL, NULL);

	game.pd->sprite->setImage(paddle, paddleImage, kBitmapUnflipped);

	PDRect cr = PDRectMake(0, 0, (float)w, (float)h);
	game.pd->sprite->setCollideRect(paddle, cr);
	game.pd->sprite->setCollisionResponseFunction(paddle, paddle_collision_response);

	game.pd->sprite->moveTo(paddle, (float)x, (float)y);

	game.pd->sprite->setZIndex(paddle, 1000);
	game.pd->sprite->addSprite(paddle);

	game.pd->sprite->setTag(paddle, PADDLE);

	return paddle;
}

LCDSprite* create_ball(int x, int y)
{
	return NULL;
}