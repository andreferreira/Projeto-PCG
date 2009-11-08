#include "maploader.h"
#include "luaenv.h"

static Mapa* mapa = NULL;

static int regmap (lua_State *L) {
	double width = lua_tonumber(L, 1);
	double height = lua_tonumber(L, 2);
	mapa->setTamanho(width,height);
	return 0;
}

static int regplatform (lua_State *L) {
	mapa->novaPlataforma(luaL_checknumber(L, 1), 
						 luaL_checknumber(L, 2), 
						 luaL_checknumber(L, 3),
						 luaL_checknumber(L, 4),
						 lua_toboolean(L, 5));
	return 0;
}


void MapLoader::load(std::string name, Mapa* m) {
	mapa = m;
	lua_State* l = newState();
	registerFunction(l,"regmap",regmap);
	registerFunction(l,"regplatform",regplatform);
	doLuaFile(l,"maploader.lua");
	doLuaFile(l,name.c_str());
	lua_close(l);
}
