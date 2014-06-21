#include "cell_game.h"
#include "lua_cell_game.h"

extern "C" {
#include <lua.h>
}

cell_game::cell_game(const std::string& level, const std::string& robot)
		: level(level)
{
	pos = this->level.find_source();

	this->robot.open_base();

	lua_pushcfunction(this->robot.L, luaopen_cell);
	lua_call(this->robot.L, 0, 0);

	this->robot.context = this;
	this->robot.load_file(robot);
}

int cell_game::start() {
	steps = 0;
	win = false;
	robot.call();
	return win;
}

int cell_game::go(direction dir) {
	++steps;

	position next_pos = pos;
	if (dir == direction::UP) {
		--next_pos.y;
	} else if (dir == direction::DOWN) {
		++next_pos.y;
	} else if (dir == direction::LEFT) {
		--next_pos.x;
	} else if (dir == direction::RIGHT) {
		++next_pos.x;
	}

	auto cell = level.cell(next_pos.x, next_pos.y);
	if (cell == cell_type::WALL || cell == cell_type::UNKNOWN) {
		return 0;
	}

	pos = next_pos;

	if (cell == cell_type::TARGET) {
		win = true;
		return -1;
	} else {
		return 1;
	}
}
