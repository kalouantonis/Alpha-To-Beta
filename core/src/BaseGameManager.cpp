#include <BaseGameManager.h>

#include <Resources/ResourceDef.h>

#include <Entities/WorldLocator.h>

#include <Graphics/Camera2D.h>
#include <Graphics/SpriteBatch.h>

#include <Physics/PhysicsLocator.h>
#include <Physics/Box2DRenderer.h>

// Systems
#include <Systems/CameraFollowingSystem.h>
#include <Systems/PhysicsSystem.h>
#include <Systems/RenderSystem.h>
#include <Lua/ScriptSystem.h>

#include <Lua/LuaStateManager.h>

#include <Utils/Logger.h>

#include <Artemis/SystemManager.h>

#include <Box2D/Dynamics/b2World.h>

#include <assert.h>

BaseGameManager::BaseGameManager()
    : m_pWorld(new artemis::World())
    , m_pRenderSystem(nullptr)
    , m_pPhysicsSystem(nullptr)
    , m_pPhysicsWorld(nullptr)
    , m_pBox2DRenderer(nullptr)
    , m_pCameraFollowingSystem(nullptr)
    , m_pScriptSystem(nullptr)
{
}

BaseGameManager::~BaseGameManager()
{
    if(m_pPhysicsSystem)
        destroyPhysics();

    if(m_pBox2DRenderer)
        destroyPhysicsRenderer();

    if(m_pPhysicsSystem)
        destroyLua();

    if(m_pWorld)
        // I know calling virtual methods from destructors is a bad idea,
        // but the user is tasked with destroying things manually. 
        // this is more like damage control
        destroy();
}

void BaseGameManager::init()
{
    CORE_DEBUG("Providing texture locator...");
    TextureLocator::provide(TextureLocator::Ptr(new TextureHolder()));

    CORE_DEBUG("Providing world locator...");
    WorldLocator::provide(m_pWorld);
}

void BaseGameManager::update(float delta)
{
    assert(m_pWorld != nullptr);

    m_pWorld->loopStart();
    m_pWorld->setDelta(delta);

    // Step physics world
    if(m_pPhysicsWorld) // If physics world exists, so does the physics system
    {
        // Use recommended velocity and position intervals according to Box2D manual
        // See: http://www.box2d.org/manual.html
        //
        // Actually, im gonna reduce velocity iterations a little for visible performance
        // increases
        m_pPhysicsWorld->Step(delta, 4, 2);
        m_pPhysicsSystem->process();
    }
    
    // Update script system
    if(m_pScriptSystem)
        m_pScriptSystem->process();
}

void BaseGameManager::render()
{
    assert(m_pCameraFollowingSystem != nullptr);
    assert(m_pRenderSystem != nullptr);

    m_pCameraFollowingSystem->process();
    
    m_pRenderSystem->process();

    // Draw debug data
    if(m_pPhysicsWorld)
        m_pPhysicsWorld->DrawDebugData();
}

void BaseGameManager::start()
{
    CORE_DEBUG("Initializing all systems...");
    getSystemManager()->initializeAll();

    if(m_pPhysicsSystem)
    {
        Camera2D& camera = m_pCameraFollowingSystem->getCamera();

        CORE_DEBUG("Resizing camera to work with physics system...");
        camera.resize(sf::Vector2u(
                    camera.getSize().x / PhysicsLocator::PixelsPerMeter.x,
                    camera.getSize().y / PhysicsLocator::PixelsPerMeter.y
        ));
    }

    CORE_DEBUG("Initialization complete");
}

void BaseGameManager::initRenderer(SpriteBatch& spriteBatch, Camera2D& camera)
{
    assert(m_pWorld != nullptr);

    artemis::SystemManager* systemManager = getSystemManager();

    CORE_DEBUG("Creating render system...");
    m_pRenderSystem = static_cast<RenderSystem*>(
        systemManager->setSystem(new RenderSystem(spriteBatch))
    );

    CORE_DEBUG("Creating camera following system...");
    m_pCameraFollowingSystem = static_cast<CameraFollowingSystem*>(
            systemManager->setSystem(new CameraFollowingSystem(camera))
    );
}

void BaseGameManager::initPhysics(const sf::Vector2f& gravity, const sf::Vector2f& ppp)
{
    CORE_DEBUG("Providing physics locator...");
    PhysicsLocator::provide(gravity, ppp);

    m_pPhysicsWorld = PhysicsLocator::getObject();

    CORE_DEBUG("Creating physics system...");
    m_pPhysicsSystem = static_cast<PhysicsSystem*>(
            getSystemManager()->setSystem(new PhysicsSystem())
    );
}

void BaseGameManager::initPhysicsRenderer(sf::RenderTargetPtr pRenderTarget)
{
    assert(m_pWorld != nullptr);

    if(!m_pPhysicsWorld)
    {
        CORE_ERROR("Attempting to initialize physics renderer without initializing physics");
        return;
    }

    m_pBox2DRenderer = std::unique_ptr<Box2DRenderer>(new Box2DRenderer(pRenderTarget));

    CORE_DEBUG("Initializing physics renderer...");
    m_pPhysicsWorld->SetDebugDraw(m_pBox2DRenderer.get());
    m_pBox2DRenderer->SetFlags(Box2DRenderer::e_shapeBit);
}

bool BaseGameManager::initLua()
{
    CORE_DEBUG("Initializing lua state...");
    if(!LuaStateManager::create())
    {
        return false;
    }

    CORE_DEBUG("Creating script system...");
    m_pScriptSystem = static_cast<ScriptSystem*>(
        getSystemManager()->setSystem(new ScriptSystem())
    );

    return true;
}

void BaseGameManager::destroyPhysics()
{
    CORE_DEBUG("Destroying physics world...");
    PhysicsLocator::remove();
    m_pPhysicsWorld = nullptr;

    m_pPhysicsSystem = nullptr;
}

void BaseGameManager::destroyPhysicsRenderer()
{
    if(m_pPhysicsWorld)
    {
        CORE_DEBUG("Destroying physics renderer...");
        // Remove debug draw
        m_pPhysicsWorld->SetDebugDraw(NULL);
        m_pBox2DRenderer = nullptr;
    }
}

void BaseGameManager::destroyLua()
{
    CORE_DEBUG("Destroying lua state...");
    LuaStateManager::destroy();

    // TODO: CHeck if this causes memory leaks.
    m_pScriptSystem = nullptr;
}

void BaseGameManager::destroy()
{
    assert(m_pWorld != nullptr);

    CORE_DEBUG("Removing all entities...");
    m_pWorld->getEntityManager()->removeAllEntities();

    CORE_DEBUG("Destroying entity world...");
    WorldLocator::remove();
    m_pWorld = nullptr;

    CORE_DEBUG("Destroying textures...");
    TextureLocator::remove();
}

artemis::SystemManager* BaseGameManager::getSystemManager() const 
{
    assert(m_pWorld);

    return m_pWorld->getSystemManager();
}
