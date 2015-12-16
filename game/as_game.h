#ifndef AS_GAME_H
#define AS_GAME_H

#include "app_state.h"

class ASGame: public AppState {
public:
	virtual void Activate();
	virtual void ProcessInput();
	virtual void Run();
	virtual void Draw();
	virtual void Deactivate();
};

#endif //!_AS_GAME_H