#ifndef SCRIPTLOADER_H
#define SCRIPTLOADER_H

extern "C" {
#include "lua/lua.h"
#include "lua/lauxlib.h"
#include "lua/lualib.h"
}

#include <string>
#include <vector>

lua_State* newState();
void doLuaFile(lua_State* l,std::string file);
void registerFunction(lua_State* l, std::string name, lua_CFunction function);

#endif
