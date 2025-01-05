//+++++++++++++++++++++++++++++++++++++++++++++++++++++V2+++++++++++++++++++++++++++++++++++++++++++++++++++

#include <iostream>
#include <string>

using namespace std;

//+++++++++++++++++++++++++++++++++++++++++++++++Include Lua headers++++++++++++++++++++++++++++++++++++++++
extern "C"
{
#include "Lua/include/lua.h"
#include "Lua/include/lauxlib.h"
#include "Lua/include/lualib.h"
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//+++++++++++++++++++++++++++++++++++++++++++++++++++++Link Lua library for Windows+++++++++++++++++++++++++
#ifdef _WIN32
#pragma comment(lib, "Lua/lua54.lib")
#endif
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//+++++++++++++++++++++++++++++++++++++++++++++++++++++Check for error msg++++++++++++++++++++++++++++++++++
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

	

	//lua code compiller
	lua_State* L = luaL_newstate();

	//lua libs for handle math usage
	luaL_openlibs(L);

	if (Checklua(L, luaL_dofile(L, "Luascript.lua"))) {

		lua_getglobal(L, "a");
		if (lua_isnumber(L, -1)) {
			float result = (float)lua_tonumber(L, -1);
			cout << "result: " << result << endl;
		}
	}
	


	//stop lua virtual machine
	lua_close(L);
	return 0;
}