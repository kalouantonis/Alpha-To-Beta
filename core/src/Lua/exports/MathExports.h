#ifndef _MATH_EXPORTS_H_
#define _MATH_EXPORTS_H_

// FWD Defs
namespace luabind
{
    namespace adl
    {
    class object;
    }
}

namespace InternalScriptExports 
{

void convertToWorldCoords(const luabind::adl::object& luaVec);

}

#endif
