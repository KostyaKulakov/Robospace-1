#include "../cell_game/cell_level.h"
#include "../cell_game/cell_game.h"

#include <gtest/gtest.h>

TEST(cell_level_test, load_file) {
	cell_level level("tests/files/cell_game/1.level");

	constexpr auto e = cell_type::EMPTY;
	constexpr auto w = cell_type::WALL;
	constexpr auto s = cell_type::SOURCE;
	constexpr auto t = cell_type::TARGET;
	constexpr auto u = cell_type::UNKNOWN;

	constexpr int N = 6;
	constexpr int M = 11;

	cell_type map[N][M] = {
		{ w, w, w, w, w, s, w, w, w, e, u },
		{ t, e, e, w, w, e, e, e, w, e, u },
		{ w, w, e, e, e, w, w, e, w, e, u },
		{ w, e, e, w, e, e, e, e, w, e, u },
		{ w, w, w, w, w, w, w, w, w, e, u },
		{ u, u, u, u, u, u, u, u, u, u, u },
	};

	EXPECT_EQ(u, level.cell(-1, 0));
	EXPECT_EQ(u, level.cell(0, -1));

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			EXPECT_EQ(map[i][j], level.cell(i, j));
		}
	}
}

TEST(cell_game_test, game) {
	cell_game game("tests/files/cell_game/1.level",
			"tests/files/cell_game/2.lua");
	position pos = game.get_position();
	EXPECT_EQ(0, pos.x);
	EXPECT_EQ(5, pos.y);
	EXPECT_EQ(1, game.start());

	std::cout << "Game ended in " << game.steps << " turns\n";
}
