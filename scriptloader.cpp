#include "scriptloader.h"

void luaRun::registerScripts() {
	registerScript("helloworld.lua");
}

void luaRun::registerScript(const std::string name) {
	Script novo(name);
	scripts.push_back(novo);
}

void luaRun::loadScripts() {
	std::vector<Script >::iterator it;
	for (it = scripts.begin();it != scripts.end(); it++) {
		if (it->L != NULL) lua_close(it->L);
		it->L = lua_open();
		luaL_openlibs(it->L);
		if (luaL_dofile(it->L, it->name.c_str())) {
			printf("%s\n", lua_tostring(it->L, -1));
		}

	}
	
}
