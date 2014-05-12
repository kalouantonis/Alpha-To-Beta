#include <Events/JumpListener.h>

#include <Events/EventData.h>
#include <Events/EventManager.h>
#include <Events/JumpEvent.h>

#include <Components/DynamicBody.h>
#include <Components/JumpBehaviour.h>

#include <Utils/Logger.h>
#include <Math/Vector.h>

#include <Box2D/Dynamics/b2Body.h>

JumpListener::JumpListener()
{
    IEventManager::get()->addListener(
                fastdelegate::MakeDelegate(this, &JumpListener::receive),
                JumpEvent::sEventType
    );
}

JumpListener::~JumpListener()
{
    // Remove listener from manager
//    IEventManager::get()->removeListener(m_delegate, JumpEvent::sEventType);
}

void JumpListener::receive(EventDataPtr pEvent)
{
    JumpEventPtr pJumpEvent = std::static_pointer_cast<JumpEvent>(pEvent);

    DynamicBody* pDynamicBody = pJumpEvent->getBody();
    const JumpBehaviour* pJumpBehaviour = pJumpEvent->getJumpBehaviour();

    if(pDynamicBody != nullptr && pJumpBehaviour != nullptr)
    {
        pDynamicBody->body->ApplyLinearImpulse(
            toB2Vec(pJumpBehaviour->impulse),
            pDynamicBody->body->GetPosition(),
            true
        );
    }
}
