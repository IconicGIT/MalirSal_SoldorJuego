#include "GhostEnemy.h"
#include "Textures.h"
#include "Render.h"
#include "input.h"

GhostEnemy::GhostEnemy(b2Vec2 startPosition, int health) : EntityEnemy()
{
	setPosition(startPosition.x, startPosition.y);
	entity_stats.hp = health;
	entity_stats.armour = 1;
	entity_stats.damage = 10;
	entity_stats.movement = 6;
	entity_stats.speed = 6;
	name.Create("ghost");
	Hitbox = app->physics->CreateCircle(startPosition.x, startPosition.y, 16);
	Hitbox->body->SetSleepingAllowed(false);

	Hitbox->body->SetGravityScale(0);
	Hitbox->body->GetFixtureList()->SetRestitution(0);
	Hitbox->body->SetFixedRotation(true);
	Hitbox->body->ResetMassData();
	Hitbox->entity_ptr = this;

}

GhostEnemy::~GhostEnemy() {}

bool GhostEnemy::Awake()
{
	return false;
}


bool GhostEnemy::Start()
{
	state = STATE_WAIT;
	speed = 1;
	Vspeed = { speed,speed };

	pac = app->tex->Load("Assets/textures/enemies/Enemigos.png");
	LifeBars = app->tex->Load("Assets/textures/UI/HealthBar DARK.png");

	recHealth = { 18, 152, 59, 6 };
	recHealthBG = { 17, 164, 61, 8 };

	idle.PushBack({ 0, 0, 48, 48 });
	idle.PushBack({ 48 * 1, 0, 48, 48 });
	idle.PushBack({ 48 * 2, 0, 48, 48 });
	idle.PushBack({ 48 * 3, 0, 48, 48 });
	idle.PushBack({ 48 * 4, 0, 48, 48 });
	idle.PushBack({ 48 * 5, 0, 48, 48 });
	idle.PushBack({ 48 * 6, 0, 48, 48 });
	idle.PushBack({ 48 * 7, 0, 48, 48 });
	idle.PushBack({ 48 * 8, 0, 48, 48 });
	idle.PushBack({ 48 * 9, 0, 48, 48 });
	idle.PushBack({ 48 * 10, 0, 48, 48 });
	idle.PushBack({ 48 * 11, 0, 48, 48 });
	idle.PushBack({ 48 * 12, 0, 48, 48 });
	idle.PushBack({ 48 * 13, 0, 48, 48 });
	idle.PushBack({ 48 * 14, 0, 48, 48 });
	idle.PushBack({ 48 * 15, 0, 48, 48 });
	idle.PushBack({ 48 * 16, 0, 48, 48 });
	idle.PushBack({ 48 * 17, 0, 48, 48 });
	idle.PushBack({ 48 * 18, 0, 48, 48 });
	idle.PushBack({ 48 * 19, 0, 48, 48 });
	idle.PushBack({ 48 * 20, 0, 48, 48 });
	

	idle.speed = 0.15f;

	inter_speed = 0.02f;

	currentAnimation = &idle;

	entity_stats.hp = 14;
	totalHealth = entity_stats.hp;
	entity_stats.armour = 1;
	entity_stats.damage = 5;
	entity_stats.movement = 4;
	entity_stats.speed = 2;
	changingSpeed = 0.1f;
	actual_mov = entity_stats.movement;
	out_of_steps = false;
	return true;
}

void GhostEnemy::Attck_01(Entity* player)
{
	player->entity_stats.hp -= entity_stats.damage * player->entity_stats.armour;
	player->last_damaged = Hitbox;
}

bool GhostEnemy::Update(float dt)
{

	if (app->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN) state = STATE_TURN;

	x = (float)METERS_TO_PIXELS(Hitbox->body->GetPosition().x);
	y = (float)METERS_TO_PIXELS(Hitbox->body->GetPosition().y);

	if (state == STATE_TURN)
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
							if (actual_mov == 0)
							{
								out_of_steps = true;
							}
							else
							{

								if (going->x < pos.x) // LEFT
								{
									Interpolate(x - 64, y, inter_speed);
								}
								else if (going->x > pos.x) // RIGHT
								{
									Interpolate(x + 64, y, inter_speed);
								}
								else if (going->y < pos.y) // UP
								{
									Interpolate(x, y - 64, inter_speed);
								}
								else if (going->y > pos.y) // DOWN
								{
									Interpolate(x, y + 64, inter_speed);
								}
								else
								{

								}
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
							Attck_01(goal->entity_ptr);
						}

						out_of_attacks = true;
					}
				}
			}
		}
	}
	else if (state == STATE_DYING)
	{

	}
	oldHP = entity_stats.hp;
	//totalHealth = 10;

	//do damage
	if (app->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		changingHP = (float)entity_stats.hp;
		entity_stats.hp -= 1; // Bro, resulta que tiene 10 de vida y le quitabas 25 ;-( XD
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
		if (state == STATE_TURN)
		{
			app->entityHandler->NextTurn(Hitbox);
		}
		app->entityHandler->DestroyEnemy(Hitbox);
	}

	rec_curr_h = changingHP / (float)totalHealth * (float)recHealth.w;
	to_draw = (int)rec_curr_h;

	rec_temp_h = recHealth;
	rec_temp_h.w = to_draw;

	if (out_of_steps || out_of_attacks || (app->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN))
	{
		app->entityHandler->NextTurn(Hitbox);
		out_of_attacks = false;
		out_of_steps = false;
		actual_mov = entity_stats.movement;
	}

	return false;
}

bool GhostEnemy::LoadState(pugi::xml_node&)
{
	return false;
}
bool GhostEnemy::SaveState(pugi::xml_node&) const
{
	return false;
}
bool GhostEnemy::CleanUp()
{
	return false;
}
void GhostEnemy::Draw()
{
	currentAnimation->Update();

	app->render->DrawTexture(pac, x - 24, y - 24, &idle.GetCurrentFrame());

	app->render->DrawTexture(LifeBars, METERS_TO_PIXELS(Hitbox->body->GetPosition().x) - 30, METERS_TO_PIXELS(Hitbox->body->GetPosition().y) - 24, &recHealthBG);
	app->render->DrawTexture(LifeBars, x - 29, y - 23, &rec_temp_h);
}

int GhostEnemy::Attack(int enemyType)
{
	return 0;
}
