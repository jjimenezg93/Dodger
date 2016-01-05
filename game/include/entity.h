#ifndef _ENTITY_H
#define _ENTITY_H

#pragma warning(disable: 4820)

#include "defs.h"
#include "../../include/u-gine.h"

class Entity {
public:
	Entity(Image *imgSprite, double x, double y, short int dirX, short int dirY, EntityType type);
	virtual ~Entity();

	virtual Sprite * GetSprite() const { return m_sprite; }
	virtual void SetSprite(Image *imgSprite);

	virtual double GetX() const { return m_sprite->GetX(); }
	virtual double GetY() const { return m_sprite->GetY(); }
	virtual void SetX(double x) { m_sprite->SetX(x); }
	virtual void SetY(double y) { m_sprite->SetY(y); }

	//size functions not in use atm -> needed for resizing, animating, etc
	virtual double GetSizeX() const { return m_sizeX; }
	virtual double GetSizeY() const { return m_sizeY; }
	virtual void SetSizeX(float x) { m_sizeX = x; }
	virtual void SetSizeY(float y) { m_sizeY = y; }

	virtual double GetSpeedX() const { return m_speedX; }
	virtual double GetSpeedY() const { return m_speedY; }
	virtual void SetSpeedX(double x) { m_speedX = x; }
	virtual void SetSpeedY(double y) { m_speedY = y; }

	virtual EntityType GetType() const { return m_type; }
	virtual void SetType(EntityType newType) { m_type = newType; }		//not in use atm

	virtual void Render();	//virtual -> different entities may need different kind of animations
private:
	Sprite *m_sprite;
	double m_sizeX, m_sizeY;
	double m_speedX, m_speedY;
	EntityType m_type;
};

#endif //!_ENTITY_H