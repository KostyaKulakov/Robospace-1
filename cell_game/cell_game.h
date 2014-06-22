#ifndef CELL_GAME_H
#define CELL_GAME_H

#include <string>

#include "cell_level.h"
#include <lua_sandbox/lua_sandbox.h>

class cell_game {
public:
	cell_game(const std::string& level, const std::string& robot);

	void set_limit(int number);

	int start();

	int go(direction dir);

	position get_position() {
		return pos;
	}

	int steps;
private:
	cell_level level;
	lua_sandbox robot;

	position pos;

	bool win;
};

#endif /* CELL_GAME_H */
