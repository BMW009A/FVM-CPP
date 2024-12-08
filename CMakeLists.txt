cmake_minimum_required(VERSION 3.26)
project(Project_02_FVM LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable verbose makefile generation (optional for debugging purposes)
set(CMAKE_VERBOSE_MAKEFILE ON)

# Find the OpenMP package
find_package(OpenMP REQUIRED)

if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}" /openmp::llvm)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}" /openmp::llvm)
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)

# For macOS: Enable macOS-specific compiler/linker flags
if (APPLE)
    # Choose the appropriate architecture-specific flags
    if (CMAKE_SYSTEM_PROCESSOR MATCHES "arm64")
        set(CMAKE_OSX_ARCHITECTURES "arm64")
    elseif (CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
        set(CMAKE_OSX_ARCHITECTURES "x86_64")
    endif ()

    message(STATUS "Configuring for macOS...")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -Wall -Wextra -Wpedantic")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")
endif ()

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

# Add the source files to the executable
include_directories(
        ${PROJECT_SOURCE_DIR}/DiffusionSolverSTL/src  # Include the main source files
        ${PROJECT_SOURCE_DIR}/DiffusionSolverSTL/src/matrix_operations
        ${gtest_SOURCE_DIR}/include
        ${gtest_BINARY_DIR}/include
)

# Add library (compile the common source code into a library)
add_library(fvm_lib
        DiffusionSolverSTL/src/utils/PCG_solver.c
        DiffusionSolverSTL/src/matrix_operations/linear_algebra.c
        DiffusionSolverSTL/src/matrix_operations/linear_algebra.h
        DiffusionSolverSTL/src/utils/preconditioner.c
        DiffusionSolverSTL/src/matrix_operations/CRSMatrix.c
        DiffusionSolverSTL/src/matrix_operations/CRSMatrix.h
        DiffusionSolverSTL/src/matrix_operations/CPPVec2CArr.hpp
        DiffusionSolverSTL/test/test_CPPVec2CArr.cpp
)

#add_executable(Project_02_FVM
#        DiffusionSolverSTL/src/main.cpp
#        DiffusionSolverSTL/src/TimeStepping.cpp
#        DiffusionSolverSTL/src/TimeStepping.hpp
#        DiffusionSolverSTL/src/ExplicitScheme.cpp
#        DiffusionSolverSTL/src/ExplicitScheme.hpp
#        DiffusionSolverSTL/src/ImplicitScheme.cpp
#        DiffusionSolverSTL/src/ImplicitScheme.hpp
#        DiffusionSolverSTL/src/CrankNicolsonScheme.cpp
#        DiffusionSolverSTL/src/CrankNicolsonScheme.hpp
#        DiffusionSolverSTL/src/HeatSolver.cpp
#        DiffusionSolverSTL/src/HeatSolver.hpp
#        DiffusionSolverSTL/src/SimulationParameters.cpp
#        DiffusionSolverSTL/src/SimulationParameters.hpp
#        DiffusionSolverSTL/src/Convergence.cpp
#        DiffusionSolverSTL/src/Convergence.hpp
#        DiffusionSolverSTL/src/Output.cpp
#        DiffusionSolverSTL/src/Output.hpp
#        DiffusionSolverSTL/src/Grid.cpp
#        DiffusionSolverSTL/src/Grid.hpp
#        DiffusionSolverSTL/src/SchemeType.hpp
#        DiffusionSolverSTL/src/ConfigParser.cpp
#        DiffusionSolverSTL/src/ConfigParser.hpp
#        DiffusionSolverSTL/src/PCG_solver.h            # C headers explicitly added
#        DiffusionSolverSTL/src/linear_algebra.h        # C headers explicitly added
#        DiffusionSolverSTL/src/preconditioner.h        # C headers explicitly added
#)

# Link the main executable with the library
#target_link_libraries(Project_02_FVM fvm_lib)

# Link OpenMP to the library
target_link_libraries(fvm_lib PRIVATE OpenMP::OpenMP_C)

# Add test executables (linking against Google Test and your library)
add_executable(test_pcg
        DiffusionSolverSTL/test/test_pcg.cpp
        DiffusionSolverSTL/src/utils/PCG_solver.h
        DiffusionSolverSTL/src/matrix_operations/linear_algebra.h)            # Explicitly include headers for test
target_link_libraries(test_pcg fvm_lib GTest::gtest_main OpenMP::OpenMP_C)

add_executable(test_linear_algebra
        DiffusionSolverSTL/test/test_linear_algebra.cpp
        DiffusionSolverSTL/src/matrix_operations/linear_algebra.h
        DiffusionSolverSTL/test/test_crs_matrix.cpp)
target_link_libraries(test_linear_algebra fvm_lib GTest::gtest_main OpenMP::OpenMP_C)

add_executable(test_crs_matrix
        DiffusionSolverSTL/test/test_crs_matrix.cpp
        DiffusionSolverSTL/src/matrix_operations/CRSMatrix.h
        DiffusionSolverSTL/src/matrix_operations/CRSMatrix.c)
target_link_libraries(test_crs_matrix fvm_lib GTest::gtest_main OpenMP::OpenMP_C)

# Discover Google Test tests
include(GoogleTest)
gtest_discover_tests(test_pcg)
gtest_discover_tests(test_linear_algebra)
gtest_discover_tests(test_crs_matrix)