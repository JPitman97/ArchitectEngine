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
	src/ArchitectEngine/AudioComponent.cpp
	src/ArchitectEngine/AudioComponent.h
	src/ArchitectEngine/SceneManager.cpp
	src/ArchitectEngine/SceneManager.h
    src/ArchitectEngine/Scene.cpp
	src/ArchitectEngine/Scene.h
)

link_directories(
	${CMAKE_SOURCE_DIR}/External/lib/msvc
)

target_include_directories(ArchitectEngine PUBLIC ${CMAKE_SOURCE_DIR}/External/include/msvc)

if(WIN32)
	target_link_libraries(ArchitectEngine glfw3 OpenAL32 opengl32 glew32 lua53 assimp) #Windows
else()
	find_package(PkgConfig REQUIRED)
	pkg_search_module(GLFW REQUIRED glfw3)
	find_package(GLEW REQUIRED)
	
	target_link_libraries(ArchitectEngine ${GLFW_LIBRARIES} GL ${GLEW_LIBRARIES} assimp lua53 OpenAL32) #Linux
endif()

add_executable(ArcLight
	src/ArcLight/main.cpp
)

target_link_libraries(ArcLight ArchitectEngine)

add_custom_command(TARGET ArcLight
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
		"${PROJECT_SOURCE_DIR}/External/lib/msvc/OpenAL32.dll"
		"${PROJECT_SOURCE_DIR}/External/lib/msvc/glew32.dll"
		"${PROJECT_SOURCE_DIR}/External/lib/msvc/lua53.dll"
		"${PROJECT_SOURCE_DIR}/External/lib/msvc/glfw3.dll"
		$<TARGET_FILE_DIR:ArcLight>
)
