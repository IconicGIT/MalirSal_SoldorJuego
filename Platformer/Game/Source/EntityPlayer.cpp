#include "Input.h"
#include "SDL/include/SDL.h"
#include "p2List.h"
#include "Scene.h"
#include "Physics.h"
#include "Textures.h"
#include "Render.h"
#include "Window.h"
#include "Audio.h";
#include "EntityPlayer.h"
#include "Animation.h"

EntityPlayer::EntityPlayer(b2Vec2 startPosition, int health) : Entity()
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
}


EntityPlayer::~EntityPlayer()
{}

bool EntityPlayer::Awake()
{
	return true;
}

bool EntityPlayer::Start()
{
	sprite = app->tex->Load("Assets/textures/chickens/chicken_idle.png");

	moveType = STEP_FREE;
	AdminMode = false;
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

	idle_left.PushBack({ 5, 4, 63, 64 });
	idle_left.PushBack({ 71, 4, 63, 64 });
	idle_left.PushBack({ 132, 4, 63, 64 });
	idle_left.PushBack({ 191, 4, 63, 64 });
	idle_left.PushBack({ 5, 91, 63, 64 });
	idle_left.PushBack({ 71, 91, 63, 64 });
	idle_left.PushBack({ 132, 91, 63, 64 });
	idle_left.PushBack({ 191, 91, 63, 64 });
	idle_left.speed = 0.1f;


	idle_right.PushBack({ 266, 4, 63, 64 });
	idle_right.PushBack({ 325, 4, 63, 64 });
	idle_right.PushBack({ 386, 4, 63, 64 });
	idle_right.PushBack({ 452, 4, 63, 64 });
	idle_right.PushBack({ 266, 91, 63, 64 });
	idle_right.PushBack({ 325, 91, 63, 64 });
	idle_right.PushBack({ 386, 91, 63, 64 });
	idle_right.PushBack({ 452, 91, 63, 64 });
	idle_right.speed = 0.1f;

	return true;
}
bool EntityPlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

void EntityPlayer::LvlUp(int exp_used)
{
	level++;
	// Increase stats
	exp -= exp_used;
	//Increase exp needed
}

bool EntityPlayer::Update(float dt)
{
	currentAnimation = &idle_left;
	if (goLeft = (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN))
	{
		moveType = STEP_FREE;

	}
	if (goLeft = (app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN))
	{
		moveType = STEP_TILES;
		
		//while ((int)x % 48 - 28  != 0) x--;
		//while ((int)y % 48 - 28 != 0) y++;

		//b2Vec2 pos = { x, y };

		//Hitbox->body->SetTransform(pos, 0);
	}
	switch (moveType)
	{
	case STEP_FREE:
	{
		goLeft = (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT);
		goRight = (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT);

		goUp = (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT);
		goDown = (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT);

		b2Vec2 movement = { (goRight - goLeft) * Vspeed.x, (goDown - goUp) * Vspeed.y };
		Hitbox->body->SetLinearVelocity(movement);
	}
		break;
	case STEP_TILES:
	{
		goLeft = (app->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN);
		goRight = (app->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN);

		goUp = (app->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN);
		goDown = (app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN);

		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{
			
		}
		
		if (goRight) Interpolate(x + 48, y, inter_speed);
		else if (goLeft) Interpolate(x - 48, y, inter_speed);
		else if (goUp) Interpolate(x, y - 48, inter_speed);
		else if (goDown) Interpolate(x, y + 48, inter_speed);

		if (interpolating)
		{
			Interpolate(newX, newY, 0.01f);
		}
		/*b2Vec2 movement = { (float)METERS_TO_PIXELS((goRight - goLeft)), (float)METERS_TO_PIXELS((goDown - goUp))};
		Hitbox->body->SetLinearVelocity(movement);*/

		/*
	if (app->input->GetKey(SDL_SCANCODE_SPACE))
	{
		Interpolate(8 * 48, 28 * 48, 0.01f);
	}

	if (canMove)
	{
		if (app->input->GetKey(SDL_SCANCODE_W))
		{
			direction = MOV_UP;
		}
		else if (app->input->GetKey(SDL_SCANCODE_A))
		{
			direction = MOV_LEFT;
		}
		else if (app->input->GetKey(SDL_SCANCODE_S))
		{
			direction = MOV_DOWN;
		}
		else if (app->input->GetKey(SDL_SCANCODE_D))
		{
			direction = MOV_RIGHT;
		}
	}


	b2Vec2 movement = { 0,0 };
	switch (direction)
	{
	case MOV_NULL:
		movement = { 0,0 };
		break;
	case MOV_UP:
	{
		if (gidUp != TILE_WALL)
		{
			canMove = false;
			movement = { 0,-Vspeed.y };
		}
		else
		{
			Hitbox->body->SetTransform({ x,y - 0.1f }, 0);


			canMove = true;
			direction = MOV_NULL;
		}

	}
		break;
	case MOV_DOWN:
	{

		if (gidDown != TILE_WALL)
		{
			canMove = false;
			movement = { 0,Vspeed.y };
		}
		else
		{
			Hitbox->body->SetTransform({ x,y + 0.1f }, 0);
			canMove = true;
			direction = MOV_NULL;
		}
	}
		break;
	case MOV_LEFT:
	{
		if (gidLeft != TILE_WALL)
		{
			canMove = false;
			movement = { -Vspeed.x,0 };

		}
		else
		{
			Hitbox->body->SetTransform({ x - 0.1f,y }, 0);

			canMove = true;
			direction = MOV_NULL;
		}
	}
		break;
	case MOV_RIGHT:
	{

		if (gidRight != TILE_WALL)
		{
			canMove = false;
			movement = { Vspeed.x,0 };

		}
		else
		{
			Hitbox->body->SetTransform({ x + 0.1f,y }, 0);

			canMove = true;
			direction = MOV_NULL;
		}
	}
		break;
	default:
		break;
	}

	Hitbox->body->SetLinearVelocity(movement);
	LOG("Pos x %f", Hitbox->body->GetPosition().x);
	LOG("Pos  %f", Hitbox->body->GetPosition().y);*/

	}
		break;
	default:
		break;
	}

	

	x = (float)METERS_TO_PIXELS(Hitbox->body->GetPosition().x);
	y = (float)METERS_TO_PIXELS(Hitbox->body->GetPosition().y);

	

	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
	{
		AdminMode = !AdminMode;
	}

	if (!AdminMode)
	{

		if (Hitbox ->body->GetFixtureList()->IsSensor())
		{
			Hitbox ->body->GetFixtureList()->SetSensor(false);
		}
	}
	else
	{

		if (!Hitbox ->body->GetFixtureList()->IsSensor())
		{
			Hitbox ->body->GetFixtureList()->SetSensor(true);
		}
		
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
	if (goUp)
	{
		//lastDirection = MOV_UP;
	}
	else if (goDown)
	{
		//lastDirection = MOV_DOWN;
	}
	else if (goLeft)
	{
		lastDirection = MOV_LEFT;
	}
	else if (goRight)
	{
		lastDirection = MOV_RIGHT;
	}
	else
	{
		if (lastDirection == MOV_RIGHT)
		{
			currentAnimation = &idle_right;
		}
		else
		{
			currentAnimation = &idle_left;
		}
	}

	currentAnimation->Update();
	app->render->DrawTexture(sprite, x - 32, y - 32, &currentAnimation->GetCurrentFrame());

	return true;
}

bool EntityPlayer::LoadState(pugi::xml_node& data)
{
	//id = data.attribute("id").as_int();
	//b2Vec2 currentPos(data.attribute("currentPos.x").as_float(), data.attribute("currentPos.y").as_float());
	//Hitbox->body->SetTransform(currentPos, 0);


	return true;
}


bool EntityPlayer::SaveState(pugi::xml_node& data) const
{
	//pugi::xml_node myself = data.append_child("EnemySnake");

	//myself.append_attribute("id").set_value(id);
	//myself.append_attribute("currentPos.x").set_value(Hitbox->body->GetPosition().x);
	//myself.append_attribute("currentPos.y").set_value(Hitbox->body->GetPosition().y);

	return true;
}

