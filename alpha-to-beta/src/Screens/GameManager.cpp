#include <Screens/GameManager.h>

#include <Components/JumpBehaviour.h>

#include <Events/JumpEvent.h>
#include <Entities/EntityFactory.h>

#include <Memory/loose_ptr.h>

#include <Input/InputLocator.h>
#include <Systems/PlayerInputSystem.h>

#include <Utils/Logger.h>

#include <Artemis/SystemManager.h>

GameManager::GameManager()
    : m_pPlayerInputSystem(nullptr)
{

}

GameManager::~GameManager()
{

}

void GameManager::init()
{
    // Call super 
    BaseGameManager::init();

    // Set up input system
    CORE_DEBUG("Creating input system...");
    m_pPlayerInputSystem =  static_cast<PlayerInputSystem*>(
            getSystemManager()->setSystem(new PlayerInputSystem())
    );

    CORE_DEBUG("Registering input locator...");
    InputLocator::provide(loose_ptr(m_pPlayerInputSystem));

    CORE_DEBUG("Creating jump listener...");
    m_pJumpListener = UJumpListenerPtr(new JumpListener());
}

void GameManager::update(float delta) 
{
    // Super
    BaseGameManager::update(delta);

    // Update input
    m_pPlayerInputSystem->process();
}

void GameManager::destroy()
{
    CORE_DEBUG("Destroying event listener...");
    m_pJumpListener = nullptr;

    // Remove input locator
    CORE_DEBUG("Destroying input locator...");
    InputLocator::remove();

    CORE_DEBUG("Destroying input system...");
    m_pPlayerInputSystem = nullptr;

    // Super
    BaseGameManager::destroy();
}

void GameManager::registerScriptEvents()
{
    REGISTER_SCRIPT_EVENT(JumpEvent, JumpEvent::sEventType);
}

void GameManager::registerComponents()
{
    REGISTER_COMPONENT(JumpBehaviour, JumpBehaviour::g_name);
}

void GameManager::unregisterComponents()
{
    UNREGISTER_COMPONENT(JumpBehaviour::g_name);
}
