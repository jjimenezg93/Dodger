#ifndef _APP_STATE_H
#define _APP_STATE_H

enum EAppState { AS_NULL, AS_START_MENU, AS_GAME, AS_GAME_OVER, AS_EXIT_APP };

class AppState {
public:
	virtual void Run() = 0;
	virtual void Draw() = 0;
	virtual void ProcessInput() = 0;
	virtual void Activate() = 0;
	virtual void Deactivate() = 0;
};

AppState *newAppState(EAppState wanted);

#endif //!_APP_STATE_H