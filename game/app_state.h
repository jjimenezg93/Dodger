#ifndef APP_STATE_H
#define APP_STATE_H

class AppState {
public:
	virtual void Run() = 0;
	virtual void Draw() = 0;
	virtual void ProcessInput() = 0;
	virtual void Activate() = 0;
	virtual void Deactivate() = 0;
};

#endif //!_APP_STATE_H