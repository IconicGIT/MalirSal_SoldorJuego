#ifndef __ENTITY_DUMMY_H__
#define __ENTITY_DUMMY_H__

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



class EntityDummy : public Entity
{
public:
	EntityDummy(b2Vec2 startPosition, int health);
	virtual ~EntityDummy();

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
		newX = (float)x ;
		newY = (float)y ;
		if (!interpolating && (oldX != newX || oldY != newY) )
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
		
	void LvlUp(int exp_used);

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

	//MovementDirection direction;

	bool canMove;

	bool goUp;
	bool goDown;
	bool goLeft;
	bool goRight;


	int gidUp;
	int gidDown;
	int gidLeft;
	int gidRight;
	int gidNow;


	iPoint mapPos;

	int level;
	int exp;
	int exp_lvlUp;

	SDL_Texture* sprite;
	Animation chicken_idle;
	Animation* chicken_;
};

#endif // __ENEMY_SNAKE_H__
