#include <Lua/exports/LoggerExports.h>

#include <Utils/Logger.h>

namespace InternalScriptExports 
{

void luaLog(LuaPlus::LuaObject text)
{
    if(text.IsConvertibleToString())
    {
        CORE_LOG("LUA", text.ToString());
    }
    else
    {
        CORE_LOG("LUA", "<" + std::string(text.TypeName()) + ">");
    }
}

}
