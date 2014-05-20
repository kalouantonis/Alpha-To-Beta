#ifndef EVENTDATA_H_
#define EVENTDATA_H_

#include <memory>

typedef unsigned long EventType;

class IEventData
{
public:
    virtual ~IEventData() {}
    /**
     * @brief Get the type of the event.
     */
    virtual EventType getEventType() const = 0;
    /**
     * @brief Get the timestamp of the event in delta from last update call
     * @return
     */
    virtual float getTimeStamp() const = 0;
    /**
     * @brief Get the name of the event in string form
     * @return
     */
    virtual const char* getName() const = 0;
};

class BaseEventData: public IEventData
{
public:
    explicit BaseEventData(const float timeStamp = 0.f)
        : m_timeStamp(timeStamp)
    {

    }

//    virtual EventType getEventType() const = 0;
    float getTimeStamp() const override { return m_timeStamp; }

private:
    const float m_timeStamp;
};

typedef std::shared_ptr<IEventData> EventDataPtr;

#endif // EVENTDATA_H_
