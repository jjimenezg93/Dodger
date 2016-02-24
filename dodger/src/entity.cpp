#include "../include/entity.h"
#include "../include/world.h"
#include "../include/component.h"
#include "../include/messages.h"

Entity::Entity(double x, double y, short int dirX, short int dirY, EDodgerEntityType type = EDET_POINTS) {
	if (dirX == 0)
		m_speedX = g_game->GetWorldSpeed();
	else
		m_speedX = g_game->GetWorldSpeed() * dirX;
	if (dirY == 0)
		m_speedY = g_game->GetWorldSpeed();
	else
		m_speedY = g_game->GetWorldSpeed() * dirY;

	m_type = type;
}

Entity::~Entity() {}

void Entity::AddComponent(Component * comp) {
	m_components.insert(m_components.end(), comp);
}

void Entity::ReceiveMessage(Message * msg) {
	for (std::vector<Component *>::iterator it = m_components.begin();
			it != m_components.end(); it++) {
		(*it)->ReceiveMessage(msg);
	}
}

void Entity::Update() {
	for (std::vector<Component *>::iterator it = m_components.begin();
			it != m_components.end(); it++) {
		(*it)->Update();
	}
}