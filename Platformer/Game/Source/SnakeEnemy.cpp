
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
	turn_ends = false;
	speed = 1;
	Vspeed = { speed,speed };

	pac = app->tex->Load("Assets/textures/enemies/snake_idle.png");
	a = { 0, 0, 48, 48 };
	inter_speed = 0.02f;
	return true;
}
bool SnakeEnemy::Update(float dt)
{

	if (app->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN) turn_ends = false;

	x = (float)METERS_TO_PIXELS(Hitbox->body->GetPosition().x);
	y = (float)METERS_TO_PIXELS(Hitbox->body->GetPosition().y);

	if (!turn_ends)
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

						}
						else
						{

						}
						turn_ends = true;
					}
				}
			}
		}
	}
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
}

int SnakeEnemy::Attack(int enemyType)
{
	return 0;
}
