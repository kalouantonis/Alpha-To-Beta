#include <Events/JumpListener.h>

#include <Events/EventData.h>
#include <Events/EventManager.h>
#include <Events/JumpEvent.h>
#include <Events/CollisionEvents.h>

#include <Components/DynamicBody.h>
#include <Components/JumpBehaviour.h>

#include <Entities/Utils.h>

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
        if(pJumpBehaviour->jump() <= pJumpBehaviour->getMaxJumps())
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

    JumpBehaviour* jumpComponents[2] {
        safeGetComponent<JumpBehaviour>(pCollisionEvent->getEntityA()),
        safeGetComponent<JumpBehaviour>(pCollisionEvent->getEntityB())
    };

    JumpBehaviour* currentJumpComponent = nullptr;

    if((!jumpComponents[0] && !jumpComponents[1]) ||
            (jumpComponents[0] && jumpComponents[1]))
        return;
    else if(jumpComponents[0])
        currentJumpComponent = jumpComponents[0];
    else
        currentJumpComponent = jumpComponents[1];


    CORE_DEBUG("RESETTING JUMPS!!!!");
    currentJumpComponent->resetJumps();
}
