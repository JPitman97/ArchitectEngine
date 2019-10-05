cmake_minimum_required(VERSION 2.6)
project(ARCHITECTENGINE)

add_library(ArchitectEngine
	src/ArchitectEngine/dummy.cpp
	src/ArchitectEngine/dummy.h
)

link_directories(
	${CMAKE_SOURCE_DIR}/External/lib/msvc
)

target_include_directories(ArchitectEngine PUBLIC ${CMAKE_SOURCE_DIR}/External/include/msvc)

target_link_libraries(ArchitectEngine SDL2 GL GLU)

add_executable(ArcLight
	src/ArcLight/main.cpp
)

target_link_libraries(ArcLight ArchitectEngine)
