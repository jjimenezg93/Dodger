#ifndef _APP_STATE_H
#define _APP_STATE_H

enum EAppState { EAS_NULL, EAS_START_MENU, EAS_GAME, EAS_GAME_OVER, EAS_EXIT_APP };

class AppState {
public:
	virtual ~AppState() {};

	virtual void Run() = 0;
	virtual void Draw() = 0;
	virtual void ProcessInput() = 0;
	virtual void Activate() = 0;
	virtual void Deactivate() = 0;		//used to unset variables (both members and globals) if needed
};

AppState * newAppState(EAppState wanted);

#endif //!_APP_STATE_H