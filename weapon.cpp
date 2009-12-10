#include "weapon.h"
#include "shot.h"
#include "shotmanager.h"
#include "game.h"

void Weapon::desenha() {
	sprite.desenha();
}

void Weapon::fire(Ponto place, double angle, Shooter* _firedBy) {
	firedBy = _firedBy;
	lua_pushlightuserdata(lstate, (void *)this);
	lua_gettable(lstate, LUA_REGISTRYINDEX);//obter funcao do script
	//passar parametros
	lua_pushnumber(lstate, place.x);
	lua_pushnumber(lstate, place.y);
	lua_pushnumber(lstate, angle);
	lua_pushlightuserdata(lstate, this);
	
	if (lua_pcall(lstate,4,0,0) != 0)  /* do the call */
        printf("error: %s", lua_tostring(lstate, -1));
}
