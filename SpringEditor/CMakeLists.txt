# ISU Flight simulator

project(SpringEditor)
cmake_minimum_required (VERSION 3.8)

# SpringEngine definitions

add_compile_definitions(SE_PLATEFORM_WINDOWS)

include_directories("../SpringEngine/include" "include/")

set(SRCS
	"src/SpringEditorApp.cpp"
	"src/EditorLayer.cpp"
)

set(IMGUI_SRCS
	"../SpringEngine/lib/ImGui/imgui.cpp"
	"../SpringEngine/lib/ImGui/imgui_demo.cpp"
	"../SpringEngine/lib/ImGui/imgui_tables.cpp"
	"../SpringEngine/lib/ImGui/imgui_widgets.cpp"
	"../SpringEngine/lib/ImGui/imgui_draw.cpp"
	"../SpringEngine/lib/ImGui/backends/imgui_impl_opengl3.cpp"
	"../SpringEngine/lib/ImGui/backends/imgui_impl_glfw.cpp"
)


add_executable (SpringEditor ${SRCS} ${IMGUI_SRCS})

target_link_libraries(SpringEditor PUBLIC SpringEngine)

target_precompile_headers(SpringEditor
  PUBLIC
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/include/pch.hpp>"
)


#add_custom_command(
#        TARGET SpringEditor
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#                "${CMAKE_CURRENT_SOURCE_DIR}/ressources/"
#                "${CMAKE_BINARY_DIR}/bin/ressources"
#)