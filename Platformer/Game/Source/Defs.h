#ifndef __DEFS_H__
#define __DEFS_H__

#include <stdio.h>

//  NULL just in case ----------------------

#ifdef NULL
#undef NULL
#endif
#define NULL  0

// Deletes a buffer
#define RELEASE( x ) \
	{						\
	if( x != NULL )		\
		{					  \
	  delete x;			\
	  x = NULL;			  \
		}					  \
	}

// Deletes an array of buffers
#define RELEASE_ARRAY( x ) \
	{							  \
	if( x != NULL )			  \
		{							\
	  delete[] x;				\
	  x = NULL;					\
		}							\
							  \
	}

#define IN_RANGE( value, min, max ) ( ((value) >= (min) && (value) <= (max)) ? 1 : 0 )
#define MIN( a, b ) ( ((a) < (b)) ? (a) : (b) )
#define MAX( a, b ) ( ((a) > (b)) ? (a) : (b) )
#define TO_BOOL( a )  ( (a != 0) ? true : false )

typedef unsigned int uint;
typedef unsigned char uchar;

template <class VALUE_TYPE> void SWAP(VALUE_TYPE& a, VALUE_TYPE& b)
{
	VALUE_TYPE tmp = a;
	a = b;
	b = tmp;
}

// Standard string size
#define SHORT_STR	 32
#define MID_STR	  255
#define HUGE_STR	8192

// Joins a path and file
inline const char* const PATH(const char* folder, const char* file)
{
	static char path[MID_STR];
	sprintf_s(path, MID_STR, "%s/%s", folder, file);
	return path;
}

enum Condition
{
	COND_IDLE = 0,
	COND_SCAR,
	COND_POISON,
};
struct Stats
{
	int hp;
	float armour;
	int damage;
	int speed;
	int movement;
	int crit;
	int dodge;
	int exp_given;
};
enum TileType
{
	TILE_WIN = 1,
	TILE_DAMAGE = 2,
	TILE_SPAWN = 3,
	TILE_WALL = 4
};

enum Level_choosing
{
	LEVEL_MENU = 0,
	LEVEL_01,
	LEVEL_02,
	LEVEL_03
};

enum MovementDirection
{
	MOV_NULL = 0,
	MOV_UP,
	MOV_DOWN,
	MOV_LEFT,
	MOV_RIGHT
};

enum PlayerMovementType
{
	STEP_FREE = 0,
	STEP_TILES,
	FOCUSING
};

enum EntityState
{
	STATE_TURN = 0,
	STATE_WAIT,
	STATE_DYING,
	STATE_FREE
};
#endif