#ifndef ENTITY_EXPORTS_H_
#define ENTITY_EXPORTS_H_

#include <LuaObject.h>

namespace InternalScriptExports
{

// Because I can, thats why
const int INVALID_ENTITY_ID = -69;

int createEntity(const char* entityResource, LuaPlus::LuaObject luaPosition);
void removeEntity(int entityId);

}

#endif
