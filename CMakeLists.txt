CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(robospace)

OPTION(TEST "Compile tests" OFF)
OPTION(VERA "Perform style check" OFF)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Weffc++ -Werror -fno-exceptions")

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR})

ADD_SUBDIRECTORY(lua_sandbox)
ADD_SUBDIRECTORY(cell_game)

IF(TEST)
	ADD_SUBDIRECTORY(tests)
ENDIF(TEST)

ADD_EXECUTABLE(robospace main.cpp)

TARGET_LINK_LIBRARIES(robospace
	lua_sandbox
)

ADD_CUSTOM_TARGET(check
	COMMAND cppcheck -q . --template gcc
	WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")

IF(VERA)
	find_package(vera++)
	include(${VERA++_USE_FILE})
	add_vera_targets(*.h *.cpp
		RECURSE
		ROOT "${CMAKE_SOURCE_DIR}/vera")
ENDIF(VERA)
