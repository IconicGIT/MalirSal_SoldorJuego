
#include "SnakeEnemy.h"



SnakeEnemy::SnakeEnemy(b2Vec2 startPosition) : EntityEnemy()
{
	setPosition(startPosition.x,startPosition.y);
}

SnakeEnemy::~SnakeEnemy() {};

bool Awake();
bool Start();
bool Update(float dt);
bool LoadState(pugi::xml_node&);
bool SaveState(pugi::xml_node&) const;
bool CleanUp();

int Attack(int enemyType) 
{

}