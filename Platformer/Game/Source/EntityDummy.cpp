#include "Input.h"
#include "App.h"
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

	speed = 1;
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
	// 17, 133,   61, 8
	//  18, 121,  59, 6

	// Red Healthbar
	// 17, 164, 61, 8
	// 18, 152, 59, 6


	recHealth = { 18, 152, 59, 6 };
	recHealthBG = { 17, 164, 61, 8 };

	changingSpeed = 2.f;
	totalHealth = 100;
	health = totalHealth;
	changingHP = 0;

	

	return true;
}

bool EntityDummy::CleanUp()
{
	LOG("Unloading player");

	return true;
}

void EntityDummy::Draw()
{
	app->render->DrawTexture(sprite, x - 16, y - 16, NULL);
	app->render->DrawTexture(LifeBars, METERS_TO_PIXELS(Hitbox->body->GetPosition().x) - 30, METERS_TO_PIXELS(Hitbox->body->GetPosition().y) - 25, &recHealthBG);
	app->render->DrawTexture(LifeBars, x - 29, y - 24, &rec_temp_h);
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
	
	
	x = (float)METERS_TO_PIXELS(Hitbox->body->GetPosition().x);
	y = (float)METERS_TO_PIXELS(Hitbox->body->GetPosition().y);

	behaviour = 50;//rand() % 50;
	
	if (behaviour < 50)
	{
		// Move to player
		PhysBody* goal = app->entityHandler->GetNearestChicken(Hitbox);
		if (goal != NULL)
		{
			iPoint pos(Hitbox->body->GetPosition().x, Hitbox->body->GetPosition().y);
			iPoint chicken(goal->body->GetPosition().x, goal->body->GetPosition().y);
			app->pathfinding->CreatePath(pos, chicken);
		
			for (int i = 0; i < app->pathfinding->GetLastPath()->Count(); i++) //DRAWING PATH
			{
				app->render->DrawRectangle({ app->pathfinding->GetLastPath()->At(i)->x, app->pathfinding->GetLastPath()->At(i)->y, 48, 48}, 255, 255, 255, 255);
			}

			if (app->pathfinding->CreatePath(pos, chicken) > 0) // creating path bc creates errors
			{
				
				const iPoint* going(app->pathfinding->GetLastPath()->At(1));
				if (going != nullptr)
				{
					b2Vec2 movement = { 0,0 };

					if (going->x < pos.x)
					{
						movement = { -Vspeed.x, 0 };
						Hitbox->body->SetLinearVelocity(movement);
					}
					else if (going->x > pos.x)
					{
						movement = { -Vspeed.x, 0 };
						Hitbox->body->SetLinearVelocity(movement);
					}
					else if (going->y < pos.y)
					{
						movement = { 0, -Vspeed.y };
						Hitbox->body->SetLinearVelocity(movement);
					}
					else if (going->y > pos.y)
					{
						movement = { 0, Vspeed.y };
						Hitbox->body->SetLinearVelocity(movement);
					}
					else
					{
						Hitbox->body->SetLinearVelocity(movement);
					}
				}

				

			}
		}
	}
	else if (behaviour < 40)
	{
		
	}
	else 
	{
		
	}


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

	

	// Life Logic


	//Helathnew;
	//newanim; // End
	//
	//steps;
	
	// Apply damage
	
	/*newHP = health;
	
	Interpolatefunction(oldHP, newHP, oldHPAnim, int steps);
	{
	
		newHPAnim.w = newHP * oldHPAnim.w / oldHP;
	
		
		for (int i = 0; i < steps; i++)
		{
	
		}
	
	}*/

	/*float skill_time = (float)healingCooldown;

	float skill_fill_f = (healingCooldownMax - skill_time) / healingCooldownMax * 132;
	int skill_fill_i = (int)skill_fill_f;

	SDL_Rect r = { 264, 92, skill_fill_i, 20 };

	if (app->scene->UI_player_skill_bar_fill != nullptr)
		app->scene->UI_player_skill_bar_fill->rec_sprite = r;*/

	//Life
	
	oldHP = health;

	//do damage
	if (app->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		changingHP = (float)health;
		health -= 25;
	}

	if (changingHP > (float)health)
	{
		
		changingHP -= changingSpeed;
	}
	else
	{
		changingHP = (float)health;
	}

	if (changingHP <= 0)
	{
		app->entityHandler->DestroyEnemy(Hitbox->body);
	}

	rec_curr_h = changingHP / (float)totalHealth * (float)recHealth.w;
	to_draw = (int)rec_curr_h;

	rec_temp_h = recHealth;
	rec_temp_h.w = rec_curr_h;

	

	/*LOG("hp = %i", health);
	LOG("total hp = %i", totalHealth);
	LOG("changing hp = %f", changingHP);
	LOG("draw hp = %i", to_draw);
	LOG("------------------------------");*/

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

