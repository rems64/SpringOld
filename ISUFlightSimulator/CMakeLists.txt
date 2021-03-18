# ISU Flight simulator

project(FlightSimulator)
cmake_minimum_required (VERSION 3.8)

# SpringEngine definitions

add_compile_definitions(SE_PLATEFORM_WINDOWS)

include_directories("../SpringEngine/include")

set(SRCS
	"FlightSimulator.cpp"
 "FlightSimulatorApp.cpp")

add_executable (FlightSimulator ${SRCS})
target_link_libraries(FlightSimulator PUBLIC SpringEngine)