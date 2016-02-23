#pragma warning(disable: 4061)	//ET_NUM_COLORS not explicitly handled (GetImageByEntityType -> switch-case)

#include "../include/component_render.h"
#include "../include/entity.h"
#include "../include/game.h"
#include "../include/game_Settings.h"
#include "../include/player.h"
#include "../include/world.h"

#include "../../include/u-gine.h"

double genRandomF(double min, double max);
Image * GetImageByEntityType(EDodgerEntityType et);

World::World(const String background, int id, int maxCollid, int initSpeed) {		//no need to use an int but Array.ToInt() returns int
	m_id = id;
	m_maxCollidables = maxCollid;
	m_worldSpeed = initSpeed;

	m_scene = new Scene(ResourceManager::Instance().LoadImage(background));

	m_player = nullptr;
}

World::~World() {
	for (unsigned short int i = 0; i < m_entities.Size(); i++) {
		delete m_entities[i];
	}

	ResourceManager::Instance().FreeResources();
}

void World::Run() {
	if (!m_player) {
		Image * playerImg = ResourceManager::Instance().LoadImage(String(PLAYER_FILENAME));
		Sprite * playerSprt = new Sprite(playerImg);
		m_player = new Player(0, 0, 1, 1);
		m_player->AddComponent(new ComponentRender(m_player, playerSprt));
		m_entities.Add(m_player);
	}

	if (m_entities.Size() <= static_cast<unsigned int>(m_maxCollidables))
		if (g_game->GetRandomGen() % 10 == 0)
			m_entities.Add(RandomSpawnEntity());

	if (!g_game->GetRandomGen()) {		//very rarely despawn an entity
		int entityToDelete = static_cast<int>(genRandomF(0, m_entities.Size()));

		if (m_entities[entityToDelete]->GetType() == EDET_PLAYER) {
			delete m_entities[static_cast<unsigned int>(entityToDelete)];
			m_entities.RemoveAt(entityToDelete);
		}
	}

	for (unsigned short int i = 0; i < m_entities.Size(); i++) {
		if (m_entities[i]->GetType() != EDET_PLAYER) {
			CheckAndUpdateEntityDirection(m_entities[i]);
			if (IsCollision(m_player, m_entities[i])) {
				if (m_entities[i]->GetType() == EDET_ENEMY)
					GSetWantedState(EDAS_GAME_OVER);
				else if (m_entities[i]->GetType() == EDET_POINTS) {
					g_game->AddPoints(POINT_RATE);
					DespawnEntity(i);
					continue;
				} else if (m_entities[i]->GetType() == EDET_SUB_SPEED) {
					m_worldSpeed -= SPEED_RATE;
					DespawnEntity(i);
					continue;
				} else if (m_entities[i]->GetType() == EDET_ADD_SPEED) {
					m_worldSpeed += SPEED_RATE;
					DespawnEntity(i);
					continue;
				}
			}

			/*m_entities[i]->SetX(m_entities[i]->GetX() + (m_entities[i]->GetSpeedX() * m_worldSpeed) * Screen::Instance().ElapsedTime());
			m_entities[i]->SetY(m_entities[i]->GetY() + (m_entities[i]->GetSpeedY() * m_worldSpeed) * Screen::Instance().ElapsedTime());*/
		}
		m_entities[i]->Update();
	}
}

void World::Draw() {
	m_scene->Render();
	Screen::Instance().Refresh();
}

/*void World::MoveLeft() {
	m_player->MoveLeft(Screen::Instance().ElapsedTime());
}

void World::MoveRight() {
	m_player->MoveRight(Screen::Instance().ElapsedTime());
}

void World::MoveUp() {
	m_player->MoveUp(Screen::Instance().ElapsedTime());
}

void World::MoveDown() {
	m_player->MoveDown(Screen::Instance().ElapsedTime());
}*/

bool World::IsCollision(Entity * ra, Entity * rb) {
	bool ret = false;

	/*if (ra->GetX() + ra->GetSizeX() >= rb->GetX() && ra->GetX() <= rb->GetX() + rb->GetSizeX()
		&& ra->GetY() + ra->GetSizeY() >= rb->GetY() && ra->GetY() <= rb->GetY() + rb->GetSizeY())
		ret = true;

	if (rb->GetX() >= ra->GetX() && rb->GetX() <= ra->GetX() + ra->GetSizeX()
		&& rb->GetY() + rb->GetSizeY() >= ra->GetY() && rb->GetY() <= ra->GetY() + ra->GetSizeY())
		ret = true;*/

	return ret;
}

Entity * World::RandomSpawnEntity() {
	EDodgerEntityType e = RandomGenEntityType();

	Sprite * sprt = m_scene->CreateSprite(GetImageByEntityType(e));

	Entity * entity = new Entity(
		genRandomF(SPAWN_BORDER, Screen::Instance().GetWidth() - SPAWN_BORDER),
		genRandomF(SPAWN_BORDER, Screen::Instance().GetHeight() - SPAWN_BORDER),
		static_cast<short>(genRandomF(DIRECTION_LEFT, DIRECTION_RIGHT)),
		static_cast<short>(genRandomF(DIRECTION_LEFT, DIRECTION_RIGHT)),
		e);

	ComponentRender * renderComp = new ComponentRender(entity, sprt);

	entity->SetSpeedX(genRandomF(0.2 * DIFFICULTY, 0.8 * DIFFICULTY));
	entity->SetSpeedY(genRandomF(0.2 * DIFFICULTY, 0.8 * DIFFICULTY));
	return entity;
}

void World::DespawnEntity(unsigned int pos) {
	delete m_entities[pos];

	//having a negative index makes no sense here, but Array is implemented this way
	m_entities.RemoveAt(static_cast<int>(pos));
}

EDodgerEntityType World::RandomGenEntityType() {
	EDodgerEntityType e = (EDodgerEntityType)(unsigned short int)(genRandomF(1, EDET_NUM_COLORS));
	return e;
}

void World::CheckAndUpdateEntityDirection(Entity * entity) {
	//in all cases, x/y position is reset -> avoids bouncing
	/*if (entity->GetX() > Screen::Instance().GetWidth() - entity->GetSizeX() - BORDER_THRESHOLD) {
		entity->SetX(Screen::Instance().GetWidth() - entity->GetSizeX() - BORDER_THRESHOLD);
		entity->SetSpeedX(entity->GetSpeedX() * -1);
	} else if (entity->GetX() <= 0) {
		entity->SetX(BORDER_THRESHOLD);
		entity->SetSpeedX(entity->GetSpeedX() * -1);
	}

	if (entity->GetY() > Screen::Instance().GetHeight() - entity->GetSizeY() - BORDER_THRESHOLD) {
		entity->SetY(Screen::Instance().GetHeight() - entity->GetSizeY() - BORDER_THRESHOLD);
		entity->SetSpeedY(entity->GetSpeedY() * -1);
	} else if (entity->GetY() <= 0) {
		entity->SetY(BORDER_THRESHOLD);
		entity->SetSpeedY(entity->GetSpeedY() * -1);
	}*/
}

Image * GetImageByEntityType(EDodgerEntityType et) {
	switch (et) {
	case EDET_PLAYER:
		return ResourceManager::Instance().LoadImage(String(PLAYER_FILENAME));
		break;
	case EDET_POINTS:
		return ResourceManager::Instance().LoadImage(String(POINTS_FILENAME));
		break;
	case EDET_ENEMY:
		return ResourceManager::Instance().LoadImage(String(ENEMY_FILENAME));
		break;
	case EDET_ADD_SPEED:
		return ResourceManager::Instance().LoadImage(String(ADD_SPEED_FILENAME));
		break;
	case EDET_SUB_SPEED:
		return ResourceManager::Instance().LoadImage(String(SUB_SPEED_FILENAME));
		break;
	default:
		return nullptr;
		break;
	}
}