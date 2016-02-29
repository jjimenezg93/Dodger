#ifndef _MESSAGES_H
#define _MESSAGES_H

enum EDodgerPlayerControlKey { EDPC_LEFT, EDPC_RIGHT, EDPC_UP, EDPC_DOWN };

struct Message {
	virtual ~Message() {}
};

struct PlayerControlMessage: public Message {
	PlayerControlMessage(EDodgerPlayerControlKey key, float elapsed) {
		m_key = key;
		m_elapsed = elapsed;
	}
	EDodgerPlayerControlKey m_key;
	float m_elapsed;
};

struct UpdateSpritePosMessage: public Message {
	UpdateSpritePosMessage(float x, float y) { m_x = x; m_y = y; }
	float m_x, m_y;
};

struct UpdateComponentPosMessage: public Message {
	UpdateComponentPosMessage(float x, float y, float elapsed) { //used as a relative update
		m_x = x;
		m_y = y;
		m_elapsed = elapsed;
	}
	float m_x, m_y, m_elapsed;
};

struct IsCollisionMessage: public Message {
	IsCollisionMessage(Entity * et) {
		m_entity = et;
		m_collided = false;
	}
	Entity * m_entity;
	bool m_collided;
};

struct GetSpriteMessage: public Message {
	GetSpriteMessage(Sprite * sp, bool modif = false) {
		m_sprt = sp;
		m_modified = modif;
	}
	Sprite * m_sprt;
	bool m_modified;
};

//if there is a way to set the Sprite, we need this message to be called from ComponentRender
struct UpdateSpriteMessage: public Message {
	UpdateSpriteMessage(Sprite * sp) {
		m_sprt = sp;
	}
	Sprite * m_sprt;
};

#endif //!_MESSAGES_H