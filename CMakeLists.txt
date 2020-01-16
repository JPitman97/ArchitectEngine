cmake_minimum_required(VERSION 2.6)
project(ARCHITECTENGINE)

include_directories(src)

add_library(ArchitectEngine
	src/ArchitectEngine/Core.cpp
	src/ArchitectEngine/Core.h
	src/ArchitectEngine/Entity.cpp
	src/ArchitectEngine/Entity.h
	src/ArchitectEngine/Component.cpp
	src/ArchitectEngine/Component.h
	src/ArchitectEngine/RendererComponent.cpp
	src/ArchitectEngine/RendererComponent.h
	src/ArchitectEngine/LuaComponent.cpp
	src/ArchitectEngine/LuaComponent.h
	src/ArchitectEngine/architectengine.h
	src/ArchitectEngine/Camera.cpp
	src/ArchitectEngine/Camera.h
	src/ArchitectEngine/ShaderProgram.cpp
	src/ArchitectEngine/ShaderProgram.h
	src/ArchitectEngine/Texture.cpp
	src/ArchitectEngine/Texture.h
	src/ArchitectEngine/Transform.cpp
	src/ArchitectEngine/Transform.h
	src/ArchitectEngine/VertexArray.cpp
	src/ArchitectEngine/VertexArray.h
	src/ArchitectEngine/VertexBuffer.cpp
	src/ArchitectEngine/VertexBuffer.h
	src/ArchitectEngine/TPCameraComponent.cpp
	src/ArchitectEngine/TPCameraComponent.h
	src/ArchitectEngine/TransformComponent.cpp
	src/ArchitectEngine/TransformComponent.h
	src/ArchitectEngine/ObjectLoader.h
	src/ArchitectEngine/Enviroment.cpp
	src/ArchitectEngine/Enviroment.h
	src/ArchitectEngine/Time.cpp
	src/ArchitectEngine/Time.h
	src/ArchitectEngine/SkyboxComponent.cpp
	src/ArchitectEngine/SkyboxComponent.h
	src/Architectengine/Input.cpp
	src/Architectengine/Input.h
	src/Architectengine/InputComponent.cpp
	src/Architectengine/InputComponent.h
	src/ArchitectEngine/BoxColliderComponent.cpp
	src/ArchitectEngine/BoxColliderComponent.h
)

link_directories(
	${CMAKE_SOURCE_DIR}/External/lib/msvc
)

target_include_directories(ArchitectEngine PUBLIC ${CMAKE_SOURCE_DIR}/External/include/msvc)

if(WIN32)
	target_link_libraries(ArchitectEngine SDL2 opengl32 glew32 lua53) #Windows
else()
	target_link_libraries(ArchitectEngine SDL2 GL GLU lua53) #Linux
endif()

add_executable(ArcLight
	src/ArcLight/main.cpp
)

target_link_libraries(ArcLight ArchitectEngine)
