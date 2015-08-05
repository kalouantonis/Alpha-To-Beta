#ifndef JUMP_BEHAVIOUR_H
#define JUMP_BEHAVIOUR_H

#include <Components/ParsedComponent.h>

#include <SFML/System/Vector2.hpp>

class JumpBehaviour: public ParsedComponent
{
public:
    JumpBehaviour(float yImpulse = 0.f, unsigned int maxJumps = 1);
	~JumpBehaviour();

	virtual bool load(const tinyxml2::XMLElement* pElement) final;

	static const char* g_name;
    virtual const char* getName() const override { return g_name; }
	
	sf::Vector2f impulse;

    unsigned int getMaxJumps() const { return m_maxJumps; }

    unsigned int jump() { return ++m_numJumps; }
	unsigned int getNumJumps() const { return m_numJumps; }
    void resetJumps() { m_numJumps = 0; }

private:
    //virtual void buildEventData() final;

    unsigned int m_numJumps;
    unsigned int m_maxJumps;
};

#endif // JUMP_BEHAVIOUR_H
