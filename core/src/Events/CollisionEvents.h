#ifndef COLLISION_EVENTS_H_
#define COLLISION_EVENTS_H_

#include <Events/EventData.h>

class b2Contact;

namespace artemis
{
class Entity;
}

class BaseCollisionEvent: public BaseEventData
{
public:
    BaseCollisionEvent(b2Contact* pContact);

    const b2Contact* getContact() const { return m_pContact; }
    b2Contact* getContact() { return m_pContact; }

    artemis::Entity *getEntityA() const { return m_pEntityA; }
    artemis::Entity *getEntityB() const { return m_pEntityB; }

private:
    b2Contact* m_pContact;

    /**
     * Extracted entities from body user data
     */
    artemis::Entity* m_pEntityA;
    artemis::Entity* m_pEntityB;
};

typedef std::shared_ptr<BaseCollisionEvent> BaseCollisionEventPtr;

class CollisonBeginEvent: public BaseCollisionEvent
{
public:
    static const EventType sEventType;

    CollisonBeginEvent(b2Contact* pContact);

    virtual EventType getEventType() const final { return sEventType; }
    virtual const char* getName() const final;
};

class CollisonEndEvent: public BaseCollisionEvent
{
public:
    static const EventType sEventType;

    CollisonEndEvent(b2Contact* pContact);

    virtual EventType getEventType() const final { return sEventType; }
    virtual const char* getName() const final;
};


#endif // COLLISION_EVENTS_H_

