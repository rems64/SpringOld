# Spring Engine

cmake_minimum_required (VERSION 3.8)

project(SpringEngine VERSION 1.0.0)

# SpringEngine definitions
add_compile_definitions(SE_PLATEFORM_WINDOWS)
add_compile_definitions(SE_BUILD_DLL)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_compile_definitions(SE_DEBUG)
endif()

include_directories( "include/" "lib/ImGui" "lib/ImGuizmo-master" "lib/ImGui/backends" "lib/GLFW/include" "lib/GLEW/include" "include/external" "lib/spdlog/include" "lib/Assimp/Include" "lib/json/include" )

set(SRCS
	
	"src/Misc/Logger.cpp"
	"src/Misc/Macros.cpp"
	"src/Core/Application.cpp"
	
	"src/Core/DataManager.cpp"
	"src/Core/Layer.cpp"
	"src/Core/LayerStack.cpp"
	"src/Core/Scene.cpp"
	
	"src/Core/SpringObject.cpp"
	"src/Core/Window.cpp"
	"src/Graphics/IndexBuffer.cpp"
	"src/Graphics/Renderer.cpp"
	"src/Graphics/Shader.cpp"
	"src/Graphics/Texture.cpp"
	"src/Graphics/VertexArray.cpp"
	"src/Graphics/VertexBuffer.cpp"
	"src/Graphics/VertexBufferLayout.cpp"
	"src/Layers/DebugUILayer.cpp"
	"src/Layers/ImGuiLayer.cpp"
	"src/Layers/TestLayer.cpp"
	"src/Layers/WorldLayer.cpp"
	"src/Graphics/Material.cpp"
	"src/Misc/Instrumentor.cpp"
	"src/Core/Actor.cpp"
	"src/Core/Mesh.cpp"
	"src/Core/ActorComponent.cpp"
	"src/Core/SceneComponent.cpp"
	"src/Core/RenderedComponent.cpp"
	"include/SpringEngine/Core/MeshComponent.hpp"
	"src/Core/MeshComponent.cpp"
	"src/Core/CameraComponent.cpp"
	"src/Core/DataBlock.cpp"
	"src/Core/Box2D.cpp"
	"src/Graphics/Framebuffer.cpp"
	"src/Core/FileDialogs.cpp"
	"src/Core/ParticleEmitter.cpp"
	"src/Core/Math.cpp"
	"src/Core/ParticleEmitterComponent.cpp"
	"src/UI/ImGuiMisc.cpp"
	"src/Core/Asset.cpp"
	"src/Core/AssetsManager.cpp"
	"src/Core/LightComponent.cpp"
	"src/Core/Light.cpp"
	"src/Core/PointLightComponent.cpp"
	"src/Editor/EditorCamera.cpp"
	 "src/Core/EditorCameraComponent.cpp" "src/Core/Pawn.cpp" "src/Core/Character.cpp" "src/Core/InputManager.cpp" "src/Core/Input.cpp")

set(IMGUI_SRCS
	"lib/ImGui/imgui.cpp"
	"lib/ImGui/imgui_demo.cpp"
	"lib/ImGui/imgui_tables.cpp"
	"lib/ImGui/imgui_widgets.cpp"
	"lib/ImGui/imgui_draw.cpp"
	"lib/ImGui/backends/imgui_impl_opengl3.cpp"
	"lib/ImGui/backends/imgui_impl_glfw.cpp"
	"lib/ImGuizmo-master/ImGuizmo.cpp"
)

set(OPENFBX_SRCS
	"lib/OpenFBX/src/miniz.c"
	"lib/OpenFBX/src/ofbx.cpp"
)

add_library(SpringEngine SHARED ${SRCS} ${IMGUI_SRCS} ${OPENFBX_SRCS})

target_include_directories(SpringEngine PUBLIC "lib/ImGui" "lib/ImGuizmo-master" "lib/ImGui/backends" "lib/GLFW/include" "lib/GLEW/include" "include/external" "lib/spdlog/include" "lib/OpenFBX/include" "lib/Assimp/Include/" "lib/json/include" )
#target_include_directories(test PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}lib/FBXImporter/importer/include")

find_package(OpengL REQUIRED COMPONENTS OpengL)

target_precompile_headers(SpringEngine
  PUBLIC
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/src/pch.hpp>"
)

add_subdirectory("lib/spdlog")

#target_link_libraries(test FBXImport)

target_link_libraries(SpringEngine "./lib/GLFW/glfw3")
target_link_libraries(SpringEngine "./lib/GLEW/glew32")
target_link_libraries(SpringEngine "./lib/freetype/freetype")
target_link_libraries(SpringEngine "./lib/FMOD/fmod_vc")
target_link_libraries(SpringEngine "./lib/FMOD/fmodstudio_vc")
target_link_libraries(SpringEngine "./lib/Assimp/Release/assimp-vc141-mt")
target_link_libraries(SpringEngine OpenGL::GL)

file(COPY "lib/GLFW/lib-vc2019/glfw3.lib" DESTINATION ${CMAKE_BINARY_DIR}/lib/GLFW/)
file(COPY "lib/GLFW/lib-vc2019/glfw3.dll" DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY "lib/GLEW/lib/glew32.lib" DESTINATION ${CMAKE_BINARY_DIR}/lib/GLEW/)
file(COPY "lib/GLEW/bin/Release/x64/glew32.dll" DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY "lib/freetype/freetype.lib" DESTINATION ${CMAKE_BINARY_DIR}/lib/freetype/)
file(COPY "lib/freetype/freetype.dll" DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY "lib/FMOD/fmod_vc.lib" DESTINATION ${CMAKE_BINARY_DIR}/lib/FMOD/)
file(COPY "lib/FMOD/fmod.dll" DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY "lib/FMOD/fmodstudio_vc.lib" DESTINATION ${CMAKE_BINARY_DIR}/lib/FMOD/)
file(COPY "lib/FMOD/fmodstudio.dll" DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY "lib/Assimp/assimp-vc141-mt.dll" DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY "lib/Assimp/Release/assimp-vc141-mt.lib" DESTINATION ${CMAKE_BINARY_DIR}/lib/Assimp/Release)

set_target_properties(SpringEngine PROPERTIES PUBLIC_HEADER "include/SpringEngine/SpringEngine.hpp")