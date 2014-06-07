#ifndef ENTITY_EXPORTS_H_
#define ENTITY_EXPORTS_H_

// Luabind FWD defs
namespace luabind
{
    namespace adl 
    {
    class object;
    }
}


namespace InternalScriptExports
{

// Because I can, thats why
const long INVALID_ENTITY_ID = -69;

long createEntity(const char* entityResource, const luabind::adl::object& luaPosition);
void removeEntity(long entityId);

}

#endif
