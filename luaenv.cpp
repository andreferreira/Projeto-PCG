#include "luaenv.h"

lua_State* newState() {
	lua_State* l = lua_open();
	luaL_openlibs(l);
	return l;
}

void doLuaFile(lua_State* l,std::string file) {
	if (luaL_dofile(l, file.c_str())) {
			printf("%s\n", lua_tostring(l, -1));
	}
}

void registerFunction(lua_State* l, std::string name, lua_CFunction function) {
	lua_pushcfunction(l, function);
	lua_setglobal(l, name.c_str());
}

