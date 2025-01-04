#include <iostream>
#include <string>



//+++++++++++++++++++++++++++++++++++++++++++++++Include Lua headers++++++++++++++++++++++++++++++++++++++++
extern "C"
{
#include  "Lua/include/lua.h"
#include "Lua/include/lauxlib.h"
#include "Lua/include/lualib.h"
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++Link Lua library for Windows+++++++++++++++++++++++++
#ifdef _WIN32
#pragma comment(lib, "Lua/lua54.lib")
#endif
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


using namespace std;

int main() {

	string cmd = "a = 7 + 165";

	//lua code compiller
	lua_State* L = luaL_newstate();

	int r = luaL_dostring(L, cmd.c_str());


	//validation
	if (r == LUA_OK) {

		//extract value a as number so we can display it
		lua_getglobal(L, "a");
		if (lua_isnumber(L, -1))
		{
			float a_in_cpp = (float)lua_tonumber(L, -1);
			cout << "a_in_cpp = " << a_in_cpp << endl;
		}

	}else
	{
		string errormsg = lua_tostring(L, -1);
		cout << errormsg << endl;

	}

	//stop lua virtual machine
	lua_close(L);
	return 0;
}