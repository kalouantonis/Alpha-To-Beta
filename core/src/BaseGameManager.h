#ifndef  BaseGameManager_INC
#define  BaseGameManager_INC

#include <SFMLPtrDef.h>
#include <SFML/System/Vector2.hpp>

#include <Artemis/World.h>

//FWD DEFS /////////////////////////////////////////////////////////////////////
class RenderSystem;
class PhysicsSystem;
class Box2DRenderer;
class JumpListener;
class CameraFollowingSystem;
class ScriptSystem;

class SpriteBatch;
class Camera2D;

class b2World;

//namespace Artemis
//{
//class World;
//}
////////////////////////////////////////////////////////////////////////////////

class BaseGameManager
{
public:
    BaseGameManager();
    virtual ~BaseGameManager();

    virtual void init();

    virtual void update(float delta);
    virtual void render();

    /**
     * Initialize render systems and camera systems
     * 
     * If called after physics initialization, the camera will be adjusted accordingly
     */
    void initRenderer(SpriteBatch& spriteBatch, Camera2D& camera);

    /**
     * Finish initialization
     */
    void start();

    /**
     * Initialize physics locator and system
     *
     * @param gravity 2D Gravity vector
     * @param ppp Pixels per meter
     */
    void initPhysics(const sf::Vector2f& gravity, 
            const sf::Vector2f& ppp = sf::Vector2f(1, 1));
    /**
     * Initialize Box2D physics renderer
     */
    void initPhysicsRenderer(sf::RenderTargetPtr pRenderTarget);

    /**
     * Initialize lua state manager and create script system
     * 
     * @return May fail to initialize lua, false if failed
     */
    bool initLua();
    /**
     * Meant to be overriden, call to register all script events
     */
    virtual void registerScriptEvents() {}
    /**
     * Meant to be override, call to unregister all registered script events
     */
    virtual void unregisterScriptEvents() {}
    /**
     * Register all given components to the entity factory
     */
    virtual void registerComponents() {}
    /**
     * Unregister all previously given components from entity factory
     */
    virtual void unregisterComponents() {}

    void destroyPhysics();
    void destroyPhysicsRenderer();
    void destroyLua();
    /** 
     * Destroy all items initialized by manager and clear world
     */
    virtual void destroy();

protected:
    artemis::SystemManager* getSystemManager() const;

private:
    std::shared_ptr<artemis::World> m_pWorld;

    RenderSystem* m_pRenderSystem;

    PhysicsSystem* m_pPhysicsSystem;
    std::shared_ptr<b2World> m_pPhysicsWorld;
    std::unique_ptr<Box2DRenderer> m_pBox2DRenderer;

    CameraFollowingSystem* m_pCameraFollowingSystem;
    ScriptSystem* m_pScriptSystem; 
};

#endif   /* ----- #ifndef GameManager_INC  ----- */
