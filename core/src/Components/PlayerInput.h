#ifndef PLAYER_INPUT_H
#define PLAYER_INPUT_H

#include <Components/ParsedComponent.h>

class PlayerInput: public ParsedComponent
{
public:
	PlayerInput();
	~PlayerInput();
	
	virtual bool load(const tinyxml2::XMLElement* pElement) final;

	static const char* g_name;
    virtual const char* getName() const override { return g_name; }
};

#endif // PLAYER_INPUT_H
