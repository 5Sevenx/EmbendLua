//+++++++++++++++++++++++++++++++++++++++++++++++++++++ V3 ++++++++++++++++++++++++++++++++++++++++++++++++++

#include <iostream>
#include <string>

using namespace std;

//+++++++++++++++++++++++++++++++++++++++++++++++ Include Lua headers +++++++++++++++++++++++++++++++++++++++
extern "C"
{
#include "Lua/include/lua.h"
#include "Lua/include/lauxlib.h"
#include "Lua/include/lualib.h"
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//+++++++++++++++++++++++++++++++++++++++++++++++++++++ Link Lua library for Windows ++++++++++++++++++++++++
#ifdef _WIN32
#pragma comment(lib, "Lua/lua54.lib")
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//+++++++++++++++++++++++++++++++++++++++++++++++++++++ Check for error msg +++++++++++++++++++++++++++++++++
bool Checklua(lua_State* L, int r) {

	if (r != LUA_OK) {
		string errormsg = lua_tostring(L, -1);
		cout << errormsg << endl;
		return false;
	}
	return true;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


int main() {


	struct Player {
		string title;
		string name; 
		string family;
		int level;

	} player;


	//lua code compiller
	lua_State* L = luaL_newstate();


	//lua libs for handle math usage
	luaL_openlibs(L);


//++++++++++++++++++++++++++++++++++++++ Interaction between Lua and C +++++++++++++++++++++++++++++++++++++
	if (Checklua(L, luaL_dofile(L, "Luascript.lua"))) {

		lua_getglobal(L, "PlayerTitle");
		if (lua_isstring(L, -1)) {
			player.title = lua_tostring(L, -1);
		}

		lua_getglobal(L, "PlayerName");
		if (lua_isstring(L, -1)) {
			player.name = lua_tostring(L, -1);
		}

		lua_getglobal(L, "PlayerFamily");
		if (lua_isstring(L, -1)) {
			player.family = lua_tostring(L, -1);
		}

		lua_getglobal(L, "PlayerLevel");
		if (lua_isnumber(L, -1)) {
			player.level = lua_tonumber(L, -1);
		}
	}

	cout << player.title << " " << player.name << " of " << player.family << " [Lvl:" << player.level << "]" << endl;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	


	//stop lua virtual machine
	lua_close(L);
	return 0;
}