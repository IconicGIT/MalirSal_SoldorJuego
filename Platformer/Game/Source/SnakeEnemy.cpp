
#include "SnakeEnemy.h"
#include "Textures.h"
#include "Render.h"
#include "input.h"
SnakeEnemy::SnakeEnemy(b2Vec2 startPosition, int health) : EntityEnemy()
{
	setPosition(startPosition.x,startPosition.y);
	entity_stats.hp = health;

	name.Create("snake");
	Hitbox = app->physics->CreateCircle(startPosition.x, startPosition.y, 16);
	Hitbox->body->SetSleepingAllowed(false);

	Hitbox->body->SetGravityScale(0);
	Hitbox->body->GetFixtureList()->SetRestitution(0);
	Hitbox->body->SetFixedRotation(true);
	Hitbox->body->ResetMassData();
	Hitbox->entity_ptr = this;

}

SnakeEnemy::~SnakeEnemy() {}

bool SnakeEnemy::Awake()
{
	return false;
}


bool SnakeEnemy::Start()
{
	turn = true;
	speed = 1;
	Vspeed = { speed,speed };

	pac = app->tex->Load("Assets/textures/enemies/snake_idle.png");
	LifeBars = app->tex->Load("Assets/textures/UI/HealthBar DARK.png");

	recHealth = { 18, 152, 59, 6 };
	recHealthBG = { 17, 164, 61, 8 };

	a = { 0, 0, 48, 48 };
	inter_speed = 0.02f;
	return true;

	entity_stats.hp = totalHealth = 10;
	entity_stats.armour = 20;
	entity_stats.damage = 10;
	entity_stats.momevent = 5;
	entity_stats.speed = 6;
}

void SnakeEnemy::Attck_01(Entity* player)
{
	player->entity_stats.hp -= this->entity_stats.damage * (1 / player->entity_stats.armour);
}

bool SnakeEnemy::Update(float dt)
{

	if (app->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN) turn = true;

	x = (float)METERS_TO_PIXELS(Hitbox->body->GetPosition().x);
	y = (float)METERS_TO_PIXELS(Hitbox->body->GetPosition().y);

	if (turn)
	{


		if (interpolating)
		{
			Interpolate(newX, newY, 0.02f);
		}
		else
		{
			behaviour = rand() % 50;

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
						app->render->DrawRectangle({ app->pathfinding->GetLastPath()->At(i)->x, app->pathfinding->GetLastPath()->At(i)->y, 48, 48 }, 255, 255, 255, 255);
					}

					int chosing = app->pathfinding->CreatePath(pos, chicken);

					if (chosing > 2) // creating path bc creates errors
					{

						const iPoint* going(app->pathfinding->GetLastPath()->At(1));
						if (going != nullptr)
						{
							b2Vec2 movement = { 0,0 };

							if (going->x < pos.x) // LEFT
							{
								Interpolate(x - 48, y, inter_speed);
							}
							else if (going->x > pos.x) // RIGHT
							{
								Interpolate(x + 48, y, inter_speed);
							}
							else if (going->y < pos.y) // UP
							{
								Interpolate(x, y - 48, inter_speed);
							}
							else if (going->y > pos.y) // DOWN
							{
								Interpolate(x, y + 48, inter_speed);
							}
							else
							{

							}
						}



					}
					else if (chosing > 0)
					{
						//ATACK
						if (behaviour < 25)
						{
							Attck_01(goal->entity_ptr);
						}
						else
						{

						}
						turn = false;
					}
				}
			}
		}
	}

	oldHP = entity_stats.hp;

	//do damage
	if (app->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		changingHP = (float)entity_stats.hp;
		entity_stats.hp -= 25;
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
	rec_temp_h.w = rec_curr_h;
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
void SnakeEnemy::Draw()
{
	app->render->DrawTexture(pac, x - 24, y - 24, &a);

	app->render->DrawTexture(LifeBars, METERS_TO_PIXELS(Hitbox->body->GetPosition().x) - 30, METERS_TO_PIXELS(Hitbox->body->GetPosition().y) - 25, &recHealthBG);
    app->render->DrawTexture(LifeBars, x - 29, y - 24, &rec_temp_h);
}

int SnakeEnemy::Attack(int enemyType)
{
	return 0;
}