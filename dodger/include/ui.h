#ifndef _UI_H
#define _UI_H

class World;

class UI {
public:
	UI(World * const ptrWorld);

	void ProcessInput();
	void Draw();

	void SetWorld(World * const ptrWorld); //useful if there was direct jump between levels
private:
	World * m_world;
};

#endif //!_UI_H