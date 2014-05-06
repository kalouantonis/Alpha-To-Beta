#ifndef JUMP_BEHAVIOUR_H
#define JUMP_BEHAVIOUR_H

#include <Components/ParsedComponent.h>

#include <SFML/System/Vector2.hpp>

class JumpBehaviour: public ParsedComponent
{
public:
	JumpBehaviour(float yImpulse = 0.f);
	~JumpBehaviour();

	virtual bool load(const tinyxml2::XMLElement* pElement) final;

	static const char* g_name;
    virtual const char* getName() const override { return g_name; }
	
	sf::Vector2f impulse;
};

#endif // JUMP_BEHAVIOUR_H
