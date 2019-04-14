cmake_minimum_required (VERSION 2.6)
project (FuzzyCarAI)
# The version number.
set (FuzzyCar_VERSION_MAJOR 1)
set (FuzzyCar_VERSION_MINOR 0)

# Configure a header file to pass some of the CMake settings
# to the source code.
configure_file (
	"${PROJECT_SOURCE_DIR}/FuzzyCarAIConfig.h.in"
	"&{PROJECT_BINARY_DIR}/FuzzyCarAIConfig.h"
	)

# Add the binary tree to the search path for include files
# so that we will find FuzzyCarAIConfig.h.
include_directories("${PROJECT_BINARY_DIR}")

# Add the executable. 
add_executable (FuzzyCarAI Source.cpp)