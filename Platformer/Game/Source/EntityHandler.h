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

#include "Defs.h"

//entities
#include "Entity.h"
#include "EntityPlayer.h"
#include "EntityEnemies.h"
#include "EntityDummy.h"
#include "Item.h"

class EntityEnemy;
class EntityPlayer;

enum EntityType
{
	ENTITY_NULL = -1,
	ENTITY_PLAYER,
	ENTITY_DUMMY,
	ENTITY_SNAKE,
	ENTITY_SOLDOR
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
	void DrawAllEntities();

	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;
	bool CleanUp();
	void CreateEntity(enum EntityType type, int x, int y);
	void DestroyEnemy(b2Body* body);
	void DestroyPlayer(b2Body* body);
	
	/*void DamageEnemy(b2Body* body, int damage);*/
	
	void DestroyAllEnemies();
	void OrderBySpeed();
	void StartCombat();
	void NextTurn(PhysBody* finished);
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
	p2List<EntityEnemy*> enemies;
	p2List<EntityPlayer*> players;

	SDL_Texture* texturePath;

	PhysBody* GetNearestChicken(PhysBody* Character);
	PhysBody* GetNearestEnemy(PhysBody* Character);

	EntityPlayer* GetMainPlayer() const
	{
		return player;
	}



private:

	EntityPlayer* player;
	int all_ids;
	

	// SORTING ALGORITHM

	/* sorts the linked list by changing next pointers (not data) */
	void MergeSort(p2List_item<Entity*>* headRef)
	{
		p2List_item<Entity*>* head = headRef;
		p2List_item<Entity*>* a;
		p2List_item<Entity*>* b;

		/* Base case -- length 0 or 1 */
		if ((head == NULL) || (head->next == NULL)) {
			return;
		}

		/* Split head into 'a' and 'b' sublists */
		FrontBackSplit(head, &a, &b);

		/* Recursively sort the sublists */
		MergeSort(a);
		MergeSort(b);

		/* answer = merge the two sorted lists together */
		headRef = SortedMerge(a, b);
	}

	/* See https:// www.geeksforgeeks.org/?p=3622 for details of this
	function */
	p2List_item<Entity*>* SortedMerge(p2List_item<Entity*>* a, p2List_item<Entity*>* b)
	{
		p2List_item<Entity*>* result = NULL;

		/* Base cases */
		if (a == NULL)
			return (b);
		else if (b == NULL)
			return (a);

		/* Pick either a or b, and recur */
		if (a->data->entity_stats.speed >= b->data->entity_stats.speed) {
			result = a;
			result->next = SortedMerge(a->next, b);
		}
		else {
			result = b;
			result->next = SortedMerge(a, b->next);
		}
		return (result);
	}
	
	void FrontBackSplit(p2List_item<Entity*>* source,
		p2List_item<Entity*>** frontRef, p2List_item<Entity*>** backRef)
	{
		p2List_item<Entity*>* fast;
		p2List_item<Entity*>* slow;
		slow = source;
		fast = source->next;

		/* Advance 'fast' two p2List_item<Entity*>s, and advance 'slow' one p2List_item<Entity*> */
		while (fast != NULL) {
			fast = fast->next;
			if (fast != NULL) {
				slow = slow->next;
				fast = fast->next;
			}
		}

		/* 'slow' is before the midpoint in the list, so split it in two
		at that point. */
		*frontRef = source;
		*backRef = slow->next;
		slow->next = NULL;
	}
};

#endif // __ENEMY_HANDLER_H__
