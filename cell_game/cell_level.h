#ifndef CELL_LEVEL
#define CELL_LEVEL

#include <string>
#include <vector>

enum class cell_type { EMPTY, WALL, SOURCE, TARGET, UNKNOWN };

static inline cell_type get_cell_type(char c) {
	if (c == '.') {
		return cell_type::EMPTY;
	} else if (c == '#') {
		return cell_type::WALL;
	} else if (c == 's') {
		return cell_type::SOURCE;
	} else if (c == 't') {
		return cell_type::TARGET;
	}
	return cell_type::UNKNOWN;
}

class cell_level {
public:
	cell_level(const std::string& filename);

	cell_type cell(int x, int y) {
		if (x < 0 || unsigned(x) >= map.size() ||
				y < 0 || unsigned(y) >= map[x].size()) {
			return cell_type::UNKNOWN;
		}

		return get_cell_type(map[x][y]);
	}

private:
	std::vector<std::string> map;
};

#endif /* CELL_LEVEL */
