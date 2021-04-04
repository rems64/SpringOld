# ISU Flight simulator

project(FlightSimulator)
cmake_minimum_required (VERSION 3.8)

# SpringEngine definitions

add_compile_definitions(SE_PLATEFORM_WINDOWS)

include_directories("../SpringEngine/include")

set(SRCS
	
 "src/FlightSimulatorApp.cpp" )



add_executable (FlightSimulator ${SRCS})

target_link_libraries(FlightSimulator PUBLIC SpringEngine)

#file(COPY "ressources/" DESTINATION ${CMAKE_BINARY_DIR}/ressources)
add_custom_command(
        TARGET FlightSimulator
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${CMAKE_CURRENT_SOURCE_DIR}/ressources/"
                "${CMAKE_BINARY_DIR}/bin/ressources"
)