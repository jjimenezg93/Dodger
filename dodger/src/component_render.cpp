#include "../include/component_render.h"
#include "../include/entity.h"
#include "../include/game_settings.h"
#include "../include/messages.h"
#include "../../include/image.h"
#include "../../include/screen.h"
#include "../../include/sprite.h"

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

void ComponentRender::Update(float) {
	if (m_sprite->GetX() > Screen::Instance().GetWidth()
			- m_sprite->GetImage()->GetWidth() * m_sprite->GetImage()->GetHFrames()
			- BORDER_THRESHOLD || m_sprite->GetX() <= 0) {
		ChangeMovementDirection changeXMsg(true, false);
		m_owner->ReceiveMessage(&changeXMsg);
	}

	if (m_sprite->GetY() > Screen::Instance().GetHeight()
			- m_sprite->GetImage()->GetHeight() * m_sprite->GetImage()->GetVFrames()
			- BORDER_THRESHOLD || m_sprite->GetY() <= 0) {
		ChangeMovementDirection changeYMsg(false, true);
		m_owner->ReceiveMessage(&changeYMsg);
	}
}