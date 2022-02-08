#include "Input.h"
#include "SDL/include/SDL.h"
#include "p2List.h"
#include "Scene.h"
#include "Physics.h"
#include "Textures.h"
#include "Render.h"
#include "Window.h"
#include "Audio.h"
#include "Pathfinding.h"
#include "EntityDummy.h"
#include "Animation.h"

EntityDummy::EntityDummy(b2Vec2 startPosition, int health) : Entity()
{
	spawnPosition = startPosition;
	name.Create("chicken_idle");
	Hitbox = app->physics->CreateCircle(spawnPosition.x, spawnPosition.y, 16);
	Hitbox->body->SetSleepingAllowed(false);
	this->health = health;
	Hitbox->body->SetGravityScale(0);
	Hitbox->body->GetFixtureList()->SetRestitution(0);
	Hitbox->body->SetFixedRotation(true);
	Hitbox->body->ResetMassData();
	inter_speed = 0.05;
	isEnemy = true;
}


EntityDummy::~EntityDummy()
{}

bool EntityDummy::Awake()
{
	return true;
}

bool EntityDummy::Start()
{
	sprite = app->tex->Load("Assets/textures/nuget.png");
	LifeBars = app->tex->Load("Assets/textures/UI/HealthBar DARK.png");

	canMove = true;


	tileSpeed = 48;
	tileVspeed = { tileSpeed ,tileSpeed };

	speed = 3;
	Vspeed = { speed,speed };

	newX = 0;
	newY = 0;
	oldX = 0;
	oldY = 0;

	LOG("player started");

	chicken_idle.PushBack({ 6, 311, 48, 48 });
	chicken_idle.PushBack({ 54, 311, 48, 48 });
	chicken_idle.PushBack({ 102, 311, 48, 48 });
	chicken_idle.PushBack({ 6, 359, 30, 24 });
	chicken_idle.PushBack({ 54, 359, 30, 24 });
	chicken_idle.PushBack({ 102, 359, 30, 24 });
	chicken_idle.speed = 0.5f;

	// Life
	// 
	// Grey healthbar
	// 17 133   61 8
	//  18 121  59 6

	// Red Healthbar
	// 17 164 61 8
	// 18 152 59 6

	backBar.PushBack({ 17, 133,   61, 8 });
	backBar.speed = 0.1f;
	backBar.loop = false;


	healthVariation.PushBack({ 18, 121,  59, 6 });

	currentLifeAnimation = &healthVariation;

	// 

	return true;
}

bool EntityDummy::CleanUp()
{
	LOG("Unloading player");

	return true;
}

void EntityDummy::LvlUp(int exp_used)
{
	level++;
	// Increase stats
	exp -= exp_used;
	//Increase exp needed
}

bool EntityDummy::Update(float dt)
{
	chicken_ = &chicken_idle;
	
	app->pathfinding->CreatePath(iPoint(x, y), app->entityHandler->players.getFirst()->data->GetPosition());
	
	x = (float)METERS_TO_PIXELS(Hitbox->body->GetPosition().x);
	y = (float)METERS_TO_PIXELS(Hitbox->body->GetPosition().y);

	


	mapPos = app->map->WorldToMap(METERS_TO_PIXELS(Hitbox->body->GetPosition().x), METERS_TO_PIXELS(Hitbox->body->GetPosition().y));

	gidNow = app->map->data.layers.start->data->Get(mapPos.x, mapPos.y);

	gidLeft = app->map->data.layers.start->data->Get(mapPos.x - 1, mapPos.y);
	gidRight = app->map->data.layers.start->data->Get(mapPos.x + 1, mapPos.y);
	gidUp = app->map->data.layers.start->data->Get(mapPos.x, mapPos.y - 1);
	gidDown = app->map->data.layers.start->data->Get(mapPos.x, mapPos.y + 1);

	/*LOG("gidNow %i", gidNow);
	LOG("gidUp %i", gidUp);
	LOG("gidDown %i", gidDown);
	LOG("gidLeft %i", gidLeft);
	LOG("gidRight %i", gidRight);
	LOG("------------------------");*/

	chicken_->Update();

	app->render->DrawTexture(sprite, x - 16, y - 16, NULL);

	// Life Logic

	//health;
	//currentLifeAnimation->GetCurrentFrame().w;// start

	//Helathnew;
	//newanim; // End
	//
	//steps;
	//
	//
	//
	//oldHP = health;
	//oldHPAnim= *currentLifeAnimation;
	//
	//// Apply damage
	//
	//newHP = health;
	//
	//Interpolatefunction(oldHP, newHP, oldHPAnim, int steps);
	//{
	//
	//	newHPAnim.w = newHP* oldHPAnim.w / oldHP;
	//
	//	
	//	for (int i = 0; i < steps; i++)
	//	{
	//
	//	}
	//
	//}


	//Life
	app->render->DrawTexture(LifeBars, x-30 , y-25 , &backBar.GetCurrentFrame());
	app->render->DrawTexture(LifeBars, x - 29, y - 24, &currentLifeAnimation->GetCurrentFrame());

	return true;
}

bool EntityDummy::LoadState(pugi::xml_node& data)
{
	//id = data.attribute("id").as_int();
	//b2Vec2 currentPos(data.attribute("currentPos.x").as_float(), data.attribute("currentPos.y").as_float());
	//Hitbox->body->SetTransform(currentPos, 0);


	return true;
}

bool EntityDummy::SaveState(pugi::xml_node& data) const
{
	//pugi::xml_node myself = data.append_child("EnemySnake");

	//myself.append_attribute("id").set_value(id);
	//myself.append_attribute("currentPos.x").set_value(Hitbox->body->GetPosition().x);
	//myself.append_attribute("currentPos.y").set_value(Hitbox->body->GetPosition().y);

	return true;
}

