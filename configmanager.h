#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <map>
#include <list>
#include <string>

#include "geometry.h"

struct lua_State;

class ConfigManager {
	private:
		lua_State* lstate;
		std::list<std::string> maps;
		std::list<std::string>::iterator map;
	public:
		std::map<std::string, int> screen;
		std::map<std::string, Ponto> player;
		std::string previousMap();
		std::string currentMap();
		std::string nextMap();
		ConfigManager();
		void load();
};

#endif
