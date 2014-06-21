#include "cell_level.h"

#include <fstream>

cell_level::cell_level(const std::string& filename) {
	std::ifstream fin;
	fin.open(filename, std::ifstream::in);

	while (fin) {
		std::string line;
		std::getline(fin, line);
		map.push_back(line);
	}
}

position cell_level::find_source() {
	for (unsigned i = 0; i < map.size(); ++i) {
		auto& line = map[i];
		auto line_size = line.size();
		for (unsigned j = 0; j < line_size; ++j) {
			if (line[j] == 's') {
				return { int(i), int(j) };
			}
		}
	}
	return { -1, -1 };
}
