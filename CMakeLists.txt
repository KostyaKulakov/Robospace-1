CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(robospace)

OPTION(TEST "Compile tests" OFF)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Weffc++ -Werror")

INCLUDE_DIRECTORIES(
)

ADD_SUBDIRECTORY(lua_sandbox)

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

find_package(vera++)
include(${VERA++_USE_FILE})
add_vera_targets(*.h *.cpp
	RECURSE
	ROOT "${CMAKE_SOURCE_DIR}/vera")
