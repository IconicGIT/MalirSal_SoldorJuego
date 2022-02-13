#ifndef __ENTITY_PLAYER_H__
#define __ENTITY_PLAYER_H__
#include "Entity.h"
#include "p2Point.h"
#include "p2List.h"
#include "App.h"
#include "Physics.h"
#include <math.h>
#include "SDL/include/SDL.h"
#include "Render.h"
#include "Animation.h"
#include "Log.h"
#include "EntityHandler.h"
#include "EntityEnemies.h"
class EntityPlayer : public Entity
{
public:
	EntityPlayer(b2Vec2 startPosition, int health);
	virtual ~EntityPlayer();
	bool Awake();
	bool Start();
	bool Update(float dt);
	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;
	bool CleanUp();
	bool PhysBodyIsInMap(PhysBody* phys)
	{
		iPoint positionInMap(
			app->map->WorldToMap(
				METERS_TO_PIXELS(phys->body->GetPosition().x),
				METERS_TO_PIXELS(phys->body->GetPosition().y)
			)
		);
		return app->pathfinding->CheckBoundaries(positionInMap);
	}
	
	void Draw() override;
	void DrawUI() override;
	PhysBody* GetPhysBody() const
	{
		return Hitbox;
	}


	iPoint GetPosition()
	{
		return iPoint(x, y);	
	}
	void setPosition(int x, int y)
	{
		b2Vec2 v(x, y);
		Hitbox->body->SetTransform(v, 0);
	}
	void ClampPos(int mapX, int mapY)
	{
		iPoint worldPos = app->map->MapToWorld(mapX, mapY);
		float bodyX = PIXEL_TO_METERS(worldPos.x) + 23;
		float bodyY = PIXEL_TO_METERS(worldPos.y) + 23;
		b2Vec2 v = { bodyX,bodyY };
		Hitbox->body->SetTransform(v, 0);
	}
	void Interpolate(int x, int y, float speed) 
	{
		newX = (float)x ;
		newY = (float)y ;
		if (!interpolating)
		{
			h = 0;
			iSpeed = speed; 
			if (speed > 1) iSpeed = 1;
			if (speed < 0) iSpeed = 0;
			oldX = this->x;
			oldY = this->y;
			interpolating = true;
			pos_dif_x = newX - oldX;
			pos_dif_y = newY - oldY;
			actual_mov--;
		}
		else {
			h += iSpeed;
			if (1 - h < 0)
				h = 1;
			
			float x_ = oldX + pos_dif_x * h;
			float y_ = oldY + pos_dif_y * h;
			b2Vec2 pos = { PIXEL_TO_METERS(x_),PIXEL_TO_METERS(y_) };
			Hitbox->body->SetTransform(pos, 0);
			if (h == 1)
			{
				interpolating = false;
				h = 0;
				Hitbox->body->SetLinearVelocity(b2Vec2(0, 0));
			}
		}
		
		
	}
	
	PhysBody* checkCloseEnemies();
	int CheckDistanceToPhysBody(PhysBody* PhysPos)
	{
		b2Vec2 dist = PhysPos->body->GetPosition() - Hitbox->body->GetPosition();
		return (abs(dist.x) + abs(dist.y));
	}
	void LvlUp(int exp_used);
	void Attack_01(Entity* enemy);
	PlayerMovementType moveType;
	PhysBody* enemyFocused;
private:
	float iSpeed;
	bool interpolating = false;;
	float oldX;
	float oldY;
	float newX;
	float newY;
	float pos_dif_x;
	float pos_dif_y;
	float h = 0;
	float inter_speed;
	b2Vec2 spawnPosition;
	
	int health;
	float x, y;
	float speed;
	b2Vec2 tileVspeed;
	float tileSpeed;
	b2Vec2 Vspeed;
	MovementDirection lastDirection;
	MovementDirection lastHorizontalAxis;
	
	Stats player_stats;
	bool canMove;
	bool goUp;
	bool goDown;
	bool goLeft;
	bool goRight;
	bool AdminMode;
	int gidUp;
	int gidDown;
	int gidLeft;
	int gidRight;
	int gidNow;
	bool tileFreeUp;
	bool tileFreeDown;
	bool tileFreeLeft;
	bool tileFreeRight;
	int playerId;
	iPoint mapPos;
	int level;
	int exp;
	int exp_lvlUp;
	SDL_Texture* sprite;
	Animation idle_left;
	Animation idle_right;
	Animation jump;
	Animation damage;
	Animation attack_;
	Animation* currentAnimation;

	bool out_of_attacks = false;
	

	// Heath bar members
	SDL_Texture* LifeBars;
	SDL_Rect recHealth;
	SDL_Rect recHealthBG;

	Animation idle;
	Animation death;
	bool out_of_steps = false;
	Animation scar;
	bool finish_animation = false;
	bool doing_scar = false;
	SDL_Texture* attack;
	b2Vec2 pos_anim;
	int actual_mov;
	float changingSpeed, changingHP;
	int newHP, oldHP;
	float rec_curr_h;
	int to_draw;
	SDL_Rect rec_temp_h;
	int totalHealth;
};

#endif // __ENEMY_SNAKE_H__                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    