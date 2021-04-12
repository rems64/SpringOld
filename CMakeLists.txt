# CMakeList.txt : fichier projet CMake de niveau supérieur, effectuez une configuration globale
# et incluez les sous-projets ici.
#
cmake_minimum_required (VERSION 3.8)

project(ISUFlightSimulator VERSION 0.1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Incluez les sous-projets.
add_subdirectory ("SpringEngine")
add_subdirectory ("ISUFlightSimulator")
add_subdirectory ("SpringEditor")