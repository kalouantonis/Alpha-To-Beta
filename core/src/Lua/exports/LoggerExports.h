#ifndef  LOGGER_EXPORTS_H_
#define  LOGGER_EXPORTS_H_

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
