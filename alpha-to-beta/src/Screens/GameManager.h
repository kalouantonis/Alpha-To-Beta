#ifndef  GameManager_INC
#define  GameManager_INC

#include <BaseGameManager.h>
#include <Events/JumpListener.h>

class PlayerInputSystem;

class GameManager: public BaseGameManager
{
public:
    GameManager();
    ~GameManager();

    virtual void init() final;
    virtual void update(float delta) final;
    virtual void destroy() final;

    virtual void registerScriptEvents() final;
    virtual void registerComponents() final;
    virtual void unregisterComponents() final;

private:
    PlayerInputSystem* m_pPlayerInputSystem;
    UJumpListenerPtr m_pJumpListener;
};

#endif   /* ----- #ifndef GameManager_INC  ----- */
