#include "lua_sandbox.h"

extern "C" {
#include <lualib.h>
}

#include <iostream>

std::map<lua_State *, lua_sandbox *> lua_sandbox::luas;

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

void lua_sandbox::open_package() {
	lua_pushcfunction(L, luaopen_package);
	lua_call(L, 0, 0);
}

void lua_sandbox::open_base() {
	lua_pushcfunction(L, luaopen_base);
	lua_call(L, 0, 0);
}

void lua_sandbox::set_module(const char *name) {
	lua_getglobal(L, "package");
	lua_getfield(L, -1, "loaded");
	lua_insert(L, -3);
	lua_pop(L, 1);
	lua_setfield(L, -2, name);
	lua_pop(L, 1);
}
