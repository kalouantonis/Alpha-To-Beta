#include <Events/JumpListener.h>

#include <Events/EventData.h>
#include <Events/EventManager.h>
#include <Events/JumpEvent.h>
#include <Events/CollisionEvents.h>

#include <Components/DynamicBody.h>
#include <Components/JumpBehaviour.h>

#include <Utils/Logger.h>
#include <Math/Vector.h>

#include <Artemis/Entity.h>

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/Contacts/b2Contact.h>

using namespace artemis;

JumpListener::JumpListener()
{
    // Add jump listener
    IEventManager::get()->addListener(
                fastdelegate::MakeDelegate(this, &JumpListener::receiveJumpEvt),
                JumpEvent::sEventType
    );

    // Add collision listener
    IEventManager::get()->addListener(
                fastdelegate::MakeDelegate(this, &JumpListener::receiveBeginCollisionEvt),
                CollisonBeginEvent::sEventType
    );
}

JumpListener::~JumpListener()
{
    // Remove listener from manager
    IEventManager::get()->removeListener(
                fastdelegate::MakeDelegate(this, &JumpListener::receiveJumpEvt),
                JumpEvent::sEventType
    );

    // Remove collision listener
    IEventManager::get()->removeListener(
                fastdelegate::MakeDelegate(this, &JumpListener::receiveBeginCollisionEvt),
                CollisonBeginEvent::sEventType
    );
}

void JumpListener::receiveJumpEvt(EventDataPtr pEvent)
{
    JumpEventPtr pJumpEvent = std::static_pointer_cast<JumpEvent>(pEvent);

    DynamicBody* pDynamicBody = pJumpEvent->getBody();
    JumpBehaviour* pJumpBehaviour = pJumpEvent->getJumpBehaviour();

    if(pDynamicBody != nullptr && pJumpBehaviour != nullptr)
    {
        if(++pJumpBehaviour->numJumps <= pJumpBehaviour->getMaxJumps())
        {
            pDynamicBody->body->ApplyLinearImpulse(
                toB2Vec(pJumpBehaviour->impulse),
                // Get object center
                pDynamicBody->body->GetWorldCenter(),
                true
            );
        }
    }
}

void JumpListener::receiveBeginCollisionEvt(EventDataPtr pEvent)
{
    BaseCollisionEventPtr pCollisionEvent =
            std::static_pointer_cast<BaseCollisionEvent>(pEvent);

    // FIXME: Check whether collision occurs at the top

    // Entity that initiated collision. I think, check this!
    Entity* entityA = pCollisionEvent->getEntityA();
    Entity* entityB = pCollisionEvent->getEntityB();

    Entity* usedEntity = nullptr;

    if(!entityA && !entityB) // No usable entities
        return;

    if(entityA)
        usedEntity = entityA;
    else
        usedEntity = entityB;

    Component* pJumpBehaviour = usedEntity->getComponent<JumpBehaviour>();

    if(pJumpBehaviour == nullptr)
        return;

    CORE_DEBUG("RESETTING JUMPS!!!!");
    static_cast<JumpBehaviour*>(pJumpBehaviour)->resetJumps();
}
