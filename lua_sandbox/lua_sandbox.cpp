#include "lua_sandbox.h"

#include <iostream>

void lua_sandbox::register_function(const std::string& name, lua_CFunction function) {
	lua_pushcfunction(L, function);
	lua_setglobal(L, name.c_str());
}

int lua_sandbox::load_file(const std::string& filename) {
	return luaL_loadfile(L, filename.c_str());
}

int lua_sandbox::call() {
	return lua_pcall(L, 0, LUA_MULTRET, 0);
}

void lua_sandbox::sethook(lua_Hook hook, int mask, int count) {
	lua_sethook(L, hook, mask, count);
}
