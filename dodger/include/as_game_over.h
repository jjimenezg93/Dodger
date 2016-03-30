#ifndef _AS_GAME_OVER_H
#define _AS_GAME_OVER_H

#pragma warning(disable: 4820)

#include "app_state.h"
#include "defs.h"
#include "../../include/u-gine.h"

struct MenuOption;

class ASGameOver : public AppState {
public:
	virtual ~ASGameOver();

	virtual void Activate();
	virtual void Deactivate();
	virtual void ProcessInput();
	virtual void Run();
	virtual void Draw();
private:
	void RestartKeyElapsed();

	Image * m_imgBackground;
	Font * m_mainFont;

	Array<MenuOption *> m_menuOptions;
	uint8 m_activeOption;

	double m_elapsedKeyInput;
	bool m_canInput;
};

#endif //!_AS_GAME_OVER_H