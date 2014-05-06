#include <Systems/PlayerInputSystem.h>

#include <Components/PlayerInput.h>
#include <Components/DynamicBody.h>
#include <Components/JumpBehaviour.h>

#include <Math/Vector.h>

#include <Utils/Logger.h>

#include <Box2D/Dynamics/b2Body.h>
#include <SFML/Window/Keyboard.hpp>

#include <Artemis/Entity.h>
#include <Artemis/World.h>

const int INVALID_ID = -69;

PlayerInputSystem::PlayerInputSystem()
	: m_pPlayerBody(nullptr)
	, m_eid(INVALID_ID)
{
	addComponentType<PlayerInput>();
	addComponentType<DynamicBody>();
}

PlayerInputSystem::~PlayerInputSystem()
{

}

bool PlayerInputSystem::containsValidEntity()
{
	return (m_pPlayerBody != nullptr) || (m_eid != INVALID_ID);
}

void PlayerInputSystem::added(artemis::Entity& e)
{
	DynamicBody* body = static_cast<DynamicBody*>(
		e.getComponent<DynamicBody>()
	);

	if((e.getComponent<PlayerInput>() != NULL) && (body != NULL))
	{
		m_pPlayerBody = body;
		m_eid = e.getId();
	}
}

void PlayerInputSystem::removed(artemis::Entity &e)
{
	if(e.getUniqueId() == m_eid)
	{
		m_pPlayerBody = nullptr;
		m_eid = INVALID_ID;
	}
}

bool PlayerInputSystem::checkProcessing()
{
	return true;
}

void PlayerInputSystem::processEntities(artemis::ImmutableBag<artemis::Entity*>& bag)
{
	if(!containsValidEntity())
		return;

	// TODO: This is continuous input, we can't have that for jumping
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		//m_pPlayerBody->body->ApplyLinearI
		const JumpBehaviour* pJumpBehaviour = dynamic_cast<const JumpBehaviour*>(
			// Get from world using ID
			world->getEntity(m_eid).getComponent<JumpBehaviour>()
		);

		if(pJumpBehaviour != nullptr)
		{
			m_pPlayerBody->body->ApplyLinearImpulse(
				toB2Vec(pJumpBehaviour->impulse),
				toB2Vec(m_pPlayerBody->getPosition()),
				true
			);
		}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_pPlayerBody->body->ApplyLinearImpulse(b2Vec2(0.2f, 0.f), 
			m_pPlayerBody->body->GetPosition(), true
		);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_pPlayerBody->body->ApplyLinearImpulse(b2Vec2(-0.2f, 0.f), 
			m_pPlayerBody->body->GetPosition(), true
		);
	}
}
