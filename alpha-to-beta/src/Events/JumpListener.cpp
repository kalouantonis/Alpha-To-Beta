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
			b2Body* pPhysBody = pDynamicBody->body;

			// Reset Y velocity for a better feeling jump
			pPhysBody->SetLinearVelocity(b2Vec2(
				pPhysBody->GetLinearVelocity().x,
				0
			));

            pPhysBody->ApplyLinearImpulse(
                toVec2<b2Vec2>(pJumpBehaviour->impulse),
                // Get object center
                pPhysBody->GetWorldCenter(),
                true
            );
        }
    }
}

void JumpListener::receiveBeginCollisionEvt(EventDataPtr pEvent)
{
    BaseCollisionEventPtr pCollisionEvent =
            std::static_pointer_cast<BaseCollisionEvent>(pEvent);

    // FIXME: Check whether collision occurs at the top of the object

    JumpBehaviour* jumpComponents[2] = {
        safeGetComponent<JumpBehaviour>(pCollisionEvent->getEntityA()),
        safeGetComponent<JumpBehaviour>(pCollisionEvent->getEntityB())
    };

    JumpBehaviour* pCurrentJumpComponent = nullptr;

    // Exit if no or 2 jump components are found
    if((!jumpComponents[0] && !jumpComponents[1]) ||
            (jumpComponents[0] && jumpComponents[1]))
        return;
    else if(jumpComponents[0])
        pCurrentJumpComponent = jumpComponents[0];
    else
        pCurrentJumpComponent = jumpComponents[1];

    pCurrentJumpComponent->resetJumps();
}
