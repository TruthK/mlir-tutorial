# CMake minimum version and project information
cmake_minimum_required(VERSION 3.13.4)
project(mlir-toy VERSION 0.0.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Generate compile_commands.json for IDEs
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

# Define paths to MLIR and LLVM
set(MLIR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/llvm-project/build/lib/cmake/mlir)
set(LLVM_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/llvm-project/build/lib/cmake/llvm)

# Find the MLIR and LLVM packages
find_package(MLIR REQUIRED CONFIG)
find_package(LLVM REQUIRED CONFIG)

list(APPEND CMAKE_MODULE_PATH "${MLIR_CMAKE_DIR}")
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")

message(STATUS "Using MLIRConfig.cmake in: ${MLIR_CMAKE_DIR}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_CMAKE_DIR}")

include(TableGen)
include(AddLLVM)
include(AddMLIR)
include(HandleLLVMOptions)

# Add include directories
include_directories(${LLVM_INCLUDE_DIRS} ${MLIR_INCLUDE_DIRS})
# add_definitions(${LLVM_DEFINITIONS})

# Set the libraries to link against
set(MLIR_LIBS
    MLIRIR
    MLIRParser
    MLIRPass
    MLIRTransforms
    MLIRSupport
    # Add additional MLIR libraries as needed
)

set(LLVM_LIBS
    LLVMSupport
    LLVMCore
    # Add additional LLVM libraries as needed
)

# Add the executable and link libraries
add_executable(mlir-toy tools/tutorial-opt.cpp)
target_link_libraries(mlir-toy PRIVATE ${MLIR_LIBS} ${LLVM_LIBS})
