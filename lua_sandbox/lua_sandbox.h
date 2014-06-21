#ifndef LUA_SANDBOX_H
#define LUA_SANDBOX_H

#include <string>
#include <map>

extern "C" {
#include <lua.h>
#include <lauxlib.h>
}

class lua_sandbox {
public:
	lua_sandbox() : L(luaL_newstate()) {
		if (L) {
			luas.insert(std::make_pair(L, this));
		}
	}

	~lua_sandbox() {
		if (L) {
			lua_close(L);
			luas.erase(L);
		}
	}

	lua_sandbox(const lua_sandbox& copy) = delete;
	void operator=(const lua_sandbox& copy) = delete;

	void register_function(const std::string& name, lua_CFunction function);
	int load_file(const std::string& filename);
	int call();
	void sethook(lua_Hook hook, int mask, int count = 0);

	void open_base();
	void open_package();

	void set_module(const char *name);

	lua_State *L;
	void *context;

	static lua_sandbox *get_from_state(lua_State *L) {
		return luas[L];
	}

	static std::map<lua_State *, lua_sandbox *> luas;
};

#endif /* LUA_SANDBOX_H */
