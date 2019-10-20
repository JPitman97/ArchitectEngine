cmake_minimum_required(VERSION 2.6)
project(ARCHITECTENGINE)

add_library(ArchitectEngine
	src/ArchitectEngine/Core.cpp
	src/ArchitectEngine/Core.h
	src/ArchitectEngine/Entity.cpp
	src/ArchitectEngine/Entity.h
	src/ArchitectEngine/Component.cpp
	src/ArchitectEngine/Component.h
	src/ArchitectEngine/Renderer.cpp
	src/ArchitectEngine/Renderer.h
	src/ArchitectEngine/architectengine.h
)

link_directories(
	${CMAKE_SOURCE_DIR}/External/lib/msvc
)

target_include_directories(ArchitectEngine PUBLIC ${CMAKE_SOURCE_DIR}/External/include/msvc)

target_link_libraries(ArchitectEngine SDL2 opengl32 glew32) #Windows
#target_link_libraries(ArchitectEngine SDL2 GL GLU) #Linux

add_executable(ArcLight
	src/ArcLight/main.cpp
)

target_link_libraries(ArcLight ArchitectEngine)
