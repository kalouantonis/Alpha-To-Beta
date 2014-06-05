#ifndef  LOGGER_EXPORTS_H_
#define  LOGGER_EXPORTS_H_

// Forward define luabind object
namespace luabind
{
    namespace adl
    {
    class object;
    }
}

namespace InternalScriptExports
{

void luaLog(const luabind::adl::object& text);

}

#endif
