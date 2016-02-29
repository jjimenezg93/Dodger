#pragma warning(disable: 4061)
//ET_NUM_COLORS not explicitly handled (GetImageByEntityType -> switch-case)

#include "../include/component_collision.h"
#include "../include/component_playercontrol.h"
#include "../include/component_position.h"
#include "../include/component_random_movement.h"
#include "../include/component_render.h"
#include "../include/entity.h"
#include "../include/game.h"
#include "../include/game_Settings.h"
#include "../include/messages.h"
#include "../include/player.h"
#include "../include/world.h"

#include "../../include/u-gine.h"

CollisionPixelData * GetCollisionPixelData(const Entity &et);
double genRandomF(double min, double max);
Image * GetImageByEntityType(EDodgerEntityType et);

//no need to use an int but Array.ToInt() returns int
World::World(const String background, int id, int maxCollid, int initSpeed) {
	m_id = id;
	m_maxCollidables = maxCollid;
	m_worldSpeed = initSpeed;

	m_scene = new Scene(ResourceManager::Instance().LoadImage(background));

	m_player = nullptr;

}

World::~World() {
	ResourceManager::Instance().FreeResources();
	for (unsigned short int i = 0; i < m_entities.Size(); i++) {
		delete m_entities[i];
	}
}

void World::Run() {
	if (!m_player) {
		Image * playerImg = ResourceManager::Instance().LoadImage(String(PLAYER_FILENAME));
		Sprite * playerSprt = m_scene->CreateSprite(playerImg);
		playerSprt->SetCollision(Sprite::CollisionMode::COLLISION_RECT);
		playerSprt->SetCollisionPixelData(
			ResourceManager::Instance().LoadCollisionPixelData(PLAYER_COLLISION_FILENAME));
		playerSprt->SetCollision(Sprite::CollisionMode::COLLISION_PIXEL);
		m_player = new Entity(EDET_PLAYER);
		m_player->AddComponent(new ComponentPlayerControl(m_player));
		m_player->AddComponent(new ComponentPosition(m_player,
			static_cast<float>(genRandomF(SPAWN_BORDER,
				Screen::Instance().GetWidth() - SPAWN_BORDER)),
			static_cast<float>(genRandomF(SPAWN_BORDER,
				Screen::Instance().GetHeight() - SPAWN_BORDER))));
		m_player->AddComponent(new ComponentRender(m_player, playerSprt));
		m_player->AddComponent(new ComponentCollision(m_player, playerSprt));
		m_player->Update(Screen::Instance().ElapsedTime());
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

	m_scene->Update(Screen::Instance().ElapsedTime());

	for (unsigned short int i = 0; i < m_entities.Size(); i++) {
		if (m_entities[i]->GetType() != EDET_PLAYER) {
			IsCollisionMessage isColMsg(m_entities[i]);
			m_player->ReceiveMessage(&isColMsg);
			
			if (isColMsg.m_collided) {
				if (m_entities[i]->GetType() == EDET_ENEMY)
					GSetWantedState(EDAS_GAME_OVER);
				else if (m_entities[i]->GetType() == EDET_POINTS) {
					g_game->AddPoints(POINT_RATE);
					DespawnEntity(i);
					continue;
				} else if (m_entities[i]->GetType() == EDET_SUB_SPEED) {
					m_worldSpeed -= WORLD_SPEED_RATE;
					DespawnEntity(i);
					continue;
				} else if (m_entities[i]->GetType() == EDET_ADD_SPEED) {
					m_worldSpeed += WORLD_SPEED_RATE;
					DespawnEntity(i);
					continue;
				}
			}
		}
		m_entities[i]->Update(Screen::Instance().ElapsedTime());
	}
}

void World::Draw() {
	m_scene->Render();
	Screen::Instance().Refresh();
}

Entity * World::RandomSpawnEntity() {
	EDodgerEntityType e = RandomGenEntityType();

	Sprite * sprt = m_scene->CreateSprite(GetImageByEntityType(e));
	sprt->SetCollision(Sprite::CollisionMode::COLLISION_RECT);
	Entity * entity = new Entity(e);
	
	/* not all sprites should have pixel collision, the best solution would be having a manager
	to decide if collision must be circ, rect or pixel, or get it from file, but this solution
	is easier to implement for now */
	sprt->SetCollisionPixelData(GetCollisionPixelData(*entity));
	sprt->SetCollision(Sprite::CollisionMode::COLLISION_PIXEL);

	ComponentPosition * posComp = new ComponentPosition(entity,
		static_cast<float>(genRandomF(SPAWN_BORDER,
			Screen::Instance().GetWidth() - SPAWN_BORDER)),
		static_cast<float>(genRandomF(SPAWN_BORDER,
			Screen::Instance().GetHeight() - SPAWN_BORDER)));
	entity->AddComponent(posComp);

	//RANDOM MOVEMENT COMPONENT

	ComponentRender * renderComp = new ComponentRender(entity, sprt);
	entity->AddComponent(renderComp);

	ComponentCollision * colComp = new ComponentCollision(m_player, sprt);
	entity->AddComponent(colComp);

	ComponentRandomMovement * randMovComp = new ComponentRandomMovement(entity, 1, 1);
	entity->AddComponent(randMovComp);

	entity->Update(Screen::Instance().ElapsedTime());

	return entity;
}

CollisionPixelData * GetCollisionPixelData(const Entity &et) {
	CollisionPixelData * colPixelData = nullptr;
	switch (et.GetType()) {
	case EDET_POINTS:
		return colPixelData = ResourceManager::Instance().LoadCollisionPixelData(
			POINTS_COLLISION_FILENAME);
		break;
	case EDET_ENEMY:
		return colPixelData = ResourceManager::Instance().LoadCollisionPixelData(
			ENEMY_COLLISION_FILENAME);
		break;
	case EDET_ADD_SPEED:
		return colPixelData = ResourceManager::Instance().LoadCollisionPixelData(
			ADD_SPEED_COLLISION_FILENAME);
		break;
	case EDET_SUB_SPEED:
		return colPixelData = ResourceManager::Instance().LoadCollisionPixelData(
			SUB_SPEED_COLLISION_FILENAME);
		break;
	default:
		break;
	}
}

void World::DespawnEntity(unsigned int pos) {
	GetSpriteMessage sprtMsg(nullptr);
	m_entities[pos]->ReceiveMessage(&sprtMsg);

	if (sprtMsg.m_sprt) {
		m_scene->DeleteSprite(sprtMsg.m_sprt);

		delete m_entities[pos];

		//having a negative index makes no sense here, but Array is implemented this way
		m_entities.RemoveAt(static_cast<int>(pos));
	}
}

EDodgerEntityType World::RandomGenEntityType() {
	EDodgerEntityType e = (EDodgerEntityType)(unsigned short int)(genRandomF(1, EDET_NUM_COLORS));
	return e;
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