#include "configmanager.h"
#include "luaenv.h"

static std::map<std::string, int> *scr = NULL;
static std::map<std::string, Ponto> *play = NULL;
static std::list<std::string> *m = NULL;

static int regscreen(lua_State *L) {
	const char *name = lua_tostring(L, 1);
	double value = lua_tonumber(L, 2);
	(*scr)[name] = (int) value;
	return 0;
}

static int regplayer(lua_State *L) {
	const char *name = lua_tostring(L, 1);
	double x = lua_tonumber(L, 2);
	double y = lua_tonumber(L, 3);
	(*play)[name] = Ponto(x, y);
	return 0;
}

static int regplayerhp(lua_State *L) {
	const char *name = lua_tostring(L, 1);
	double x = lua_tonumber(L, 2);
	(*scr)[name] = x;
	return 0;
}

static int regmap(lua_State *L) {
	m->push_back(lua_tostring(L, 1));
	return 0;
}

ConfigManager::ConfigManager() {
    lstate = NULL;
}

std::string ConfigManager::previousMap() {
	return map != maps.begin() ? *(--map) : *map;
}

std::string ConfigManager::currentMap() {
	return *map;
}

std::string ConfigManager::nextMap() {
	return map != --(maps.end()) ? *(++map) : *map;
}

void ConfigManager::load() {
	if (lstate != NULL)
		lua_close(lstate);
	integer.clear();
	ponto.clear();
	maps.clear();
	scr = &integer;
	play = &ponto;
	m = &maps;
	lstate = newState();
	registerFunction(lstate, "regscreen", regscreen);
	registerFunction(lstate, "regplayer", regplayer);
	registerFunction(lstate, "regplayerhp", regplayerhp);
	registerFunction(lstate, "regmap", regmap);
	doLuaFile(lstate,"configmanager.lua");
	doLuaFile(lstate,"config.lua");
	map = maps.begin();
}
