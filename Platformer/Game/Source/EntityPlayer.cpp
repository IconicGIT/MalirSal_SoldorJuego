#include "Input.h"
#include "SDL/include/SDL.h"
#include "p2List.h"
#include "Scene.h"
#include "Physics.h"
#include "Textures.h"
#include "Render.h"
#include "Window.h"
#include "Audio.h"
#include "EntityPlayer.h"
#include "Animation.h"
#include "Pathfinding.h"

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
	Hitbox->entity_ptr = this;
	inter_speed = 0.05;

	entity_stats.hp = 10;
	totalHealth = 10;
	entity_stats.armour = 1;
	entity_stats.damage = 4;
	entity_stats.momevent = 5;
	entity_stats.speed = 6;
}



EntityPlayer::~EntityPlayer()
{}

bool EntityPlayer::Awake()
{
	return true;
}

bool EntityPlayer::Start()
{
	sprite = app->tex->Load("Assets/textures/chickens/chickens_spritesheet.png");
	LifeBars = app->tex->Load("Assets/textures/UI/HealthBar DARK.png");

	recHealth = { 18, 152, 59, 6 };
	recHealthBG = { 17, 164, 61, 8 };

	moveType = STEP_TILES;
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

	//23
	idle.PushBack({ 0 , 0, 64, 64});
	idle.PushBack({ 64 * 1, 0, 64, 64 }) ;
	idle.PushBack({ 64 * 2, 0, 64, 64 }) ;
	idle.PushBack({ 64 * 3, 0, 64, 64 }) ;
	idle.PushBack({ 64 * 4, 0, 64, 64 }) ;
	idle.PushBack({ 64 * 5, 0, 64, 64 }) ;
	idle.PushBack({ 64 * 6, 0, 64, 64 }) ;
	idle.PushBack({ 64 * 7, 0, 64, 64 }) ;
	idle.PushBack({ 64 * 8, 0, 64, 64 }) ;
	idle.PushBack({ 64 * 9,  0, 64, 64 }) ;
	idle.PushBack({ 64 * 10, 0, 64, 64 });
	idle.PushBack({ 64 * 11, 0, 64, 64 });
	idle.PushBack({ 64 * 12, 0, 64, 64 });
	idle.PushBack({ 64 * 13, 0, 64, 64 });
	idle.PushBack({ 64 * 14, 0, 64, 64 });
	idle.PushBack({ 64 * 15, 0, 64, 64 });
	idle.PushBack({ 64 * 16, 0, 64, 64 });
	idle.PushBack({ 64 * 17, 0, 64, 64 });
	idle.PushBack({ 64 * 18, 0, 64, 64 });
	idle.PushBack({ 64 * 19, 0, 64, 64 });
	idle.PushBack({ 64 * 20, 0, 64, 64 });
	idle.PushBack({ 64 * 21, 0, 64, 64 });
	idle.PushBack({ 64 * 22, 0, 64, 64 });

	idle.speed = 0.18f;

	jump.PushBack({ 0 , 64 * 1, 64, 64 });
	jump.PushBack({ 64 * 1, 64 * 1, 64, 64 });
	jump.PushBack({ 64 * 2, 64 * 1, 64, 64 });
	jump.PushBack({ 64 * 3, 64 * 1, 64, 64 });
	jump.PushBack({ 64 * 4, 64 * 1, 64, 64 });
	jump.PushBack({ 64 * 5, 64 * 1, 64, 64 });
	jump.PushBack({ 64 * 6, 64 * 1, 64, 64 });
	jump.PushBack({ 64 * 7, 64 * 1, 64, 64 });
	jump.PushBack({ 64 * 8, 64 * 1, 64, 64 });
	jump.PushBack({ 64 * 9,  64 * 1, 64, 64 });
	jump.PushBack({ 64 * 10, 64 * 1, 64, 64 });
	jump.PushBack({ 64 * 11, 64 * 1, 64, 64 });
	jump.PushBack({ 64 * 12, 64 * 1, 64, 64 });
	jump.PushBack({ 64 * 13, 64 * 1, 64, 64 });
	jump.PushBack({ 64 * 14, 64 * 1, 64, 64 });
	jump.PushBack({ 64 * 15, 64 * 1, 64, 64 });
	jump.PushBack({ 64 * 16, 64 * 1, 64, 64 });
	jump.PushBack({ 64 * 17, 64 * 1, 64, 64 });
	jump.PushBack({ 64 * 18, 64 * 1, 64, 64 });
	jump.PushBack({ 64 * 19, 64 * 1, 64, 64 });
	jump.PushBack({ 64 * 20, 64 * 1, 64, 64 });
	jump.PushBack({ 64 * 21, 64 * 1, 64, 64 });
	jump.PushBack({ 64 * 22, 64 * 1, 64, 64 });

	jump.speed = 0.1f;


	currentAnimation = &idle;
	changingSpeed = 0.1f;
	// La changing speed tiene que ser siempre inferior al daño que se le aplica a la entidad

	return true;
}
bool EntityPlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

void EntityPlayer::Draw()
{

	currentAnimation->Update();
	if (lastDirection == MOV_LEFT || lastHorizontalAxis == MOV_LEFT)
	{
		app->render->DrawTexture(sprite, x - 32, y - 32, &currentAnimation->GetCurrentFrame());
	}
	if (lastDirection == MOV_RIGHT || lastHorizontalAxis == MOV_RIGHT)
	{
		app->render->DrawTexture(sprite, x - 32, y - 32, &currentAnimation->GetCurrentFrame(), SDL_FLIP_HORIZONTAL);
	}

	app->render->DrawTexture(LifeBars, METERS_TO_PIXELS(Hitbox->body->GetPosition().x) - 30, METERS_TO_PIXELS(Hitbox->body->GetPosition().y) - 25, &recHealthBG);
	app->render->DrawTexture(LifeBars, x - 29, y - 24, &rec_temp_h);
}

PhysBody* EntityPlayer::checkCloseEnemies()
{
	PhysBody* enemy = app->entityHandler->GetNearestEnemy(Hitbox);
	return enemy;
}

void EntityPlayer::LvlUp(int exp_used)
{
	level++;
	// Increase stats
	exp -= exp_used;
	//Increase exp needed
}

void EntityPlayer::Attack_01(Entity* enemy)
{
	enemy->entity_stats.hp -= this->entity_stats.damage * enemy->entity_stats.armour;
}

bool EntityPlayer::Update(float dt)
{

	if (state == STATE_TURN)
	{
		// DEBUG KEYS
	// 
	//////////////
		if (app->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN)
		{
			app->entityHandler->CreateEntity(ENTITY_DUMMY, 12 * 48, 22 * 48);
		}

		if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) // Step Free
		{
			moveType = STEP_FREE;

		}
		if (app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) // Step Tiles
		{
			moveType = STEP_TILES;
		}

		if (app->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
		{
			if (app->physics->GetDebug() == true)
			{
				app->physics->SetDebug(false);
			}
			else
			{
				app->physics->SetDebug(true);
			}

		}
		if (app->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
		{
			/*if (app->render->cameraFollow == true)
			{
				app->render->cameraFollow = false;
			}
			else
			{
				app->render->cameraFollow = true;
			}*/
			app->render->cameraFollow = !app->render->cameraFollow;

		}


		if (app->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
		{
			currentAnimation = &jump;
		}

		/*if (app->render->cameraFollow == true)
		{
			LOG("True");
		}
		else
		{
			LOG("False");
		}*/


		switch (moveType)
		{
		case STEP_TILES:
		{
			goLeft = (app->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN);
			goRight = (app->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN);

			goUp = (app->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN);
			goDown = (app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN);

			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
			{

			}

			// implement attack !!
			if (app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
			{
				enemyFocused = NULL;
				// change moveType!!!!

				enemyFocused = checkCloseEnemies();
				if (enemyFocused)
				{
					moveType = FOCUSING;
				}
			}
			if (goRight) Interpolate(x + 48, y, inter_speed);
			else if (goLeft) Interpolate(x - 48, y, inter_speed);
			else if (goUp) Interpolate(x, y - 48, inter_speed);
			else if (goDown) Interpolate(x, y + 48, inter_speed);

			if (interpolating)
			{

				Interpolate(newX, newY, 0.01f);
			}
			else
			{
				if (goUp)
				{
					lastDirection = MOV_UP;
				}
				else if (goDown)
				{
					lastDirection = MOV_DOWN;
				}
				else if (goLeft)
				{
					//currentAnimation = &idle_left;
					lastDirection = MOV_LEFT;
					lastHorizontalAxis = MOV_LEFT;
				}
				else if (goRight)
				{
					//currentAnimation = &idle_right;
					lastDirection = MOV_RIGHT;
					lastHorizontalAxis = MOV_RIGHT;

				}
				else if (goRight && goDown || goRight && goUp)
				{

					lastDirection = MOV_RIGHT;
					lastHorizontalAxis = MOV_RIGHT;
				}
				else if (goLeft && goDown || goLeft && goUp)
				{


					lastDirection = MOV_LEFT;
					lastHorizontalAxis = MOV_LEFT;
				}
			}
		} break;
		case FOCUSING:
		{
			if (app->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN)
			{
				Attack_01(enemyFocused->entity_ptr);
				state = STATE_DYING;
			}

			if (app->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN)
			{
				moveType = STEP_TILES;
				state = STATE_DYING;
			}
		} break;
		}

		

	}
	else if (state == STATE_WAIT)
	{

	}
	else if (state == STATE_FREE)
	{

		goLeft = (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT);
		goRight = (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT);

		goUp = (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT);
		goDown = (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT);

		b2Vec2 movement = { (goRight - goLeft) * Vspeed.x, (goDown - goUp) * Vspeed.y };
		Hitbox->body->SetLinearVelocity(movement);
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

	

	

	oldHP = entity_stats.hp;

	//do damage
	if (app->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		changingHP = (float)entity_stats.hp;
		entity_stats.hp -= 1; // Baja un monton por el daño del enemigo, huyue de el y spamea r para ver que funciona
	}

	if (changingHP > (float)entity_stats.hp)
	{

		changingHP -= changingSpeed;
	}
	else
	{
		changingHP = (float)entity_stats.hp;
	}

	if (changingHP <= 0)
	{
		app->entityHandler->DestroyEnemy(Hitbox->body);
	}

	rec_curr_h = changingHP / (float)totalHealth * (float)recHealth.w;
	to_draw = (int)rec_curr_h;

	rec_temp_h = recHealth;
	rec_temp_h.w = to_draw;


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

