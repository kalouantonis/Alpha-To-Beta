project(luaplus)

include_directories(
    ${luaplus_SOURCE_DIR};
    ${luaplus_SOURCE_DIR}/src;
)

set(
    MAIN_SRC
    "LuaObject.cpp"
    "LuaPlusAddons.c"
    #"LuaPlusAll.cpp"
    "LuaPlus.cpp"
    "LuaPlusFunctions.cpp"
    "LuaPlus_Libs.cpp"
    "LuaState.cpp"
    "LuaState_DumpObject.cpp"
    "LuaStateOutFile.cpp"
    "LuaTableIterator.cpp"
    "lwstrlib.c"
    "popen.c"
)

set(
    MAIN_HDR
    "LuaAutoBlock.h"
    "LuaCall.h"
    "LuaFunction.h"
    "LuaHelper.h"
    "LuaHelper_Object.h"
    "LuaHelper_StackObject.h"
    "LuaLink.h"
    "LuaObject.h"
    "LuaPlusCD.h"
    "LuaPlus.h"
    "LuaPlusInternal.h"
    "LuaStackObject.h"
    "LuaStackTableIterator.h"
    "LuaStateCD.h"
    "LuaState.h"
    "LuaStateOutFile.h"
    "LuaTableIterator.h"
)

set(
    INNER_SRC
    "src/lapi.c"
    "src/lauxlib.c"
    "src/lbaselib.c"
    "src/lcode.c"
    "src/ldblib.c"
    "src/ldebug.c"
    "src/ldo.c"
    "src/ldump.c"
    "src/lfunc.c"
    "src/lgc.c"
    "src/linit.c"
    "src/liolib.c"
    "src/llex.c"
    "src/lmathlib.c"
    "src/lmem.c"
    "src/loadlib.c"
    "src/lobject.c"
    "src/lopcodes.c"
    "src/loslib.c"
    "src/lparser.c"
    "src/lstate.c"
    "src/lstring.c"
    "src/lstrlib.c"
    "src/ltable.c"
    "src/ltablib.c"
    "src/ltm.c"
    #"src/lua.c"
    #"src/luac.c"
    "src/lundump.c"
    "src/lvm.c"
    "src/lzio.c"
    "src/print.c"
)

set(
    INNER_HDR
    "src/lapi.h"
    "src/lauxlib.h"
    "src/lcode.h"
    "src/ldebug.h"
    "src/ldo.h"
    "src/lfunc.h"
    "src/lgc.h"
    "src/llex.h"
    "src/llimits.h"
    "src/lmathlib.c"
    "src/lmem.h"
    "src/lobject.h"
    "src/lopcodes.h"
    "src/lparser.h"
    "src/lstate.h"
    "src/lstring.h"
    "src/ltable.h"
    "src/ltm.h"
    "src/luaconf.h"
    "src/lua.h"
    "src/lualib.h"
    "src/lundump.h"
    "src/lvm.h"
    "src/lzio.h"
)

set(
    ALL_SRC 
    ${MAIN_SRC} 
    ${INNER_SRC}
)

set(
    ALL_HDR
    ${MAIN_HDR}
    ${INNER_HDR}
)

set(luaplus_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/luaplus)

add_library(luaplus STATIC 
    ${ALL_SRC}
    ${ALL_HDR}
)

# Install headers
install(FILES ${ALL_HDR}
    DESTINATION ${luaplus_BINARY_DIR}/include/luaplus)


