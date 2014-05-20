#include <Events/CollisionEvents.h>

#include <Box2D/Dynamics/Contacts/b2Contact.h>


// BaseCollisionEvent///////////////////////////////////////////////////////////
BaseCollisionEvent::BaseCollisionEvent(b2Contact *pContact)
    : BaseEventData()
    , m_pContact(pContact)
{
    // I know C style casts are bad, but void* aren't cool either :)
    m_pEntityA = (artemis::Entity*) pContact->GetFixtureA()->GetBody()->GetUserData();
    m_pEntityB = (artemis::Entity*) pContact->GetFixtureB()->GetBody()->GetUserData();
}
////////////////////////////////////////////////////////////////////////////////

// CollisonBeginEvent //////////////////////////////////////////////////////////
const EventType CollisonBeginEvent::sEventType = 0x6bda68cf;

CollisonBeginEvent::CollisonBeginEvent(b2Contact *pContact)
    : BaseCollisionEvent(pContact)
{
}

const char *CollisonBeginEvent::getName() const
{
    return "CollisionBeginEvent";
}
////////////////////////////////////////////////////////////////////////////////

// CollisionEndEvent ///////////////////////////////////////////////////////////
const EventType CollisonEndEvent::sEventType = 0x5e928a15;

CollisonEndEvent::CollisonEndEvent(b2Contact *pContact)
    : BaseCollisionEvent(pContact)
{

}

const char *CollisonEndEvent::getName() const
{
    return "CollisionEndEvent";
}
////////////////////////////////////////////////////////////////////////////////
