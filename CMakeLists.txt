cmake_minimum_required(VERSION 3.8) 
project(ARCHITECTENGINE)

include_directories(src)

add_library(ArchitectEngine
	External/include/msvc/glad/glad.c # Glad extension library
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

target_include_directories(ArchitectEngine PUBLIC ${CMAKE_SOURCE_DIR}/External/include/msvc)

target_link_directories(ArchitectEngine PUBLIC ${CMAKE_SOURCE_DIR}/External/lib/msvc)

if(WIN32)
	list(APPEND CMAKE_PREFIX_PATH "C:\\SDKs\\ReactPhysics3D\\64-Bit")
	find_package(ReactPhysics3D REQUIRED) 
	target_link_libraries(ArchitectEngine glfw3 OpenAL32 opengl32 lua53 ReactPhysics3D::ReactPhysics3D) #Windows
else()
	find_package(PkgConfig REQUIRED)
	pkg_search_module(GLFW REQUIRED glfw3)
	find_package(GLEW REQUIRED)
	
	target_link_libraries(ArchitectEngine ${GLFW_LIBRARIES} GL lua53 OpenAL32 ReactPhysics3D::ReactPhysics3D) #Linux
endif()

add_executable(ArcLight
	src/ArcLight/main.cpp
)

target_link_libraries(ArcLight ArchitectEngine)

add_custom_command(TARGET ArcLight
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
		"${PROJECT_SOURCE_DIR}/External/lib/msvc/OpenAL32.dll"
		"${PROJECT_SOURCE_DIR}/External/lib/msvc/lua53.dll"
		"${PROJECT_SOURCE_DIR}/External/lib/msvc/glfw3.dll"
		$<TARGET_FILE_DIR:ArcLight>
)
