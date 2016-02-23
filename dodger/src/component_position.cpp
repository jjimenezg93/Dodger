#include "../include/component_position.h"

ComponentPosition::ComponentPosition(Entity * et, Sprite * sprt) {
	m_owner = et;
}

void ComponentPosition::ReceiveMessage(Message * msg) {
	
}

void ComponentPosition::Update() {
	//m_owner->GetSprite()->Render();
}