# ISU Flight simulator

project(ISUFlightSimulator)
cmake_minimum_required (VERSION 3.8)

# SpringEngine definitions

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

add_compile_definitions(SE_PLATEFORM_WINDOWS)

include_directories("../SpringEngine/include")

set(SRCS
 "src/FlightSimulatorApp.cpp"  )



add_executable (ISUFlightSimulator ${SRCS})

target_link_libraries(ISUFlightSimulator PUBLIC SpringEngine)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("On n'enlève pas la console")
else()
    message("On enlève la console")
    set_target_properties(ISUFlightSimulator PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup /SUBSYSTEM:WINDOWS")
endif()
#file(COPY "ressources/" DESTINATION ${CMAKE_BINARY_DIR}/ressources)
add_custom_command(
        TARGET ISUFlightSimulator
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${CMAKE_CURRENT_SOURCE_DIR}/ressources/"
                "${CMAKE_BINARY_DIR}/bin/ressources"
)