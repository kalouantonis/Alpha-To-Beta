#include <Systems/GameManager.h>

#include <Systems/RenderSystem.h>
#include <Systems/PhysicsSystem.h>

#include <Artemis/Entity.h>
#include <Artemis/SystemManager.h>

#include <Utils/Logger.h>


#include <SFML/Window/Keyboard.hpp>

#include <Resources/ResourceDef.h>

GameManager::GameManager(SpriteBatch& spriteBatch)
    : WorldManager()
    , m_spriteBatch(spriteBatch)
{
    m_level.reset(new Level(*this));
}

void GameManager::initialize()
{
    // factory.loadFromDirectory("assets");
    artemis::SystemManager* systemManager = this->getSystemManager();

    CORE_DEBUG("Creating render system...");

    m_renderSystem = static_cast<RenderSystem*>(
        systemManager->setSystem(new RenderSystem(m_spriteBatch))
    );

    CORE_DEBUG("Creating physics system");

    m_physicsSystem = static_cast<PhysicsSystem*>(
        systemManager->setSystem(new PhysicsSystem(sf::Vector2f(0, -9.81f)))
    );

    CORE_DEBUG("Initializing all systems...");

    systemManager->initializeAll();

    CORE_DEBUG("Loading entities...");

    m_level->load("assets/levels/level1.xml");

    CORE_DEBUG("Initialization complete.");
}

void GameManager::update(float delta) 
{
    WorldManager::update(delta);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F5))
    {
        // Clear textures
        //TextureLocator::getObject()->clear();
        m_level->reload();
    }
}

void GameManager::render()
{
	// Call render systems
    m_renderSystem->process();
}


GameManager::~GameManager()
{
}
