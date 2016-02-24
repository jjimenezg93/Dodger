#include "../include/component_playercontrol.h"
#include "../include/component_position.h"
#include "../include/component_render.h"
#include "../include/entity.h"
#include "../include/game_settings.h"
#include "../include/messages.h"

ComponentPlayerControl::ComponentPlayerControl(Entity * et) {
	m_owner = et;
}

void ComponentPlayerControl::ReceiveMessage(Message * msg) {
	PlayerControlMessage * posMsg = dynamic_cast<PlayerControlMessage *>(msg);
	if (posMsg) {
		switch (posMsg->m_key) {
		case EDPC_LEFT:
			m_owner->ReceiveMessage(new UpdatePositionMessage(-SPEED_RATE, 0));
			break;
		case EDPC_RIGHT:
			m_owner->ReceiveMessage(new UpdatePositionMessage(SPEED_RATE, 0));
			break;
		case EDPC_UP:
			m_owner->ReceiveMessage(new UpdatePositionMessage(0, -SPEED_RATE));
			break;
		case EDPC_DOWN:
			m_owner->ReceiveMessage(new UpdatePositionMessage(0, SPEED_RATE));
			break;
		default:
			break;

		}
	}
}

void ComponentPlayerControl::Update() {
	
}