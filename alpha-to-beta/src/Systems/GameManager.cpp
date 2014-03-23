#include <Systems/GameManager.h>
#include <Systems/MovementSystem.h>
#include <Systems/RenderSystem.h>

#include <Entities/EntityFactory.h>

#include <Utils/Logger.h>

// TODO: GTFO
#include <Components/Transform.h>
#include <Components/Renderable.h>
#include <Components/Physics.cpp>

GameManager::GameManager(SpriteBatch& spriteBatch)
    : m_spriteBatch(spriteBatch)
{

}

void GameManager::configure() 
{
	system_manager->add<MovementSystem>();
	system_manager->add<RenderSystem>(m_spriteBatch);
}

void GameManager::initialize()
{
    EntityFactory factory(entity_manager);
    factory.loadFromDirectory("assets");

    m_textureHolder.load("heart", "assets/img.png");
    m_textureHolder.load("player", "assets/still1.png");

    CORE_DEBUG("Loaded textures...");

    CORE_DEBUG("Loading entities...");

    entityx::Entity entity = entity_manager->create();

    entity.assign<Transform>(100, 100, 32, 32);
    entity.assign<Renderable>(m_textureHolder.get("heart"));
    entity.assign<Physics>(1, 0, 2, 0);

    entity = entity_manager->create();
    entity.assign<Transform>(150, 150, 16, 16);
    entity.assign<Renderable>(m_textureHolder.get("heart"));

    entity = entity_manager->create();
    entity.assign<Transform>(250, 250, 64, 64);
    entity.assign<Renderable>(m_textureHolder.get("player"));

    CORE_DEBUG("Initialization complete.");
}

void GameManager::update(float dt) 
{
	// Update movement using delta time
	system_manager->update<MovementSystem>(dt);
}

void GameManager::render()
{
	// Call render systems
	system_manager->update<RenderSystem>(0.0);	
}


void GameManager::dispose()
{
    CORE_DEBUG("Destroying entities...");
    entity_manager->destroy_all();

    CORE_DEBUG("Disposing textures...");
    m_textureHolder.clear();
}