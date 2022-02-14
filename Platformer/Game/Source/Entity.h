#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Module.h"
#include "Defs.h"
#include "Physics.h"
#include "p2Point.h"

class PhysBody;

class Entity : public Module
{
public:
	Entity() 
	{
		
	}

	~Entity()
	{}

	void SetID(int id)
	{
		this->id = id;
	}

	int Id() const
	{
		return id;
	}

	bool isEnemy = false;
	
	virtual void Draw()
	{

	}

	virtual void DrawUI()
	{

	}

	virtual iPoint GetMapPosition()
	{
		iPoint ret = { 0,0 };
		return ret;
	}

	PhysBody* last_damaged;
	PhysBody* Hitbox = nullptr;
	Stats entity_stats;
	EntityState state;
	int totalHealth;

	
private:

protected:

	int id;
};






#endif // !__ENTITY_H__
