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
