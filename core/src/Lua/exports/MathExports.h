#ifndef _MATH_EXPORTS_H_
#define _MATH_EXPORTS_H_

#include <LuaObject.h>

namespace InternalScriptExports 
{

void convertToWorldCoords(LuaPlus::LuaObject luaVec);

float floor(float val);
float sin(float val);
float cos(float val);
float tan(float val);
float ceil(float val);
float round(float val);

}

#endif
