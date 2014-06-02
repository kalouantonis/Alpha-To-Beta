#include <Physics/CollisionDispatcher.h>

#include <Box2D/Dynamics/Contacts/b2Contact.h>

#include <Events/CollisionEvents.h>
#include <Events/EventManager.h>

void CollisionDispatcher::BeginContact(b2Contact *contact)
{
    IEventManager::get()->queueEvent(
        EventDataPtr(new CollisonBeginEvent(contact))
    );
}

void CollisionDispatcher::EndContact(b2Contact *contact)
{
    IEventManager::get()->queueEvent(
        EventDataPtr(new CollisonEndEvent(contact))
    );
}
