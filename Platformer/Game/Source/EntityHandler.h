#ifndef __ENEMY_HANDLER_H__
#define __ENEMY_HANDLER_H__

#include "Module.h"
#include "p2Point.h"
#include "p2List.h"
#include "App.h"
#include "Physics.h"
#include <math.h>
#include "SDL/include/SDL.h"
#include "Render.h"
#include "Animation.h"
#include "Log.h"
#include "Map.h"
#include "Pathfinding.h"

//entities
#include "Entity.h"
#include "EntityPlayer.h"
#include "EntityDummy.h"
#include "Item.h"
class EntityPlayer;

enum EntityType
{
	ENTITY_NULL = -1,
	ENTITY_PLAYER,
	ENTITY_DUMMY,
	ITEM_BANANA
};

class Item;

class EntityHandler : public Module
{
public:
	EntityHandler();
	virtual ~EntityHandler();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();
	bool Update(float dt);
	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;
	bool CleanUp();
	void CreateEntity(enum EntityType type, int x, int y);
	void DestroyEnemy(b2Body* body);
	/*void DamageEnemy(b2Body* body, int damage);*/
	void HandleEnemyDespawn();
	void DestroyAllEnemies();

	EntityType GetEntityType(b2Body*) const;
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

	bool checkForEnemies();
	
	p2List<Entity*> allEntities;
	
	p2List<Item*> items;
	p2List<EntityDummy*> dummies;

	p2List<EntityPlayer*> players;

	SDL_Texture* texturePath;

	PhysBody* GetNearestChicken(PhysBody* Character);

	EntityPlayer* GetMainPlayer() const
	{
		return player;
	}

private:

	EntityPlayer* player;
	int all_ids;
	

	
	

};

#endif // __ENEMY_HANDLER_H__
