cmake_minimum_required(VERSION 3.26)
project(Project_02_FVM LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

# Add the source files to the executable
include_directories(
        ${PROJECT_SOURCE_DIR}/DiffusionSolverSTL/src  # Include the main source files
        ${gtest_SOURCE_DIR}/include
        ${gtest_BINARY_DIR}/include
)

# Add library (compile the common source code into a library)
add_library(fvm_lib
        DiffusionSolverSTL/src/PCG_solver.c
        DiffusionSolverSTL/src/linear_algebra.c
        DiffusionSolverSTL/src/preconditioner.c
)

add_executable(Project_02_FVM
        2DImp-STL/main.cpp
        2DImp-STL/output.cpp
        2DImp-STL/output.hpp
        DiffusionSolverSTL/src/main.cpp
        DiffusionSolverSTL/src/TimeStepping.cpp
        DiffusionSolverSTL/src/TimeStepping.hpp
        DiffusionSolverSTL/src/ExplicitScheme.cpp
        DiffusionSolverSTL/src/ExplicitScheme.hpp
        DiffusionSolverSTL/src/ImplicitScheme.cpp
        DiffusionSolverSTL/src/ImplicitScheme.hpp
        DiffusionSolverSTL/src/CrankNicolsonScheme.cpp
        DiffusionSolverSTL/src/CrankNicolsonScheme.hpp
        DiffusionSolverSTL/src/HeatSolver.cpp
        DiffusionSolverSTL/src/HeatSolver.hpp
        DiffusionSolverSTL/src/SimulationParameters.cpp
        DiffusionSolverSTL/src/SimulationParameters.hpp
        DiffusionSolverSTL/src/Convergence.cpp
        DiffusionSolverSTL/src/Convergence.hpp
        DiffusionSolverSTL/src/Output.cpp
        DiffusionSolverSTL/src/Output.hpp
        DiffusionSolverSTL/src/Grid.cpp
        DiffusionSolverSTL/src/Grid.hpp
        DiffusionSolverSTL/src/SchemeType.hpp
        DiffusionSolverSTL/src/ConfigParser.cpp
        DiffusionSolverSTL/src/ConfigParser.hpp
        DiffusionSolverSTL/src/PCG_solver.h            # C headers explicitly added
        DiffusionSolverSTL/src/linear_algebra.h        # C headers explicitly added
        DiffusionSolverSTL/src/preconditioner.h        # C headers explicitly added
)

# Link the main executable with the library
target_link_libraries(Project_02_FVM fvm_lib)

# Add test executables (linking against Google Test and your library)
add_executable(test_pcg
        DiffusionSolverSTL/test/test_pcg.cpp
        DiffusionSolverSTL/src/PCG_solver.h
        DiffusionSolverSTL/src/linear_algebra.h)            # Explicitly include headers for test
target_link_libraries(test_pcg fvm_lib GTest::gtest_main)

add_executable(test_linear_algebra
        DiffusionSolverSTL/test/test_linear_algebra.cpp
        DiffusionSolverSTL/src/linear_algebra.h)        # Explicitly include headers for test
target_link_libraries(test_linear_algebra fvm_lib GTest::gtest_main)

# Discover Google Test tests
include(GoogleTest)
gtest_discover_tests(test_pcg)
gtest_discover_tests(test_linear_algebra)