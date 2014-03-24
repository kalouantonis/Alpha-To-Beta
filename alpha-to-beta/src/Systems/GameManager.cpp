#include <Systems/GameManager.h>
#include <Systems/MovementSystem.h>
#include <Systems/RenderSystem.h>

#include <Artemis/Entity.h>
#include <Artemis/SystemManager.h>
#include <Artemis/EntityManager.h>

#include <Utils/Logger.h>

// TODO: GTFO
#include <Components/Transform.h>
#include <Components/Renderable.h>
#include <Components/Physics.cpp>

GameManager::GameManager(SpriteBatch& spriteBatch)
    : WorldManager()
    , m_spriteBatch(spriteBatch)
{

}

void GameManager::initialize()
{
    // EntityFactory factory(entity_manager);
    // factory.loadFromDirectory("assets");
    artemis::SystemManager* systemManager = this->getSystemManager();

    CORE_DEBUG("Creating movement system...");

    m_movementSystem = static_cast<MovementSystem*>(
        systemManager->setSystem(new MovementSystem())
    );

    CORE_DEBUG("Creating render system...");

    m_renderSystem = static_cast<RenderSystem*>(
        systemManager->setSystem(new RenderSystem(m_spriteBatch))
    );

    systemManager->initializeAll();

    CORE_DEBUG("Loading textures...");

    m_textureHolder.load("heart", "assets/img.png");
    m_textureHolder.load("player", "assets/still1.png");

    CORE_DEBUG("Loading entities...");

    artemis::Entity& heart = this->createEntity();

    heart.addComponent(new Transform(100, 100, 32, 32));
    heart.addComponent(new Renderable(m_textureHolder.get("heart")));
    heart.addComponent(new Physics(1, 0, 2, 0));
    heart.refresh();

    artemis::Entity& player = this->createEntity();
    player.addComponent(new Transform(200, 200, 32, 32));
    player.addComponent(new Renderable(m_textureHolder.get("player")));
    player.refresh();

    artemis::Entity& hidden = this->createEntity();
    hidden.addComponent(new Transform(200, 200, 32, 32));
    hidden.refresh();

    this->deleteEntity(player);

    // entityx::Entity entity = entity_manager->create();

    // entity.assign<Transform>(100, 100, 32, 32);
    // entity.assign<Renderable>(m_textureHolder.get("heart"));
    // entity.assign<Physics>(1, 0, 2, 0);

    // entity = entity_manager->create();
    // entity.assign<Transform>(150, 150, 16, 16);
    // entity.assign<Renderable>(m_textureHolder.get("heart"));

    // entity = entity_manager->create();
    // entity.assign<Transform>(250, 250, 64, 64);
    // entity.assign<Renderable>(m_textureHolder.get("player"));

    CORE_DEBUG("Initialization complete.");
}

void GameManager::update(float delta) 
{
    WorldManager::update(delta);
	// Update movement using delta time
	// system_manager->update<MovementSystem>(dt);
    m_movementSystem->process();
}

void GameManager::render()
{
	// Call render systems
	// system_manager->update<RenderSystem>(0.0);	
    m_renderSystem->process();
}


void GameManager::dispose()
{
    CORE_DEBUG("Destroying entities...");
    // entity_manager->destroy_all();

    CORE_DEBUG("Disposing textures...");
    // m_textureHolder.clear();
}