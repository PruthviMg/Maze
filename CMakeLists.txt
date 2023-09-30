cmake_minimum_required(VERSION 3.5.1)
set(CMAKE_BUILD_TYPE Debug)

project(Maze)

set(CMAKE_CXX_FLAGS "-std=c++0x -g")
set(TARGET ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules/" ${CMAKE_MODULE_PATH})

find_package(SFML 2
  COMPONENTS    
    system window graphics network audio REQUIRED)

set(LIBS pthread sfml-graphics sfml-audio sfml-window sfml-system)

include_directories(
    ${CMAKE_SOURCE_DIR}/config/
    ${CMAKE_SOURCE_DIR}/resource/json/include/
    ${CMAKE_SOURCE_DIR}/src/Common/inc/
    ${CMAKE_SOURCE_DIR}/src/Logger/inc/
	${CMAKE_SOURCE_DIR}/src/Manager/api/
    ${CMAKE_SOURCE_DIR}/src/Manager/inc/
    ${CMAKE_SOURCE_DIR}/src/Platform/api/
    ${CMAKE_SOURCE_DIR}/src/Platform/inc/
)

file(GLOB_RECURSE ${PROJECT_NAME}_SOURCE_FILES
	Maze.cpp src/*.cpp
)	


add_executable(${TARGET} ${${PROJECT_NAME}_SOURCE_FILES})
target_link_libraries(${TARGET} ${LIBS})