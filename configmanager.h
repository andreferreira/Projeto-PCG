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
	public:
		std::map<std::string, int> screen;
		std::map<std::string, Ponto> player;
		std::list<std::string> maps;
		ConfigManager();
		void load();
};

#endif
