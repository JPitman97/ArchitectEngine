cmake_minimum_required(VERSION 2.6)
project(ARCHITECTENGINE)

add_library(ArchitectEngine
	src/ArchitectEngine/dummy.cpp
)
target_link_libraries(ArchitectEngine SDL2 opengl32 glew32)

add_executable(ArcLight
	src/ArcLight/main.cpp
)
target_link_libraries(ArcLight ArchitectEngine)
