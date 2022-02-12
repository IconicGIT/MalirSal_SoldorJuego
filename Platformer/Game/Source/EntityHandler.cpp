
#include "Input.h"
#include "SDL/include/SDL.h"
#include "p2List.h"
#include "Scene.h"
#include "Physics.h"
#include "Textures.h"
#include"Render.h"
#include "Window.h"
#include "Audio.h";
#include "EntityHandler.h"
#include "SnakeEnemy.h"
#include "SoldorEnemy.h"
#include "GhostEnemy.h"
#include "BatEnemy.h"
#include "MummyEnemy.h"


#include <stdlib.h>     
#include <time.h>       


EntityHandler::EntityHandler() : Module()
{
	name.Create("EntityHandler");
}

EntityHandler::~EntityHandler()
{}

bool EntityHandler::Awake()
{
	return true;
}

bool EntityHandler::Start()
{

	texturePath = app->tex->Load("Assets/maps/meta.png");

	all_ids = 0;

	CreateEntity(ENTITY_PLAYER, 6 * 48, 23 * 48, 0);
	//CreateEntity(ENTITY_DUMMY, 12 * 48, 22 * 48);
	

	return true;
}
bool EntityHandler::CleanUp()
{
	LOG("Unloading eHandler");

	for (int i = 0; i < allEntities.count(); i++)
	{

		Entity* entity;
		allEntities.at(i, entity);

		entity->CleanUp();
	}


	return true;
}

void EntityHandler::CreateEntity(EntityType type, int x, int y, int id__)
{

	switch (type)
	{
	case ENTITY_PLAYER:
	{
		b2Vec2 pos(x + 24, y + 24);
		EntityPlayer* newPlayer = new EntityPlayer(pos, id__);
		player = newPlayer;
		players.add(newPlayer);
		allEntities.add(newPlayer);
		newPlayer->Start();
		newPlayer->SetID(all_ids);
		all_ids++;
	}
	break;
	case ENTITY_DUMMY:
	{
		b2Vec2 pos(x + 24, y + 24);
		EntityDummy* newDummy = new EntityDummy(pos, 2);
		dummies.add(newDummy);
		allEntities.add(newDummy);
		newDummy->Start();
		newDummy->SetID(all_ids);
		all_ids++;
	}
	break;
	case ENTITY_SNAKE:
	{
		b2Vec2 pos(x + 24, y + 24);
		SnakeEnemy* newSnake = new SnakeEnemy(pos, 2);
		enemies.add(newSnake);
		allEntities.add(newSnake);
		newSnake->Start();
		newSnake->SetID(all_ids);
		all_ids++;
	} break;
	case ENTITY_SOLDOR:
	{
		b2Vec2 pos(x + 24, y + 24);
		SoldorEnemy* newSoldor = new SoldorEnemy(pos);
		enemies.add(newSoldor);
		allEntities.add(newSoldor);
		newSoldor->Start();
		newSoldor->SetID(all_ids);
		all_ids++;
	} break;
	/*case ENEMY_SNAKE:
	{
		b2Vec2 pos(x, y);
		EnemySnake* newSnake = new EnemySnake(pos, 2);
		enemiesSnake.add(newSnake);
		allEntities.add(newSnake);
		newSnake->Start();
		newSnake->SetID(all_ids);
		all_ids++;

		break;
	}*/
	/*case ENEMY_BIRD:
	{
		b2Vec2 pos(x, y);
		EnemyBird* newBird = new EnemyBird(pos, 1);
		enemiesBird.add(newBird);
		allEntities.add(newBird);
		newBird->Start();
		newBird->SetID(all_ids);
		all_ids++;

		break;
	}*/
	/*case ITEM_BANANA:
	{
		b2Vec2 pos(x, y);
		Item* newItem = new Item(ItemType::BANANA, pos);
		items.add(newItem);
		allEntities.add(newItem);
		newItem->Start();
		newItem->SetID(all_ids);
		all_ids++;

		break;
	} */
	//case ROCKET_BANANA:
	//{
	//	b2Vec2 pos(x, y);
	//	RocketBanana* newRocket = new RocketBanana(pos, 1);
	//	
	//	rockets.add(newRocket);
	//	allEntities.add(newRocket);
	//	newRocket->Start();
	//	newRocket->SetID(all_ids);
	//	all_ids++;
	//	break;
	//} 
	//	
	default:
		break;
	}

	//LOG("Entity Created");
}

bool EntityHandler::Update(float dt)
{
	srand(time(0));

	for (int i = 0; i < allEntities.count(); i++)
	{

		Entity* entitiy;
		allEntities.at(i, entitiy);

		entitiy->Update(dt);
	}

	return true;
}

void EntityHandler::DrawAllEntities()
{
	Entity* entitiy;

	for (int i = 0; i < allEntities.count(); i++)
	{
		allEntities.at(i, entitiy);

		entitiy->Draw();
	}
}

bool EntityHandler::checkForEnemies()
{
	Entity* entitiy;

	for (int i = 0; i < allEntities.count(); i++)
	{
		allEntities.at(i, entitiy);

		if (entitiy->isEnemy)
		{
			return true;
		}
	}

	return false;
}

PhysBody* EntityHandler::GetNearestChicken(PhysBody* Character)
{
	
	p2List_item<EntityPlayer*>* chicken = app->entityHandler->players.getFirst();
	int temp = chicken->data->CheckDistanceToPhysBody(Character);

	PhysBody* NearPlayer = chicken->data->GetPhysBody();
	for (int i = 0; chicken; chicken = chicken->next)
	{
		

		int j = chicken->data->CheckDistanceToPhysBody(Character);
		if (j<temp)
		{
			temp = j;
			NearPlayer = chicken->data->GetPhysBody();
		}
	}
	return NearPlayer;
}

PhysBody* EntityHandler::GetNearestEnemy(PhysBody* Character)
{
	p2List_item<EntityEnemy*>* enemy = app->entityHandler->enemies.getFirst();
	if (enemy != NULL)
	{
		int temp = enemy->data->CheckDistanceToPhysBody(Character);

		PhysBody* NearEnemy = enemy->data->GetPhysBody();
		for (int i = 0; enemy; enemy = enemy->next)
		{


			int j = enemy->data->CheckDistanceToPhysBody(Character);
			if (j < temp)
			{
				temp = j;
				NearEnemy = enemy->data->GetPhysBody();
			}
		}
		return NearEnemy;
	}
	else return NULL;
	
}


bool EntityHandler::LoadState(pugi::xml_node& data)
{
	//DestroyAllEnemies();
	//pugi::xml_node myself = data.child("EntityHandler");

	DestroyAllEnemies();


	if (data != NULL)
	{
		pugi::xml_node prop;

		int i = 0;
		//prop = myself.child("EnemyMushroom");
		//while (prop.type() == pugi::node_element)
		//{
		//	CreateEntity(EntityType::ENEMY_MUSHROOM, 0, 0);
		//	EnemyMushroom* temp;
		//	enemiesMushroom.at(i, temp);
		//	temp->LoadState(myself);
		//	i++;
		//
		//	prop = prop.next_sibling("EnemyMushroom");
		//}

		/*for (prop = data.child("Item"); prop.type() == pugi::node_element; prop = prop.next_sibling("Item"))
		{
			CreateEntity(ITEM_BANANA, 0, 0);
			Item* ent = nullptr;
			items.at(i, ent);
			ent->LoadState(prop);

			i++;

		}*/
		i = 0;

		for (prop = data.child("chicken_idle"); prop.type() == pugi::node_element; prop = prop.next_sibling("chicken_idle"))
		{
			CreateEntity(ENTITY_PLAYER, 0, 0, 1);
			EntityPlayer* ent = nullptr;
			players.at(i, ent);
			ent->LoadState(prop);

			i++;

		}
		i = 0;

		//for (prop = data.child("EnemyBird"); prop.type() == pugi::node_element; prop = prop.next_sibling("EnemyBird"))
		//{
		//	CreateEntity(ENEMY_BIRD, 0, 0);
		//	EnemyBird* ent = nullptr;
		//	enemiesBird.at(i, ent);
		//	ent->LoadState(prop);

		//	i++;

		//}
		//i = 0;

		//for (prop = data.child("EnemyMushroom"); prop.type() == pugi::node_element; prop = prop.next_sibling("EnemyMushroom"))
		//{
		//	CreateEntity(ENEMY_MUSHROOM, 0, 0);
		//	EnemyMushroom* ent = nullptr;
		//	enemiesMushroom.at(i,ent);
		//	ent->LoadState(prop);

		//	i++;
		//
		//}
		//i = 0;

		
	}

	return true;
}


bool EntityHandler::SaveState(pugi::xml_node& data) const
{
	//pugi::xml_node myself = data.child("EntityHandler");
	//if (myself.type() != pugi::node_element)
	//{
	//	pugi::xml_node myself = data.append_child("EntityHandler");
	//
	//}

	//myself.append_attribute("MushroomCount").set_value(enemiesMushroom.count());
	//myself.append_attribute("BirdCount").set_value(enemiesBird.count());
	//myself.append_attribute("SnakeCount").set_value(enemiesSnake.count());

	pugi::xml_node iteratorRemove = data.first_child();

	while (iteratorRemove.next_sibling())
	{
		pugi::xml_node toRemove = iteratorRemove.next_sibling();
		data.remove_child(toRemove);
	}
	data.remove_child(iteratorRemove);


	for (int i = 0; i < players.count(); i++)
	{

		EntityPlayer* pl;
		players.at(i, pl);

		pl->SaveState(data);
	}

	//for (int i = 0; i < enemiesBird.count(); i++)
	//{

	//	EnemyBird* iteratorBird;
	//	enemiesBird.at(i, iteratorBird);

	//	iteratorBird->SaveState(data);
	//}

	//for (int i = 0; i < enemiesSnake.count(); i++)
	//{

	//	EnemySnake* iteratorSnake;
	//	enemiesSnake.at(i, iteratorSnake);

	//	iteratorSnake->SaveState(data);
	//}

	//for (int i = 0; i < items.count(); i++)
	//{

	//	Item* it;
	//	items.at(i, it);

	//	it->SaveState(data);
	//}
	return true;
}


void EntityHandler::DestroyEnemy(b2Body* body)
{

	
	for (p2List_item<EntityEnemy*>* dummy = enemies.getFirst(); dummy; dummy = dummy->next)
	{


		if (dummy->data->GetPhysBody()->body == body)
		{
			enemies.del(dummy);
			p2List_item<Entity*>* eToDelete = allEntities.findNode(dummy->data);
			allEntities.del(eToDelete);

			app->physics->GetWorld()->DestroyBody(body);

		}
		
	}
}

void EntityHandler::DestroyPlayer(b2Body* body)
{
	if (players.getFirst() != NULL)
	{
		for (p2List_item<EntityPlayer*>* dummy = players.getFirst(); dummy; dummy = dummy->next)	
		{


			if (dummy->data->GetPhysBody()->body == body)
			{
				players.del(dummy);
				p2List_item<Entity*>* eToDelete = allEntities.findNode(dummy->data);
				allEntities.del(eToDelete);

				app->physics->GetWorld()->DestroyBody(body);

			}
		}
	}
}

EntityType EntityHandler::GetEntityType(b2Body* body) const
{
	bool cont = false;


	//p2List_item<EnemyMushroom*>* mushroom = enemiesMushroom.getFirst();
	//for (int i = 0; i < enemiesMushroom.count(); i++)
	//{
	//	//LOG("n: %i", enemiesMushroom.count());
	//	if (cont) break;
	//	EnemyMushroom* iteratorMushroom;
	//	enemiesMushroom.at(i, iteratorMushroom);



	//	if (iteratorMushroom->GetPhysBody()->body == body)
	//	{
	//		return ENEMY_MUSHROOM;
	//		cont = true;
	//	}
	//	else
	//		mushroom = mushroom->next;
	//}

	//p2List_item<EnemyBird*>* bird = enemiesBird.getFirst();

	//for (int i = 0; i < enemiesBird.count(); i++)
	//{
	//	if (cont) break;

	//	EnemyBird* iteratorBird;
	//	enemiesBird.at(i, iteratorBird);


	//	if (iteratorBird->GetPhysBody()->body == body)
	//	{
	//		return ENEMY_BIRD;
	//		cont = true;

	//	}
	//	else
	//		bird = bird->next;
	//}


	//p2List_item<EnemySnake*>* snake = enemiesSnake.getFirst();
	//for (int i = 0; i < enemiesSnake.count(); i++)
	//{
	//	if (cont) break;

	//	EnemySnake* iteratorSnake;
	//	enemiesSnake.at(i, iteratorSnake);

	//	if (iteratorSnake->GetPhysBody()->body == body)
	//	{
	//		return ENEMY_SNAKE;
	//		cont = true;

	//	}
	//	else
	//		snake = snake->next;
	//}

	//p2List_item<RocketBanana*>* rocket = rockets.getFirst();
	//for (int i = 0; i < rockets.count(); i++)
	//{
	//	if (cont) break;

	//	RocketBanana* iteratorRocket;
	//	rockets.at(i, iteratorRocket);


	//	if (iteratorRocket->GetPhysBody()->body == body)
	//	{
	//		return ROCKET_BANANA;
	//		cont = true;
	//	}
	//	else
	//		rocket = rocket->next;
	//}
/*
	p2List_item<Item*>* it = items.getFirst();
	for (int i = 0; i < items.count(); i++)
	{
		if (cont) break;

		Item* item;
		items.at(i, item);


		if (item->GetPhysBody()->body == body)
		{
			return ITEM_BANANA;
			cont = true;
		}
		else
			it = it->next;
	}

	return ENTITY_NULL;
}
*/
//void EntityHandler::DamageEnemy(b2Body* body, int damage)
//{
//
//	bool cont = false;
//
//	
//	for (int i = 0; i < enemiesMushroom.count(); i++)
//	{
//		if (cont) break;
//		EnemyMushroom* iteratorMushroom;
//		enemiesMushroom.at(i, iteratorMushroom);
//
//
//
//		if (iteratorMushroom->GetPhysBody()->body == body)
//		{
//			LOG("found type");	iteratorMushroom->DoDamage(damage);
//			cont = true;
//		}
//	}
//
//
//	for (int i = 0; i < enemiesBird.count(); i++)
//	{
//		if (cont) break;
//
//		EnemyBird* iteratorBird;
//		enemiesBird.at(i, iteratorBird);
//
//
//
//		if (iteratorBird->GetPhysBody()->body == body)
//		{
//			LOG("found type"); 
//			iteratorBird->DoDamage(damage);
//			cont = true;
//		}
//	}
//
//
//
//	for (int i = 0; i < enemiesSnake.count(); i++)
//	{
//		if (cont) break;
//
//		EnemySnake* iteratorSnake;
//		enemiesSnake.at(i, iteratorSnake);
//
//		if (iteratorSnake->GetPhysBody()->body == body)
//		{
//			LOG("found type");
//			iteratorSnake->DoDamage(damage);
//			cont = true;
//		}
//	}
//
//	for (int i = 0; i < rockets.count(); i++)
//	{
//		if (cont) break;
//
//		RocketBanana* iteratorRocket;
//		rockets.at(i, iteratorRocket);
//
//		if (iteratorRocket->GetPhysBody()->body == body)
//		{
//			LOG("found type");
//			iteratorRocket->DoDamage(damage);
//			cont = true;
//		}
//	}
//}

//void EntityHandler::HandleEnemyDespawn()
//{

	//for (int i = 0; i < enemiesMushroom.count(); i++)
	//{

	//	EnemyMushroom* iteratorMushroom;
	//	enemiesMushroom.at(i, iteratorMushroom);

	//	if (PhysBodyIsInMap(iteratorMushroom->GetPhysBody())) 
	//		DestroyEnemy(iteratorMushroom->GetPhysBody()->body);
	//}

	//for (int i = 0; i < enemiesBird.count(); i++)
	//{

	//	EnemyBird* iteratorBird;
	//	enemiesBird.at(i, iteratorBird);

	//	if (PhysBodyIsInMap(iteratorBird->GetPhysBody()))
	//		DestroyEnemy(iteratorBird->GetPhysBody()->body);
	//}

	//for (int i = 0; i < enemiesSnake.count(); i++)
	//{

	//	EnemySnake* iteratorSnake;
	//	enemiesSnake.at(i, iteratorSnake);

	//	if (PhysBodyIsInMap(iteratorSnake->GetPhysBody()))
	//		DestroyEnemy(iteratorSnake->GetPhysBody()->body);
	//}
	//for (int i = 0; i < rockets.count(); i++)
	//{

	//	RocketBanana* iteratorRocket;
	//	rockets.at(i, iteratorRocket);

	//	if (PhysBodyIsInMap(iteratorRocket->GetPhysBody()))
	//		DestroyEnemy(iteratorRocket->GetPhysBody()->body);
return EntityType();
	//}
}


void EntityHandler::DestroyAllEnemies()
{
	int a = 0;
	/*a = enemiesMushroom.count();
	for (int i = a; i > 0; i--)
	{

		EnemyMushroom* iteratorMushroom;
		bool ret = enemiesMushroom.at(i - 1, iteratorMushroom);
		
		DestroyEnemy(iteratorMushroom->GetPhysBody()->body);
	}

	a = enemiesBird.count();
	for (int i = a; i > 0; i--)
	{

		EnemyBird* iteratorBird;
		enemiesBird.at(i - 1, iteratorBird);
		
		DestroyEnemy(iteratorBird->GetPhysBody()->body);
	}

	a = enemiesSnake.count();
	for (int i = a; i > 0; i--)
	{

		EnemySnake* iteratorSnake;
		enemiesSnake.at(i - 1, iteratorSnake);
		
		DestroyEnemy(iteratorSnake->GetPhysBody()->body);
	}

	a = rockets.count();
	for (int i = a; i > 0; i--)
	{

		RocketBanana* iteratorRocket;
		rockets.at(i - 1, iteratorRocket);

		DestroyEnemy(iteratorRocket->GetPhysBody()->body);
	}*/

	a = items.count();
	for (int i = a; i > 0; i--)
	{

		Item* it;
		items.at(i - 1, it);

		DestroyEnemy(it->GetPhysBody()->body);
	}

}

void EntityHandler::OrderBySpeed()
{
	MergeSort(allEntities.getFirst());

}

void EntityHandler::StartCombat()
{
	OrderBySpeed();

	int turn = false;
	for (p2List_item<Entity*>* node = allEntities.getFirst(); node; node = node->next)
	{
		if (turn)
		{
			node->data->state = STATE_WAIT;

		}
		else
		{
			node->data->state = STATE_TURN;
			app->render->follow = node->next->data;
			turn = true;
		}
	}
}

void EntityHandler::NextTurn(PhysBody* finished)
{
	
	for (p2List_item<Entity*>* node = allEntities.getFirst(); node; node = node->next)
	{
		if (node->data->Hitbox == finished)
		{
			node->data->state = STATE_WAIT;
			if (node->next != NULL)
			{
				node->next->data->state = STATE_TURN;
				app->render->follow = node->next->data;
			}
			else
			{
				allEntities.getFirst()->data->state = STATE_TURN;
				app->render->follow = allEntities.getFirst()->data;
			}
		}
	}
}

