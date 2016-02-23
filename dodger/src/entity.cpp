#include "../include/entity.h"
#include "../include/world.h"
#include "../include/component.h"

Entity::Entity(double x, double y, short int dirX, short int dirY, EDodgerEntityType type = EDET_POINTS) {
	//m_sprite = new Sprite(imgSprite);

	//m_sprite->SetX(x);
	//m_sprite->SetY(y);

	if (dirX == 0)
		m_speedX = g_game->GetWorldSpeed();
	else
		m_speedX = g_game->GetWorldSpeed() * dirX;
	if (dirY == 0)
		m_speedY = g_game->GetWorldSpeed();
	else
		m_speedY = g_game->GetWorldSpeed() * dirY;
	
	//m_sizeX = imgSprite->GetWidth();
	//m_sizeY = imgSprite->GetHeight();

	m_type = type;
}

Entity::~Entity() {
	//delete m_sprite;
}

/*void Entity::SetSprite(Image * imgSprite) {
	delete m_sprite;
	m_sprite = new Sprite(imgSprite);
}*/

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

/*void Entity::Render() {
	m_sprite->Render();
}*/