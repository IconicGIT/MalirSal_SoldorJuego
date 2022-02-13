#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Module.h"
#include "Defs.h"
#include "Physics.h"

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

	};

	virtual void DrawUI()
	{

	};
	PhysBody* last_damaged;
	PhysBody* Hitbox;
	Stats entity_stats;
	EntityState state;
	int totalHealth;
	Condition enemy_cond = COND_IDLE;
private:

protected:

	int id;

	;
};






#endif // !__ENTITY_H__
