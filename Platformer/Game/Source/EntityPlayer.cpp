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




EntityPlayer::EntityPlayer(b2Vec2 startPosition, int id_) : Entity()
{
	spawnPosition = startPosition;
	name.Create("chicken_idle");
	Hitbox = app->physics->CreateCircle(spawnPosition.x, spawnPosition.y, 16);
	Hitbox->body->SetSleepingAllowed(false);
	Hitbox->body->SetGravityScale(0);
	Hitbox->body->GetFixtureList()->SetRestitution(0);
	Hitbox->body->SetFixedRotation(true);
	Hitbox->body->ResetMassData();
	Hitbox->entity_ptr = this;
	inter_speed = 0.025f;

	entity_stats.hp = 16;
	totalHealth = entity_stats.hp;
	entity_stats.armour = 0.8;
	entity_stats.damage = 6;
	entity_stats.momevent = 5;
	entity_stats.speed = 4;
	actual_mov = entity_stats.momevent;
	id = id_;
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

	recHealth = { 19, 30, 62, 4 };
	recHealthBG = { 18, 40, 64, 6 };

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
	state = STATE_FREE;
	LOG("player started");

	//23
	idle.PushBack({ 0 , id * 64 * 4, 64, 64});
	idle.PushBack({ 64 * 1, id * 64 * 4, 64, 64 }) ;
	idle.PushBack({ 64 * 2, id * 64 * 4, 64, 64 }) ;
	idle.PushBack({ 64 * 3, id * 64 * 4, 64, 64 }) ;
	idle.PushBack({ 64 * 4, id * 64 * 4, 64, 64 }) ;
	idle.PushBack({ 64 * 5, id * 64 * 4, 64, 64 }) ;
	idle.PushBack({ 64 * 6, id * 64 * 4, 64, 64 }) ;
	idle.PushBack({ 64 * 7, id * 64 * 4, 64, 64 }) ;
	idle.PushBack({ 64 * 8, id * 64 * 4, 64, 64 }) ;
	idle.PushBack({ 64 * 9,  id * 64 * 4, 64, 64 }) ;
	idle.PushBack({ 64 * 10, id * 64 * 4, 64, 64 });
	idle.PushBack({ 64 * 11, id * 64 * 4, 64, 64 });
	idle.PushBack({ 64 * 12, id * 64 * 4, 64, 64 });
	idle.PushBack({ 64 * 13, id * 64 * 4, 64, 64 });
	idle.PushBack({ 64 * 14, id * 64 * 4, 64, 64 });
	idle.PushBack({ 64 * 15, id * 64 * 4, 64, 64 });
	idle.PushBack({ 64 * 16, id * 64 * 4, 64, 64 });
	idle.PushBack({ 64 * 17, id * 64 * 4, 64, 64 });
	idle.PushBack({ 64 * 18, id * 64 * 4, 64, 64 });
	idle.PushBack({ 64 * 19, id * 64 * 4, 64, 64 });
	idle.PushBack({ 64 * 20, id * 64 * 4, 64, 64 });
	idle.PushBack({ 64 * 21, id * 64 * 4, 64, 64 });
	idle.PushBack({ 64 * 22, id * 64 * 4, 64, 64 });

	idle.speed = 0.18f;


	//jump.PushBack({ 0 , 64 * 1, 64, 64 });
	//jump.PushBack({ 64 * 1, 64 * 1, 64, 64 });
	//jump.PushBack({ 64 * 2, 64 * 1, 64, 64 });
	//jump.PushBack({ 64 * 3, 64 * 1, 64, 64 });
	//jump.PushBack({ 64 * 4, 64 * 1, 64, 64 });
	jump.PushBack({ 64 * 5, (id * 64 * 4) + 64 * 1, 64, 64 });
	//jump.PushBack({ 64 * 6, 64 * 1, 64, 64 });
	jump.PushBack({ 64 * 7, (id * 64 * 4) + 64 * 1, 64, 64 });
	jump.PushBack({ 64 * 8, (id * 64 * 4) + 64 * 1, 64, 64 });
	jump.PushBack({ 64 * 9,  (id * 64 * 4) + 64 * 1, 64, 64 });
	jump.PushBack({ 64 * 10, (id * 64 * 4) + 64 * 1, 64, 64 });
	jump.PushBack({ 64 * 11, (id * 64 * 4) + 64 * 1, 64, 64 });
	
	//jump.PushBack({ 64 * 11, 64 * 1, 64, 64 });
	
	jump.PushBack({ 64 * 12, (id * 64 * 4) + 64 * 1, 64, 64 });
	jump.PushBack({ 64 * 12, (id * 64 * 4) + 64 * 1, 64, 64 });


	jump.PushBack({ 64 * 13, (id * 64 * 4) + 64 * 1, 64, 64 });
	jump.PushBack({ 64 * 14, (id * 64 * 4) + 64 * 1, 64, 64 });
	
	

	jump.speed = 0.25f;
	jump.loop = false;

	out_of_steps = false;


	death.PushBack({ 64 * 0, 64 * 12, 64, 64 });
	death.PushBack({ 64 * 1+1, 64 * 12, 64, 64 });
	death.PushBack({ 64 * 2-1, 64 * 12, 64, 64 });
	death.PushBack({ 64 * 3, 64 * 12, 64, 64 });
	death.PushBack({ 64 * 4, 64 * 12, 64, 64 });
	death.PushBack({ 64 * 5+1, 64 * 12, 64, 64 });
	death.PushBack({ 64 * 6 , 64 * 12, 64, 64 });
	death.PushBack({ 64 * 7, 64 * 12, 64, 64 });
	death.PushBack({ 64 * 8, 64 * 12, 64, 64 });
	death.PushBack({ 64 * 9,  64 * 12, 64, 64 });
	death.PushBack({ 64 * 10, 64 * 12, 64, 64 });
	death.PushBack({ 64 * 11, 64 * 12, 64, 64 });
	death.PushBack({ 64 * 12, 64 * 12, 64, 64 });
	death.PushBack({ 64 * 13, 64 * 12, 64, 64 });
	death.PushBack({ 64 * 14, 64 * 12, 64, 64 });
	death.PushBack({ 64 * 15, 64 * 12, 64, 64 });
	death.PushBack({ 64 * 16, 64 * 12, 64, 64 });
	death.PushBack({ 64 * 17, 64 * 12, 64, 64 });
	death.PushBack({ 64 * 18, 64 * 12, 64, 64 });
	death.PushBack({ 64 * 19, 64 * 12, 64, 64 });
	death.PushBack({ 64 * 20, 64 * 12, 64, 64 });
	death.PushBack({ 64 * 21, 64 * 12, 64, 64 });
	

	death.loop = false;
	death.speed = 0.1f;

	attack = app->tex->Load("Assets/textures/UI/attack_anim.png");

	scar.PushBack({ 0 * 48, 1 * 48, 48, 48 });
	scar.PushBack({ 1 * 48, 1 * 48, 48, 48 });
	scar.PushBack({ 2 * 48, 1 * 48, 48, 48 });
	scar.PushBack({ 3 * 48, 1 * 48, 48, 48 });
	scar.PushBack({ 4 * 48, 1 * 48, 48, 48 });
	scar.PushBack({ 5 * 48, 1 * 48, 48, 48 });
	scar.PushBack({ 6 * 48, 1 * 48, 48, 48 });
	scar.PushBack({ 7 * 48, 1 * 48, 48, 48 });
	scar.PushBack({ 8 * 48, 1 * 48, 48, 48 });
	scar.speed = 0.1f;
	scar.loop = false;

	attack_.PushBack({ 0 * 64, (id * 64 * 4) + 3 * 64, 64, 64 });
	attack_.PushBack({ 1 * 64, (id * 64 * 4) + 3 * 64, 64, 64 });
	attack_.PushBack({ 2 * 64, (id * 64 * 4) + 3 * 64, 64, 64 });
	attack_.PushBack({ 3 * 64, (id * 64 * 4) + 3 * 64, 64, 64 });
	attack_.PushBack({ 4 * 64, (id * 64 * 4) + 3 * 64, 64, 64 });
	attack_.PushBack({ 5 * 64, (id * 64 * 4) + 3 * 64, 64, 64 });
	attack_.PushBack({ 6 * 64, (id * 64 * 4) + 3 * 64, 64, 64 });
	attack_.PushBack({ 7 * 64, (id * 64 * 4) + 3 * 64, 64, 64 });
	attack_.PushBack({ 8 * 64, (id * 64 * 4) + 3 * 64, 64, 64 });
	attack_.PushBack({ 9 * 64, (id * 64 * 4) + 3 * 64, 64, 64 });
	attack_.PushBack({ 10 * 64,(id * 64 * 4) +  3 * 64, 64, 64 });
	attack_.PushBack({ 11 * 64,(id * 64 * 4) +  3 * 64, 64, 64 });

	attack_.loop = false;
	attack_.speed = 0.16f;

	damage.PushBack({ 0 * 64, (id * 64 * 4) +  2 * 64, 64, 64 });
	damage.PushBack({ 1 * 64, (id * 64 * 4) +  2 * 64, 64, 64 });
	damage.PushBack({ 2 * 64, (id * 64 * 4) +  2 * 64, 64, 64 });
	damage.PushBack({ 3 * 64, (id * 64 * 4) +  2 * 64, 64, 64 });
	damage.PushBack({ 4 * 64, (id * 64 * 4) +  2 * 64, 64, 64 });
	damage.PushBack({ 5 * 64, (id * 64 * 4) +  2 * 64, 64, 64 });
	damage.PushBack({ 6 * 64, (id * 64 * 4) +  2 * 64, 64, 64 });
	damage.PushBack({ 7 * 64, (id * 64 * 4) +  2 * 64, 64, 64 });
	damage.PushBack({ 8 * 64, (id * 64 * 4) +  2 * 64, 64, 64 });
	

	damage.loop = false;
	damage.speed = 0.16f;
	

	currentAnimation = &idle;
	changingSpeed = 0.1f;

	// La changing speed tiene que ser siempre inferior al daño que se le aplica a la entidad

	return true;
}

bool EntityPlayer::CleanUp()
{
	LOG("Unloading player");
	app->entityHandler->DestroyPlayer(Hitbox);
	
	return true;
}

void EntityPlayer::Draw()
{

	currentAnimation->Update();
	if (currentAnimation->HasFinished())
	{
		if (currentAnimation == &jump)
		{
			currentAnimation = &idle;
			jump.Reset();
		}
		else if (currentAnimation == &attack_ )
		{
			currentAnimation = &idle;
			attack_.Reset();
		}
		else if (currentAnimation == &damage)
		{
			currentAnimation = &idle;
			damage.Reset();
		}
	}
	if (lastDirection == MOV_LEFT)
	{
		app->render->DrawTexture(sprite, x - 32, y - 40, &currentAnimation->GetCurrentFrame());
	}
	else if (lastDirection == MOV_RIGHT)
	{
		app->render->DrawTexture(sprite, x - 32, y - 40, &currentAnimation->GetCurrentFrame(), SDL_FLIP_HORIZONTAL);
	}



	app->render->DrawTexture(LifeBars, METERS_TO_PIXELS(Hitbox->body->GetPosition().x) - 30, METERS_TO_PIXELS(Hitbox->body->GetPosition().y) - 54, &recHealthBG);
	app->render->DrawTexture(LifeBars, x - 29, y - 53, &rec_temp_h);

}

void EntityPlayer::DrawUI()
{
	if (doing_scar)
	{

		if (!scar.HasFinished())
		{
			scar.Update();
			app->render->DrawTexture(attack, pos_anim.x, pos_anim.y, &scar.GetCurrentFrame());
		}
		else
		{
			finish_animation = true;
			scar.Reset();
		}
	}
}

PhysBody* EntityPlayer::checkCloseEnemies()
{
	PhysBody* enemy = app->entityHandler->GetNearestEnemy(Hitbox);
	iPoint a;
	iPoint b;
	enemy->GetPosition(a.x, a.y);
	a = app->map->WorldToMap(a.x, a.y);
	b = app->map->WorldToMap(x, y);
	int chosing = app->pathfinding->CreatePath(b, a);

	if(id == 1 && (chosing < 8))
	{
		return enemy;
	}
	else if (chosing < 3)
	{
		return enemy;
	}
	else
	{
		return NULL;
	}
	
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
	//
	currentAnimation = &attack_;
	enemy->entity_stats.hp -= this->entity_stats.damage * enemy->entity_stats.armour;
	int x_, y_;
	enemy->Hitbox->GetPosition(x_, y_);
	pos_anim.x = x_;
	pos_anim.y = y_;
	doing_scar = true;
	state = STATE_WAIT;
	enemy->last_damaged = Hitbox;

}

void EntityPlayer::LongShot(Entity* enemy)
{
	//
	currentAnimation = &attack_;
	enemy->entity_stats.hp -= this->entity_stats.damage * enemy->entity_stats.armour;
	int x_, y_;
	enemy->Hitbox->GetPosition(x_, y_);
	pos_anim.x = x_;
	pos_anim.y = y_;
	doing_scar = true;
	state = STATE_WAIT;
	enemy->last_damaged = Hitbox;

}

void EntityPlayer::PushAttack(Entity* enemy)
{
	//
	currentAnimation = &attack_;
	enemy->entity_stats.hp -= this->entity_stats.damage * enemy->entity_stats.armour;
	int x_, y_;
	enemy->Hitbox->GetPosition(x_, y_);
	pos_anim.x = x_;
	pos_anim.y = y_;
	doing_scar = true;
	state = STATE_WAIT;
	enemy->last_damaged = Hitbox;

}

bool EntityPlayer::Update(float dt)
{

	x = (float)METERS_TO_PIXELS(Hitbox->body->GetPosition().x);
	y = (float)METERS_TO_PIXELS(Hitbox->body->GetPosition().y);

	if (state == STATE_TURN)
	{
	
		if (app->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN)
		{
			app->entityHandler->CreateEntity(ENTITY_DUMMY, 12 * 48, 22 * 48, 0);
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

			

			
			if (interpolating)
			{

				Interpolate(newX, newY, 0.01f);
			}
			else
			{
				if (actual_mov == 0)
				{
					out_of_steps = true;
				}
				else
				{
					if (goRight)
					{
						lastDirection = MOV_RIGHT;
						lastHorizontalAxis = MOV_RIGHT;
						Interpolate(x + 64, y, inter_speed);
						currentAnimation = &jump;
					}
					else if (goLeft)
					{
						Interpolate(x - 64, y, inter_speed);
						lastDirection = MOV_LEFT;
						currentAnimation = &jump;
					}
					else if (goUp)
					{
						Interpolate(x, y - 64, inter_speed);
						currentAnimation = &jump;
					}
					else if (goDown)
					{
						Interpolate(x, y + 64, inter_speed);
						currentAnimation = &jump;
					}

					
					
				}

				// implement attack !!
				if (app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
				{
					enemyFocused = NULL;
					// change moveType!!!!

					enemyFocused = checkCloseEnemies();
					if (enemyFocused != NULL)
					{
						moveType = FOCUSING;
					}
				}
			}
			
			
		} break;
		case FOCUSING:
		{
			if (app->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN) 
			{
				Attack_01(enemyFocused->entity_ptr);
				
				moveType = STEP_TILES;
				out_of_attacks = true;
			}

			if (app->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN)
			{
				moveType = STEP_TILES;
				
			}

			if (app->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN)
			{
				if (id = 0)
				{
					PushAttack(enemyFocused->entity_ptr);

					moveType = STEP_TILES;
					out_of_attacks = true;
				}
				else if (id == 1)
				{

				}
				else if (id == 2)
				{
					LongShot(enemyFocused->entity_ptr);

					moveType = STEP_TILES;
					out_of_attacks = true;
				}

			}

		} break;
		default:
		{

		} break;
		}
		

		if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
		{
			AdminMode = !AdminMode;
		}

		if (!AdminMode)
		{

			if (Hitbox->body->GetFixtureList()->IsSensor())
			{
				Hitbox->body->GetFixtureList()->SetSensor(false);
			}
		}
		else
		{

			if (!Hitbox->body->GetFixtureList()->IsSensor())
			{
				Hitbox->body->GetFixtureList()->SetSensor(true);
			}

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
	else if (state == STATE_DYING)
	{
		if (currentAnimation->HasFinished())
		{
			CleanUp();
			delete(this);
			app->entityHandler->NextTurn(last_damaged);
		}
	}

	

	
	
	


	

	mapPos = app->map->WorldToMap(METERS_TO_PIXELS(Hitbox->body->GetPosition().x), METERS_TO_PIXELS(Hitbox->body->GetPosition().y));

	//gidNow = app->map->data.layers.start->data->Get(mapPos.x, mapPos.y);
	//
	//gidLeft = app->map->data.layers.start->data->Get(mapPos.x - 1, mapPos.y);
	//gidRight = app->map->data.layers.start->data->Get(mapPos.x + 1, mapPos.y);
	//gidUp = app->map->data.layers.start->data->Get(mapPos.x, mapPos.y - 1);
	//gidDown = app->map->data.layers.start->data->Get(mapPos.x, mapPos.y + 1);




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
		app->entityHandler->DestroyEnemy(Hitbox);
	}

	rec_curr_h = changingHP / (float)totalHealth * (float)recHealth.w;
	to_draw = (int)rec_curr_h;

	rec_temp_h = recHealth;
	rec_temp_h.w = to_draw;

	if (entity_stats.hp <= 0)
	{
		state = STATE_DYING;
		currentAnimation = &death;
	}

	if ( out_of_steps || (finish_animation && out_of_attacks)|| (app->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN))
	{
		app->entityHandler->NextTurn(Hitbox);
		finish_animation = false;
		doing_scar = false;
		out_of_steps = false;
		out_of_attacks = false;
		actual_mov = entity_stats.momevent;
	}
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

