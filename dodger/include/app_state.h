#ifndef _APP_STATE_H
#define _APP_STATE_H

enum EDodgerAppState {
	EDAS_NULL, 
	EDAS_CHOOSE_LANG,
	EDAS_START_MENU,
	EDAS_GAME,
	EDAS_GAME_OVER,
	EDAS_EXIT_APP
};

class AppState {
public:
	virtual ~AppState() {};

	virtual void Run() = 0;
	virtual void Draw() = 0;
	virtual void ProcessInput() = 0;
	virtual void Activate() = 0;
	virtual void Deactivate() = 0;		//used to unset variables before destructor (both members and globals) if needed
};

AppState * newAppState(EDodgerAppState wanted);

#endif //!_APP_STATE_H