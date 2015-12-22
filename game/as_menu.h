#ifndef AS_MENU_H
#define AS_MENU_H

#include "app_state.h"

class ASMenu: public AppState {
public:
	virtual void ProcessInput();
	virtual void Run();
	virtual void Draw();
	virtual void Activate();
	virtual void Deactivate();
};

#endif //!_AS_MENU_H