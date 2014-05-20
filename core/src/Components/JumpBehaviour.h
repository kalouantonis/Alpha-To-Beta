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
    unsigned int numJumps;

    unsigned int getMaxJumps() const { return m_maxJumps; }
    void resetJumps() { numJumps = 0; }

private:
    unsigned int m_maxJumps;
};

#endif // JUMP_BEHAVIOUR_H
