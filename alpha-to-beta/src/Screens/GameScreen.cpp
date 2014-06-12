#include <Screens/GameScreen.h>
#include <Utils/Logger.h>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

#include <Input/InputLocator.h>

#include <Memory/loose_ptr.h>

#include <Events/JumpListener.h>
#include <Entities/WorldLocator.h>

#include <Lua/LuaStateManager.h>

#include <Systems/RenderSystem.h>
#include <Systems/PhysicsSystem.h>
#include <Systems/PlayerInputSystem.h>
#include <Systems/CameraFollowingSystem.h>

#include <Physics/Box2DRenderer.h>
#include <Physics/PhysicsLocator.h>

#include <Resources/ResourceDef.h>

#include <Artemis/SystemManager.h>

GameScreen::GameScreen(sf::RenderTargetPtr window)
    : IScreen(window)
    , m_world(new artemis::World())
    , m_spriteBatch(window)
    , m_camera(window)
    , m_pRenderSystem(nullptr)
    , m_pPhysicsSystem(nullptr)
    , m_pInputSystem(nullptr)
    , m_pJumpListener(nullptr)
    , m_pB2Renderer(new Box2DRenderer(window))
{
}

bool GameScreen::init()
{
	TextureLocator::provide(TextureLocator::Ptr(new TextureHolder()));

	CORE_DEBUG("Creating lua state...");
	if(!LuaStateManager::create())
	{
		return false;
	}

	LuaStateManager::get()->executeString("log('Hello C++!')");

	PhysicsLocator::provide(sf::Vector2f(0, 9.81f), sf::Vector2f(70, 70));

    // TODO: Don't use temporary reference

    WorldLocator::provide(m_world);

    // Execute test file
    LuaStateManager::get()->executeFile("test.lua");

	artemis::SystemManager* systemManager = m_world->getSystemManager();

	CORE_DEBUG("Creating render system...");
	m_pRenderSystem = static_cast<RenderSystem*>(
		 systemManager->setSystem(new RenderSystem(m_spriteBatch))
	);

	//m_pRenderSystem->setWorld(&m_world);

	CORE_DEBUG("Creating physics system...");
	m_pPhysicsSystem = static_cast<PhysicsSystem*>(
		systemManager->setSystem(new PhysicsSystem())
	);

	CORE_DEBUG("Creating input system...");
	m_pInputSystem = static_cast<PlayerInputSystem*>(
		systemManager->setSystem(new PlayerInputSystem())
	);

	m_pCameraSystem = static_cast<CameraFollowingSystem*>(
		systemManager->setSystem(new CameraFollowingSystem(m_camera))
	);

	// Set input processor
	InputLocator::provide(loose_ptr(m_pInputSystem));

	CORE_DEBUG("Initializing physics renderer...");
	PhysicsLocator::getObject()->SetDebugDraw(m_pB2Renderer.get());
	m_pB2Renderer->SetFlags(Box2DRenderer::e_shapeBit);

	CORE_DEBUG("Adding listeners...");
	m_pJumpListener.reset(new JumpListener());

	CORE_DEBUG("Initializing all systems...");
	systemManager->initializeAll();

	CORE_DEBUG("Loading entities...");
	m_level.load("assets/levels/level1.xml");

	CORE_DEBUG("Resizing camera to work with physics system");
	m_camera.resize(sf::Vector2u(
		m_camera.getSize().x / PhysicsLocator::PixelsPerMeter.x,
		m_camera.getSize().y / PhysicsLocator::PixelsPerMeter.y
	));

	CORE_DEBUG("Initialization complete.");

	return true;
}

GameScreen::~GameScreen()
{
    CORE_DEBUG("Removing all entities...");
    // Clear out all entities
    m_world->getEntityManager()->removeAllEntities();
    
    CORE_DEBUG("Removing input processor...");
    InputLocator::remove();

    CORE_DEBUG("Disposing textures...");
    TextureLocator::getObject()->clear();

    CORE_DEBUG("Disposing TextureLocator...");
    TextureLocator::remove();

    CORE_DEBUG("Disposing the physics world...");
    PhysicsLocator::remove();

    CORE_DEBUG("Destroying lua state...");
    LuaStateManager::destroy();

    CORE_DEBUG("Destroying entity world...");
    WorldLocator::remove();

    CORE_DEBUG("GameScreen disposed...");
}

void GameScreen::pollInput(const sf::Event &event)
{
	if(event.type == sf::Event::MouseWheelMoved)
	{
		m_camera.zoom(event.mouseWheel.delta != 1 ? 1.1f : 0.9f);
	}
}

void GameScreen::update(float deltaTime)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F5))
    {
        m_level.reload();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
    {
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_camera.move(-0.05f, 0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_camera.move(0.05f, 0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        m_camera.move(0, -0.05f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        m_camera.move(0, 0.05f);
    }

    m_world->loopStart();
    m_world->setDelta(deltaTime);

    // Update input
    m_pInputSystem->process();

    // Step physics world
    PhysicsLocator::getObject()->Step(deltaTime, 6, 2);
    m_pPhysicsSystem->process();
}

void GameScreen::render()
{
    m_pCameraSystem->process();
    m_pRenderSystem->process();
    // Draw debug over other data
    PhysicsLocator::getObject()->DrawDebugData();
}

void GameScreen::resize(const sf::Vector2u &size)
{
    // m_camera.resize(size);
}
