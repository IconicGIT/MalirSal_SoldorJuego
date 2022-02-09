#ifndef __ENTITY_PLAYER_H__
#define __ENTITY_PLAYER_H__

#include "Entity.h"
#include "p2Point.h"
#include "p2List.h"
#include "App.h"
#include "Physics.h"
#include <math.h>
#include "SDL/include/SDL.h"
#include "Render.h"
#include "Animation.h"
#include "Log.h"
#include "EntityHandler.h"


struct Stats
{
	int hp;
	int armour;
	int damage;
	int speed;
	int momevent;
	int crit;
	int dodge;
};

enum TileType
{
	TILE_WIN = 1,
	TILE_DAMAGE = 2,
	TILE_SPAWN = 3,
	TILE_WALL = 4
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
	STEP_TILES
};

class EntityPlayer : public Entity
{
public:
	EntityPlayer(b2Vec2 startPosition, int health);
	virtual ~EntityPlayer();

	bool Awake();
	bool Start();
	bool Update(float dt);
	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;
	bool CleanUp();

	bool PhysBodyIsInMap(PhysBody* phys)
	{
		iPoint positionInMap(
			app->map->WorldToMap(
				METERS_TO_PIXELS(phys->body->GetPosition().x),
				METERS_TO_PIXELS(phys->body->GetPosition().y)
			)
		);

		return app->pathfinding->CheckBoundaries(positionInMap);

	}
	
	PhysBody* GetPhysBody() const
	{
		return Hitbox;
	}

	iPoint GetPosition()
	{
		return iPoint(x, y);	
	}

	void setPosition(int x, int y)
	{
		b2Vec2 v(x, y);
		Hitbox->body->SetTransform(v, 0);
	}

	void ClampPos(int mapX, int mapY)
	{
		iPoint worldPos = app->map->MapToWorld(mapX, mapY);
		float bodyX = PIXEL_TO_METERS(worldPos.x) + 23;
		float bodyY = PIXEL_TO_METERS(worldPos.y) + 23;
		b2Vec2 v = { bodyX,bodyY };
		Hitbox->body->SetTransform(v, 0);
	}

	void Interpolate(int x, int y, float speed) 
	{
		newX = (float)x ;
		newY = (float)y ;
		if (!interpolating)
		{
			h = 0;
			iSpeed = speed; 
			if (speed > 1) iSpeed = 1;
			if (speed < 0) iSpeed = 0;
			oldX = this->x;
			oldY = this->y;
			interpolating = true;

			pos_dif_x = newX - oldX;
			pos_dif_y = newY - oldY;
		}
		else {
			h += iSpeed;

			if (1 - h < 0)
				h = 1;

			
			float x_ = oldX + pos_dif_x * h;
			float y_ = oldY + pos_dif_y * h;

			b2Vec2 pos = { PIXEL_TO_METERS(x_),PIXEL_TO_METERS(y_) };
			Hitbox->body->SetTransform(pos, 0);

			if (h == 1)
			{
				interpolating = false;
				h = 0;
			}

		}
		

		
	}
	
	int CheckDistanceToPhysBody(PhysBody* PhysPos)
	{
		b2Vec2 dist = PhysPos->body->GetPosition() - Hitbox->body->GetPosition();

		return (abs(dist.x) + abs(dist.y));
	}

	void LvlUp(int exp_used);


	PlayerMovementType moveType;

private:

	float iSpeed;
	bool interpolating = false;;
	float oldX;
	float oldY;
	float newX;
	float newY;
	float pos_dif_x;
	float pos_dif_y;
	float h = 0;
	float inter_speed;

	b2Vec2 spawnPosition;
	PhysBody* Hitbox;
	int health;
	float x, y;

	float speed;
	b2Vec2 tileVspeed;

	float tileSpeed;
	b2Vec2 Vspeed;

	MovementDirection lastDirection;
	
	Stats player_stats;

	bool canMove;

	bool goUp;
	bool goDown;
	bool goLeft;
	bool goRight;
	bool AdminMode;

	int gidUp;
	int gidDown;
	int gidLeft;
	int gidRight;
	int gidNow;

	bool tileFreeUp;
	bool tileFreeDown;
	bool tileFreeLeft;
	bool tileFreeRight;

	int playerId;

	iPoint mapPos;

	int level;
	int exp;
	int exp_lvlUp;

	SDL_Texture* sprite;
	Animation idle_left;
	Animation idle_right;
	Animation* currentAnimation;
};

#endif // __ENEMY_SNAKE_H__
