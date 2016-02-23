#include "../include/component_render.h"
#include "../../include/sprite.h"

ComponentRender::ComponentRender(Entity * et, Sprite * sprt) {
	m_owner = et;
	m_sprite = sprt;
}

void ComponentRender::ReceiveMessage(Message * msg) {
	UpdatePosMessage * posMsg = dynamic_cast<UpdatePosMessage *>(msg);
	if (posMsg) {
		m_sprite->SetPosition(posMsg->x, posMsg->y);
	}
}

void ComponentRender::Update() {
	//m_owner->GetSprite()->Render();
}