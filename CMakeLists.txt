cmake_minimum_required(VERSION 3.18) 
project(ARCHITECTENGINE)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include_directories(src)

set(GLAD External/include/msvc/glad/glad.c) # Glad extension library
set(DEARIMGUI
	External/include/msvc/dearimgui/imgui.cpp
	External/include/msvc/dearimgui/imgui.h
	External/Include/msvc/dearimgui/imgui_demo.cpp
	External/include/msvc/dearimgui/imconfig.h
	External/include/msvc/dearimgui/imgui_impl_glfw.cpp
	External/include/msvc/dearimgui/imgui_impl_glfw.h
	External/include/msvc/dearimgui/imgui_impl_opengl3.cpp
	External/include/msvc/dearimgui/imgui_impl_opengl3.h
	External/include/msvc/dearimgui/imgui_internal.h
	External/include/msvc/dearimgui/imgui_widgets.cpp
	External/include/msvc/dearimgui/imgui_draw.cpp
	External/include/msvc/dearimgui/imstb_rectpack.h
	External/include/msvc/dearimgui/imstb_textedit.h
	External/include/msvc/dearimgui/imstb_truetype.h
)
set(COMPONENTS
	src/ArchitectEngine/RendererComponent.cpp
	src/ArchitectEngine/RendererComponent.h
	src/ArchitectEngine/LuaComponent.cpp
	src/ArchitectEngine/LuaComponent.h
	src/ArchitectEngine/TPCameraComponent.cpp
	src/ArchitectEngine/TPCameraComponent.h
	src/ArchitectEngine/TransformComponent.cpp
	src/ArchitectEngine/TransformComponent.h
	src/ArchitectEngine/SkyboxComponent.cpp
	src/ArchitectEngine/SkyboxComponent.h
	src/Architectengine/InputComponent.cpp
	src/Architectengine/InputComponent.h
	src/ArchitectEngine/BoxColliderComponent.cpp
	src/ArchitectEngine/BoxColliderComponent.h
	src/ArchitectEngine/RigidBodyComponent.cpp
	src/ArchitectEngine/RigidBodyComponent.h
)
add_library(ArchitectEngine
	${GLAD}
	${DEARIMGUI}
	${COMPONENTS}
	
	src/ArchitectEngine/Core.cpp
	src/ArchitectEngine/Core.h
	src/ArchitectEngine/Entity.cpp
	src/ArchitectEngine/Entity.h
	src/ArchitectEngine/Component.cpp
	src/ArchitectEngine/Component.h

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
	
	src/ArchitectEngine/Enviroment.cpp
	src/ArchitectEngine/Enviroment.h
	src/ArchitectEngine/Time.cpp
	src/ArchitectEngine/Time.h
	
	src/Architectengine/Input.cpp
	src/Architectengine/Input.h
	
	src/ArchitectEngine/AudioComponent.cpp
	src/ArchitectEngine/AudioComponent.h
	src/ArchitectEngine/SceneManager.cpp
	src/ArchitectEngine/SceneManager.h
    src/ArchitectEngine/Scene.cpp
	src/ArchitectEngine/Scene.h
)

source_group(glad FILES ${GLAD})
source_group(dearimgui FILES ${DEARIMGUI})
source_group(Components FILES ${COMPONENTS})

target_include_directories(ArchitectEngine PUBLIC ${CMAKE_SOURCE_DIR}/External/include/msvc)

target_link_directories(ArchitectEngine PUBLIC ${CMAKE_SOURCE_DIR}/External/lib/msvc)

if(WIN32)
	list(APPEND CMAKE_PREFIX_PATH "C:\\SDKs\\ReactPhysics3D\\64-Bit\\Debug")
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
