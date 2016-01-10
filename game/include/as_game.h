#ifndef _AS_GAME_H
#define _AS_GAME_H

#include "app_state.h"

class ASGame: public AppState {
public:
	virtual ~ASGame();

	virtual void Activate();
	virtual void Deactivate();
	virtual void ProcessInput();
	virtual void Run();
	virtual void Draw();
};

#endif //!_AS_GAME_H