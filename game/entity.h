#ifndef _ENTITY_H
#define _ENTITY_H

#include "defs.h"
#include "../include/u-gine.h"

class Entity {
public:
	Entity(Image *imgSprite, float x, float y, short int dirX, short int dirY, EntityType type);
	virtual ~Entity();

	float GetX() const { return m_sprite->GetX(); }
	float GetY() const { return m_sprite->GetY(); }
	void SetX(float x) { m_sprite->SetX(x); }
	void SetY(float y) { m_sprite->SetY(y); }

	float GetSizeX() const { return m_sizeX; }
	float GetSizeY() const { return m_sizeY; }
	void SetSizeX(float x) { m_sizeX = x; }
	void SetSizeY(float y) { m_sizeY = y; }

	float GetSpeedX() const { return m_speedX; }
	float GetSpeedY() const { return m_speedY; }
	void SetSpeedX(float x) { m_speedX = x; }
	void SetSpeedY(float y) { m_speedY = y; }

	EntityType GetType() const { return m_type; }
	void SetType(EntityType newType) { m_type = newType; }		//not in use atm

	void Render();
private:
	Sprite *m_sprite;
	float m_sizeX, m_sizeY;
	float m_speedX, m_speedY;
	EntityType m_type;
};

#endif //!_ENTITY_H