
#include "SnakeEnemy.h"



SnakeEnemy::SnakeEnemy(b2Vec2 startPosition) : EntityEnemy()
{
	setPosition(startPosition.x,startPosition.y);
}

SnakeEnemy::~SnakeEnemy() {}
bool SnakeEnemy::Awake()
{
	return false;
}
bool SnakeEnemy::Start()
{
	return false;
}
bool SnakeEnemy::Update(float dt)
{
	return false;
}
bool SnakeEnemy::LoadState(pugi::xml_node&)
{
	return false;
}
bool SnakeEnemy::SaveState(pugi::xml_node&) const
{
	return false;
}
bool SnakeEnemy::CleanUp()
{
	return false;
}
int SnakeEnemy::Attack(int enemyType)
{
	return 0;
}
