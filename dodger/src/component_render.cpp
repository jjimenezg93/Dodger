#include "../include/component_render.h"
#include "../../include/sprite.h"
#include "../include/messages.h"

ComponentRender::ComponentRender(Entity * et, Sprite * sprt) {
	m_owner = et;
	m_sprite = sprt;
}

void ComponentRender::ReceiveMessage(Message * msg) {
	UpdateSpriteMessage * posMsg = dynamic_cast<UpdateSpriteMessage *>(msg);
	if (posMsg) {
		m_sprite->SetPosition(posMsg->m_x, posMsg->m_y);
	}
}

void ComponentRender::Update() {
	
}