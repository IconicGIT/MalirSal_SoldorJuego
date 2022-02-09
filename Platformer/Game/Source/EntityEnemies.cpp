#include "EntityEnemies.h"
#include <stdlib.h>     
#include <time.h>      


EntityEnemy::EntityEnemy(b2Vec2 startPosition, int health)
{
	Hitbox = app->physics->CreateCircle(startPosition.x, startPosition.y, 16);
	Hitbox->body->SetSleepingAllowed(false);
	this->health = health;
	Hitbox->body->SetGravityScale(0);
	Hitbox->body->GetFixtureList()->SetRestitution(0);
	Hitbox->body->SetFixedRotation(true);
	Hitbox->body->ResetMassData();
	Hitbox->entity_ptr = this;
}

EntityEnemy::EntityEnemy()
{
	Hitbox = app->physics->CreateCircle(10, 10, 16);
	Hitbox->body->SetSleepingAllowed(false);
	this->health = health;
	Hitbox->body->SetGravityScale(0);
	Hitbox->body->GetFixtureList()->SetRestitution(0);
	Hitbox->body->SetFixedRotation(true);
	Hitbox->body->ResetMassData();
	Hitbox->entity_ptr = this;
}

EntityEnemy::~EntityEnemy()
{
}

bool EntityEnemy::Awake()
{
	return true;
}

bool EntityEnemy::Start()
{
	return true;
}

bool EntityEnemy::Update(float dt)
{
	behaviour = rand() % 50;

	if (behaviour < 10)
	{

	}
	else if (behaviour < 25)
	{

	}
	else if (behaviour < 45)
	{

	}
	return true;
}

bool EntityEnemy::LoadState(pugi::xml_node&)
{
	return true;
}

bool EntityEnemy::SaveState(pugi::xml_node&) const
{
	return true;
}

bool EntityEnemy::CleanUp()
{
	return true;
}
