#pragma once
#ifndef __ENTITY_ENEMIES_H__
#define __ENTITY_ENEMIES_H__

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


class EntityEnemy : public Entity
{
public:
	EntityEnemy(b2Vec2 startPosition, int health);
	EntityEnemy();
	virtual ~EntityEnemy();

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
		newX = (float)x + 24;
		newY = (float)y + 24;
		if (!interpolating && (oldX != newX || oldY != newY))
		{
			h = 0;
			iSpeed = speed;
			if (speed > 1) iSpeed = 1;
			if (speed < 0) iSpeed = 0;
			oldX = METERS_TO_PIXELS(Hitbox->body->GetPosition().x);
			oldY = METERS_TO_PIXELS(Hitbox->body->GetPosition().y);
			interpolating = true;


		}
		else {
			h += iSpeed;

			if (1 - h < 0)
				h = 1;

			float x_ = oldX * (1 - h) + newX * h;
			float y_ = oldY * (1 - h) + newY * h;

			b2Vec2 pos = { PIXEL_TO_METERS(x_),PIXEL_TO_METERS(y_) };
			Hitbox->body->SetTransform(pos, 0);

			if (h == 1)
			{
				interpolating = false;
				h = 0;
			}

		}



	}

	/*
	Enemy Types:
	1- Snake
	
	*/

	virtual int Attack(int enmeyType) { return -1; };


private:

	float iSpeed;
	bool interpolating = false;;
	float oldX;
	float oldY;
	float newX;
	float newY;
	float h = 0;

	int behaviour;

	b2Vec2 spawnPosition;
	PhysBody* Hitbox;
	int health;
	float x, y;
	float speed;
	b2Vec2 Vspeed;

	MovementDirection direction;

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

	iPoint mapPos;



};



//class EnemySnake : public Entity
//{
//public:
//	EnemySnake(b2Vec2 startPosition, int health);
//	virtual ~EnemySnake();
//
//	// Called before render is available
//	
//	
//	int CheckDistanceToPhysBody(PhysBody* PhysPos)
//	{
//		b2Vec2 dist = PhysPos->body->GetPosition() - Hitbox->body->GetPosition();
//
//		return (abs(dist.x) + abs(dist.y));
//	}
//
//	void SnakeAttack();
//	// Called before the first frame
//	
//
//	int lastTime = 0;
//	int currentTime = 0;
//	bool snakeDirection = true;
//	int snakeAnim = 0;
//	bool snakeAgro = false;
//	int snakeAttackAnim = 0;
//	int snakeAttackTime = 0;
//
//	
//
//	void DoDamage(int damage);
//
//private:
//	p2List<PhysBody*> acidThrown;
//	SDL_Rect r_snakeIdle[6];
//	SDL_Rect r_snakeAttack[4];
//	
//	PhysBody* acidBox;
//	
//	const int maxDistanceAgroBase = 13;
//	bool lastAcidDirection = true;
//	int health;
//	int attackCooldown = 0;
//	bool acidOnMap = false;
//	
//};

#endif // __ENEMY_SNAKE_H__

