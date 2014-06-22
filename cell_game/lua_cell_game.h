#ifndef LUA_CELL_GAME
#define LUA_CELL_GAME

struct lua_State;
struct lua_Debug;

void abort_hook(lua_State *L, lua_Debug *ar);
int luaopen_cell(lua_State *L);

#endif /* LUA_CELL_GAME */
