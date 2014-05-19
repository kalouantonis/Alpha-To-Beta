#ifndef COLLISION_EVENTS_H_
#define COLLISION_EVENTS_H_

#include <Events/EventData.h>

class b2Contact;

class BaseCollisionEvent: public BaseEventData
{
public:
    BaseCollisionEvent(b2Contact* pContact);

    const b2Contact* getContact() const { return m_pContact; }
    b2Contact* getContact() { return m_pContact; }

private:
    b2Contact* m_pContact;
};

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

