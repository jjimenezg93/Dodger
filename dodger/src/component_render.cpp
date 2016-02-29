#include "../include/component_render.h"
#include "../../include/sprite.h"
#include "../include/messages.h"

ComponentRender::ComponentRender(Entity * et, Sprite * sprt) {
	m_owner = et;
	m_sprite = sprt;
}

void ComponentRender::ReceiveMessage(Message * msg) {
	UpdateSpritePosMessage * posMsg = dynamic_cast<UpdateSpritePosMessage *>(msg);
	if (posMsg) {
		m_sprite->SetPosition(posMsg->m_x, posMsg->m_y);
	}
	GetSpriteMessage * sprtMsg = dynamic_cast<GetSpriteMessage *>(msg);
	if (sprtMsg) {
		sprtMsg->m_sprt = m_sprite;
		sprtMsg->m_modified = true;
	}
}

void ComponentRender::Update(float elapsed) {
	
}