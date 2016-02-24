#ifndef _MESSAGES_H
#define _MESSAGES_H

enum EDodgerPlayerControlKey { EDPC_LEFT, EDPC_RIGHT, EDPC_UP, EDPC_DOWN };

struct Message {
	virtual ~Message() {}
};

struct PlayerControlMessage: public Message {
	PlayerControlMessage(EDodgerPlayerControlKey key) { m_key = key; }
	EDodgerPlayerControlKey m_key;
};

struct UpdateSpriteMessage: public Message {
	UpdateSpriteMessage(float x, float y) { m_x = x; m_y = y; }
	float m_x, m_y;
};

struct UpdatePositionMessage: public Message {
	UpdatePositionMessage(float x, float y) { m_x = x; m_y = y; } //used as a relative update
	float m_x, m_y;
};

#endif //!_MESSAGES_H