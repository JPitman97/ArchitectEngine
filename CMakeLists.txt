cmake_minimum_required(VERSION 2.6)
project(ARCANEENGINE)

add_library(ArcaneEngine
	src/ArcaneEngine/dummy.cpp
)
target_link_libraries(ArcaneEngine SDL2 opengl32 glew32)

add_executable(ArcLight
	src/ArcLight/main.cpp
)
target_link_libraries(ArcLight ArcaneEngine)