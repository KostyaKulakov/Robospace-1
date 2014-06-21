SET(CELL_GAME_SOURCES
	cell_level.cpp
	cell_game.cpp
	lua_cell_game.cpp
)

ADD_LIBRARY(cell_game_lib ${CELL_GAME_SOURCES})

TARGET_LINK_LIBRARIES(cell_game_lib lua_sandbox)
