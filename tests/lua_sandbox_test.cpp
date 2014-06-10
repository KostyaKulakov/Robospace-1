#include "../lua_sandbox/lua_sandbox.h"
#include <gtest/gtest.h>

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

TEST(lua_sandbox_test, create_destroy) {
	lua_sandbox lua;
}

static int my_function_called;
static int my_function(lua_State *) {
	++my_function_called;
	return 0;
}

TEST(lua_sandbox_test, register_function) {
	my_function_called = 0;
	lua_sandbox lua;
	lua.register_function("my_function", my_function);
	ASSERT_EQ(0, lua.load_file("tests/lua/my_function.lua")) << "Loading of file failed";
	ASSERT_EQ(0, lua.call()) << "Calling function failed";
	ASSERT_EQ(1, my_function_called) << "my_function is not called";
}

static int line_hook_called;
static void line_hook(lua_State *, lua_Debug *ar) {
	if (ar->event == LUA_HOOKLINE) {
		++line_hook_called;
	} else {
		FAIL();
	}
}

TEST(lua_sandbox_test, line_hook) {
	line_hook_called = 0;

	lua_sandbox lua;
	lua.sethook(&line_hook, LUA_MASKLINE);
	ASSERT_EQ(0, lua.load_file("tests/lua/line_hook.lua")) << "Failed to load file";
	ASSERT_EQ(0, lua.call()) << "Failed to call function";
	ASSERT_EQ(5, line_hook_called) << "Hook was called incorrect time";
}

TEST(lua_sandbox_test, fail_import) {
	lua_sandbox lua;

	ASSERT_EQ(0, lua.load_file("tests/lua/fail_import.lua")) << "Failed to load file";
	ASSERT_EQ(2, lua.call()) << "Failed to call function";
	EXPECT_TRUE(lua_isnil(lua.L, -2)) << "First value should be nil";
	EXPECT_TRUE(lua_isstring(lua.L, -1)) << "Second value should be string";
}

TEST(lua_sandbox_test, good_import) {
	lua_sandbox lua;

	lua.open_package();

	lua_createtable(lua.L, 0, 0);
	lua.set_module("success");

	ASSERT_EQ(0, lua.load_file("tests/lua/good_import.lua")) << "Failed to load file";
	ASSERT_EQ(0, lua.call()) << "Failed to call function";
}
