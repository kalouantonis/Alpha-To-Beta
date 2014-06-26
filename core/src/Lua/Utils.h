#ifndef LUA_UTILS_H_
#define LUA_UTILS_H_

#include <LuaObject.h>

template <typename VecT>
LuaPlus::LuaObject vec2ToTable(const VecT& vec)
{
	LuaPlus::LuaObject retTable;
	retTable.AssignNewTable(LuaStateManager::get()->getLuaState());

	retTable.SetNumber("x", vec.x);
	retTable.SetNumber("y", vec.y);

	return retTable;
}

template <typename VecT>
VecT tableToVec2(const LuaPlus::LuaObject& luaTable)
{
	LuaPlus::LuaObject temp;
	// Vector to be returned 
	VecT outVec;

	// x
	temp = luaTable.Get("x");
	if(temp.IsNumber())
		outVec.x = temp.GetFloat();
	else 
		CORE_ERROR("Specified x value for lua vector is not a number");

	// y
	temp = luaTable.Get("y");
	if(temp.IsNumber())
		outVec.y = temp.GetFloat();
	else
		CORE_ERROR("Specified y value for lua vector is not a number");

	return outVec;
}

#endif