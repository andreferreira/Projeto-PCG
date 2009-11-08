#ifndef SCRIPTLOADER_H
#define SCRIPTLOADER_H

extern "C" {
#include "lua/lua.h"
#include "lua/lauxlib.h"
#include "lua/lualib.h"
}

#include <string>
#include <vector>

class Script {
	public:
		std::string name;
		lua_State* L;
		Script(std::string name) { this->name = name; L = NULL;}
};

lua_State* newState();
void doLuaFile(lua_State* l,std::string file);
void registerFunction(lua_State* l, std::string name, lua_CFunction function);

class luaRun {
	public:
		void loadScripts();
		void registerScripts();
	private:
		void registerScript(const std::string &name);
		std::vector<Script> scripts;
};

#endif
