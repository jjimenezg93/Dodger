#include "../include/component_collision.h"
#include "../include/entity.h"
#include "../include/messages.h"
#include "../../include/sprite.h"

ComponentCollision::ComponentCollision(Entity * et, Sprite * sprt) {
	m_owner = et;
	m_sprite = sprt;
}

void ComponentCollision::ReceiveMessage(Message * msg) {
	IsCollisionMessage * colMsg = dynamic_cast<IsCollisionMessage *>(msg);
	if (colMsg) {
		GetSpriteMessage sprtMsg(m_sprite);
		colMsg->m_entity->ReceiveMessage(&sprtMsg);

		if (sprtMsg.m_modified) {
			colMsg->m_collided = m_sprite->CheckCollision(sprtMsg.m_sprt);
		}
	}

	UpdateSpriteMessage * updateSprtMsg = dynamic_cast<UpdateSpriteMessage *>(msg);
	if (updateSprtMsg) {
		m_sprite = updateSprtMsg->m_sprt;
	}
}

void ComponentCollision::Update(float) {}