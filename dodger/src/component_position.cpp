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

void ComponentPosition::ReceiveMessage(Message * msg) {
	UpdateComponentPosMessage * posMsg = dynamic_cast<UpdateComponentPosMessage *>(msg);
	if (posMsg) {
		m_x += posMsg->m_x * posMsg->m_elapsed;
		m_y += posMsg->m_y * posMsg->m_elapsed;
	}

	GetSpritePosMessage * sprtPosMsg = dynamic_cast<GetSpritePosMessage *>(msg);
	if (sprtPosMsg) {
		sprtPosMsg->m_x = m_x;
		sprtPosMsg->m_y = m_y;
	}
}

void ComponentPosition::Update(float) {
	m_owner->ReceiveMessage(new UpdateSpritePosMessage(m_x, m_y));
}