#ifndef COLLISION_EVENTS_H_
#define COLLISION_EVENTS_H_

#include <Events/EventData.h>
#include <Lua/ScriptEvent.h>

class b2Contact;

namespace artemis
{
class Entity;
}

class BaseCollisionEvent: public ScriptEvent
{
public:
	BaseCollisionEvent();
    BaseCollisionEvent(b2Contact* pContact);

    /**
     * @brief Get box2d contact from collision
     * 
     * @return Constant reference to contact
     */
    const b2Contact* getContact() const { return m_pContact; }
    /**
     * @brief Get box2d contact from collision
     *
     * @return reference to contact
     */
    b2Contact* getContact() { return m_pContact; }

    artemis::Entity *getEntityA() const { return m_pEntityA; }
    artemis::Entity *getEntityB() const { return m_pEntityB; }

private:
	virtual void buildEventData() final {}
	virtual bool buildEventFromScript() final { return false; }

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

	CollisonBeginEvent();
    CollisonBeginEvent(b2Contact* pContact);

    virtual EventType getEventType() const final { return sEventType; }
    virtual const char* getName() const final;

	EXPORT_FOR_SCRIPT_EVENT(CollisonBeginEvent)
};

class CollisonEndEvent: public BaseCollisionEvent
{
public:
    static const EventType sEventType;

	CollisonEndEvent();
    CollisonEndEvent(b2Contact* pContact);

    virtual EventType getEventType() const final { return sEventType; }
    virtual const char* getName() const final;

    EXPORT_FOR_SCRIPT_EVENT(CollisonEndEvent)
};


#endif // COLLISION_EVENTS_H_

