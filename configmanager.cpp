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

static int regmap(lua_State *L) {
	m->push_front(lua_tostring(L, 1));
	return 0;
}

ConfigManager::ConfigManager() {
    lstate = NULL;
}

void ConfigManager::load() {
	if (lstate != NULL)
		lua_close(lstate);
	screen.clear();
	player.clear();
	maps.clear();
	scr = &screen;
	play = &player;
	m = &maps;
	lstate = newState();
	registerFunction(lstate, "regscreen", regscreen);
	registerFunction(lstate, "regplayer", regplayer);
	registerFunction(lstate, "regmap", regmap);
	doLuaFile(lstate,"configmanager.lua");
	doLuaFile(lstate,"config.lua");
}
