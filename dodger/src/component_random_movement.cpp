#include "../include/component_random_movement.h"
#include "../include/component_position.h"
#include "../include/defs.h"
#include "../include/entity.h"
#include "../include/messages.h"
#include "../include/game_settings.h"

#define MIN_CHANGE_DIRECTION_TIME 0.05

ComponentRandomMovement::ComponentRandomMovement(Entity * et, int dirX = 1, int dirY = 1) {
	m_owner = et;
	m_dirX = dirX;
	m_dirY = dirY;
	m_lastChangeX = 0;
	m_lastChangeY = 0;
}

void ComponentRandomMovement::ReceiveMessage(Message * msg) {
	ChangeMovementDirection * changeMsg = dynamic_cast<ChangeMovementDirection *>(msg);
	if (changeMsg) {
		if (changeMsg->m_changeX && m_lastChangeX > MIN_CHANGE_DIRECTION_TIME) {
			if (m_dirX == 1)
				m_dirX = -1;
			else
				m_dirX = 1;
			m_lastChangeX = 0;
		}
		
		if (changeMsg->m_changeY && m_lastChangeY > MIN_CHANGE_DIRECTION_TIME) {
			if (m_dirY == 1)
				m_dirY = -1;
			else
				m_dirY = 1;
			m_lastChangeY = 0;
		}
	}
}

void ComponentRandomMovement::Update(float elapsed) {
	m_lastChangeX += elapsed;
	m_lastChangeY += elapsed;

	UpdateComponentPosMessage posMsg(g_game->GetWorldSpeed() * m_dirX,
		g_game->GetWorldSpeed() * m_dirY, elapsed);
	m_owner->ReceiveMessage(&posMsg);
}
