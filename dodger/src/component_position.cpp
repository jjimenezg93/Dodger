#include "../include/component_position.h"
#include "../include/component_render.h"
#include "../include/entity.h"
#include "../include/messages.h"

#include "../../include/screen.h"

ComponentPosition::ComponentPosition(Entity * et, float x, float y) {
	m_owner = et;
	m_x = x;
	m_y = y;
}

/* ElapsedTime should be passed as parameter for low coupling, but then it should probably
come from Entity */
void ComponentPosition::ReceiveMessage(Message * msg) {
	UpdatePositionMessage * posMsg = dynamic_cast<UpdatePositionMessage *>(msg);
	if (posMsg) {
		m_x += posMsg->m_x * Screen::Instance().ElapsedTime();
		m_y += posMsg->m_y * Screen::Instance().ElapsedTime();
	}
}

void ComponentPosition::Update() {
	m_owner->ReceiveMessage(new UpdateSpriteMessage(m_x, m_y));
}