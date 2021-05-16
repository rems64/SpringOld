# ISU Flight simulator

project(Ecloshoot)
cmake_minimum_required (VERSION 3.8)

# SpringEngine definitions

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

add_compile_definitions(SE_PLATEFORM_WINDOWS)

include_directories("../SpringEngine/include")

set(SRCS
 "src/EcloshootApp.cpp"  )



add_executable (Ecloshoot ${SRCS})

target_link_libraries(Ecloshoot PUBLIC SpringEngine)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("On n'enleve pas la console")
else()
    message("On enleve la console")
    set_target_properties(Ecloshoot PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup /SUBSYSTEM:WINDOWS")
endif()
#file(COPY "ressources/" DESTINATION ${CMAKE_BINARY_DIR}/ressources)
add_custom_command(
        TARGET Ecloshoot
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${CMAKE_CURRENT_SOURCE_DIR}/ressources/"
                "${CMAKE_BINARY_DIR}/bin/ressources"
)