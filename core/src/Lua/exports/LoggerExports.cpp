#include <Lua/exports/LoggerExports.h>

#include <Utils/Logger.h>

#include <luabind/object.hpp>

namespace InternalScriptExports 
{

void luaLog(const luabind::adl::object& text)
{
   try 
   {
       // Attempt to cast object to string
       const std::string& luaText = luabind::object_cast<std::string>(text);
       // Output if success
       CORE_LOG("LUA", luaText);
   }
   catch(const luabind::cast_failed& e)
   {
       // Print exception if failed
       CORE_LOG("LUA", "Logger can't cast type to string.");
   }
}

}
