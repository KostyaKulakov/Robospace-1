#ifndef LUA_SANDBOX_H
#define LUA_SANDBOX_H

#include <string>

extern "C" {
#include <lua.h>
#include <lauxlib.h>
}

class lua_sandbox {
public:
	lua_sandbox() : L(lua_open()) {
	}

	~lua_sandbox() {
		lua_close(L);
	}

	lua_sandbox(const lua_sandbox& copy) = delete;
	void operator=(const lua_sandbox& copy) = delete;

	void register_function(const std::string& name, lua_CFunction function);
	int load_file(const std::string& filename);
	int call();
	void sethook(lua_Hook hook, int mask, int count = 0);

	lua_State *L;
};

#endif /* LUA_SANDBOX_H */
