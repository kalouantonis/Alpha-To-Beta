#include <Events/JumpEvent.h>

#include <Components/DynamicBody.h>
#include <Components/JumpBehaviour.h>

#include <Entities/WorldLocator.h>
#include <Entities/Utils.h>

#include <Lua/LuaStateManager.h>
#include <Lua/Utils.h>

const EventType JumpEvent::sEventType = 0x8a2620ec;

JumpEvent::JumpEvent()
    : ScriptEvent()
    , m_pBody(nullptr)
    , m_pJumpBehaviour(nullptr)
{

}

JumpEvent::JumpEvent(DynamicBody* body, JumpBehaviour* jumpBehaviour)
    : ScriptEvent()
    , m_pBody(body)
    , m_pJumpBehaviour(jumpBehaviour)
{

}

const char *JumpEvent::getName() const
{
    return "JumpEvent";
}

void JumpEvent::buildEventData() 
{
	// Create new table
	m_eventData.AssignNewTable(LuaStateManager::get()->getLuaState());
	// Give impulse
	m_eventData.SetObject("impulse", vec2ToTable(m_pJumpBehaviour->impulse));
	m_eventData.SetInteger("max_jumps", m_pJumpBehaviour->getMaxJumps());
	m_eventData.SetInteger("num_jumps", m_pJumpBehaviour->getNumJumps());
}

bool JumpEvent::buildEventFromScript()
{
	if(m_eventData.IsTable())
	{
		// Attempt to get ID
		LuaPlus::LuaObject temp = m_eventData.GetByName("id");

		if(temp.IsInteger())
		{
			// Convert to int
			int eid = temp.ToInteger();

			// Check that we have invalid ID
			if(eid < 0)
			{
				CORE_ERROR("ID provided for JumpEvent must be larger than 0");
				return false;
			}

			// Get entity from world
			artemis::Entity& e = WorldLocator::getObject()->getEntity(eid);

			// Attempt to receive dynamic body
			DynamicBody* pDynamicBody = safeGetComponent<DynamicBody>(&e);
			// Attempt to receieve jump behaviour
			JumpBehaviour* pJumpBehaviour = safeGetComponent<JumpBehaviour>(&e);

			if(pDynamicBody != nullptr && pJumpBehaviour != nullptr) // Success
			{
				// Set components
				m_pBody = pDynamicBody;
				m_pJumpBehaviour = pJumpBehaviour;
				return true;
			}
			else 
			{
				CORE_ERROR("Requested entity for JumpEvent does not contain a DynamicBody and a JumpBehaviour");
				return false;
			}
		}
		else
		{
			CORE_ERROR("Invalid ID sent to JumpEvent. Must be of type integer; type = " + std::string(temp.TypeName()));
			return false;
		}
	}

	CORE_ERROR("Event data for JumpEvent must be of type table; type = " + std::string(m_eventData.TypeName()));

	return false;
}