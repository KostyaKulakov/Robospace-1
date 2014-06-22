#include "lua_cell_game.h"

#include <lua_sandbox/lua_sandbox.h>
#include "cell_level.h"
#include "cell_game.h"

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

static int l_go(lua_State *L) {
	direction dir = static_cast<direction>(luaL_checknumber(L, 1));
	lua_sandbox *sandbox = lua_sandbox::get_from_state(L);
	cell_game *game = static_cast<cell_game *>(sandbox->context);
	int result = game->go(dir);
	if (result == -1) {
		lua_pushstring(L, "Game is over!");
		lua_error(L);
	}
	lua_pushboolean(L, result);
	return 1;
}

void abort_hook(lua_State *L, lua_Debug *) {
	lua_pushstring(L, "You loose");
	lua_error(L);
}

int luaopen_cell(lua_State *L) {
	lua_pushnumber(L, static_cast<int>(direction::LEFT));
	lua_setglobal(L, "LEFT");
	lua_pushnumber(L, static_cast<int>(direction::UP));
	lua_setglobal(L, "UP");
	lua_pushnumber(L, static_cast<int>(direction::DOWN));
	lua_setglobal(L, "DOWN");
	lua_pushnumber(L, static_cast<int>(direction::RIGHT));
	lua_setglobal(L, "RIGHT");
	lua_pushnumber(L, static_cast<int>(direction::STAY));
	lua_setglobal(L, "STAY");

	lua_pushcfunction(L, l_go);
	lua_setglobal(L, "go");
	return 0;
}
