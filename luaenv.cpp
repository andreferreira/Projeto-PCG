#include "luaenv.h"

void luaRun::registerScripts() {
	registerScript("helloworld.lua");
}

void luaRun::registerScript(const std::string &name) {
	Script novo(name);
	scripts.push_back(novo);
}

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

void luaRun::loadScripts() {
	std::vector<Script >::iterator it;
	for (it = scripts.begin();it != scripts.end(); it++) {
		if (it->L != NULL) lua_close(it->L);
		it->L = newState();
		doLuaFile(it->L,it->name);
	}
	
}
