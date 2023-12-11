cmake_minimum_required(VERSION 3.12)
project(PuzzleSolver)

set(CMAKE_CXX_STANDARD 17)

# Set the path to the installed OR-Tools directory
set(ORTOOLS_INSTALL_DIR "/usr/local/Cellar/or-tools/9.8_1")

# Include directories for OR-Tools and Abseil
include_directories(
    ${ORTOOLS_INSTALL_DIR}/include
    ${ORTOOLS_INSTALL_DIR}/include/third_party/absl
)

# Link directories
link_directories(${ORTOOLS_INSTALL_DIR}/lib)

# Add your source files
add_executable(PuzzleSolver src/kubok.cpp src/main.cpp)

# Link against OR-Tools library
target_link_libraries(PuzzleSolver ortools)
