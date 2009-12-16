#include "maploader.h"
#include "luaenv.h"

static Mapa* mapa = NULL;

static int regmap (lua_State *L) {
	double width = lua_tonumber(L, 1);
	double height = lua_tonumber(L, 2);
	Ponto spawn;
	spawn.x = lua_tonumber(L, 3);
	spawn.y = lua_tonumber(L, 4);
	mapa->setSpawn(spawn);
	mapa->setTamanho(width,height);
	return 0;
}

static int regplatform (lua_State *L) {
	mapa->novaPlataforma(luaL_checknumber(L, 1), 
						 luaL_checknumber(L, 2), 
						 luaL_checknumber(L, 3),
						 luaL_checknumber(L, 4),
						 lua_toboolean(L, 5),
						 luaL_checknumber(L, 6),
						 luaL_checknumber(L, 7),
						 luaL_checknumber(L, 8));
	return 0;
}

static int regweapon (lua_State *L) {
	const char* nome = lua_tostring(L, 1);
	double x = lua_tonumber(L, 2);
	double y = lua_tonumber(L, 3);
	mapa->dropWeapon(nome, Ponto(x, y));
	return 0;
}

static int regenemy (lua_State *L) {
	const char* nome = lua_tostring(L, 1);
	double x = lua_tonumber(L, 2);
	double y = lua_tonumber(L, 3);
	mapa->game->spawnEnemy(nome, Ponto(x, y));
	return 0;
}

void MapLoader::load(std::string name, Mapa* m) {
	mapa = m;
	lua_State* l = newState();
	registerFunction(l,"regmap",regmap);
	registerFunction(l,"regplatform",regplatform);
	registerFunction(l,"regweapon",regweapon);
	registerFunction(l,"regenemy",regenemy);
	doLuaFile(l,"maploader.lua");
	doLuaFile(l,name.c_str());
	lua_close(l);
}
