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
	SnakeEnemy(b2Vec2 startPosition);
	virtual ~SnakeEnemy();

	bool Awake();
	bool Start();
	bool Update(float dt);
	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;
	bool CleanUp();

	int Attack(int enemyType) override;


private:

	int attackPower;

	//Stats snakeStats;
};


#endif // __ENEMY_SNAKE_H__

