#pragma once
#ifndef __SNAKE_ENEMIES_H__
#define __SNAKE_ENEMIES_H__

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
#include "EntityEnemies.h"
#include "EntityHandler.h"


//struct Stats
//{
//	int hp;
//	int armour;
//	int damage;
//	int speed;
//	int momevent;
//	int crit;
//	int dodge;
//	int venom;
//};


class SnakeEnemy : public EntityEnemy
{
public:
	SnakeEnemy(b2Vec2 startPosition, int health);
	virtual ~SnakeEnemy();

	bool Awake();
	bool Start();
	bool Update(float dt);
	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;
	bool CleanUp();

	void Draw() override;
	int Attack(int enemyType) override;

	

	void Interpolate(int x, int y, float speed)
	{
		newX = (float)x;
		newY = (float)y;
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

	void Attck_01(Entity* player);

	SDL_Rect a;
	SDL_Texture* pac;
	float x, y;
	int behaviour;

	float iSpeed;
	bool interpolating = false;
	float oldX;
	float oldY;
	float newX;
	float newY;
	float pos_dif_x;
	float pos_dif_y;
	float h = 0;
	float inter_speed;

	
	// Heath bar members
	SDL_Texture* LifeBars;
	SDL_Rect recHealth;
	SDL_Rect recHealthBG;


	float changingSpeed, changingHP;
	int newHP, oldHP;
	float rec_curr_h;
	int to_draw;
	SDL_Rect rec_temp_h;
	int totalHealth;

private:

	float speed;
	b2Vec2 Vspeed;
	int attackPower;

	bool out_of_steps = false;
	bool out_of_attacks = false;
	//Stats snakeStats;
};


#endif // __ENEMY_SNAKE_H__

