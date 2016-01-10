#include "../include/entity.h"
#include "../include/world.h"

Entity::Entity(Image * imgSprite, double x, double y, short int dirX, short int dirY, EntityType type = ET_POINTS) {
	m_sprite = new Sprite(imgSprite);

	m_sprite->SetX(x);
	m_sprite->SetY(y);

	if (dirX == 0)
		m_speedX = g_game->GetWorldSpeed();
	else
		m_speedX = g_game->GetWorldSpeed() * dirX;
	if (dirY == 0)
		m_speedY = g_game->GetWorldSpeed();
	else
		m_speedY = g_game->GetWorldSpeed() * dirY;
	
	m_sizeX = imgSprite->GetWidth();
	m_sizeY = imgSprite->GetHeight();

	m_type = type;
}

Entity::~Entity() {
	delete m_sprite;
}

void Entity::SetSprite(Image * imgSprite) {
	delete m_sprite;
	m_sprite = new Sprite(imgSprite);
}

void Entity::Render() {
	m_sprite->Render();
}