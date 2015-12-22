#ifndef _UI_H
#define _UI_H

class World;

class UI {
public:
	UI(World *ptrWorld);

	void ProcessInput();
	void Draw();

	void SetWorld(World *ptrWorld);
private:
	World *m_world;
};

#endif	//!_UI_H