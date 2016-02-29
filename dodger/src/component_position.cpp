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
	UpdateComponentPosMessage * posMsg = dynamic_cast<UpdateComponentPosMessage *>(msg);
	if (posMsg) {
		m_x += posMsg->m_x * posMsg->m_elapsed;
		m_y += posMsg->m_y * posMsg->m_elapsed;
	}
}

void ComponentPosition::Update(float elapsed) {
	m_owner->ReceiveMessage(new UpdateSpritePosMessage(m_x, m_y));
}