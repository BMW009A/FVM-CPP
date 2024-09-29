cmake_minimum_required(VERSION 3.29)
project(Project_02_FVM)

set(CMAKE_CXX_STANDARD 20)

add_executable(Project_02_FVM 2DImp-STL/main.cpp
        2DImp-STL/output.cpp
        2DImp-STL/output.hpp
        DiffusionSolverSTL/main.cpp
        DiffusionSolverSTL/TimeStepping.cpp
        DiffusionSolverSTL/TimeStepping.hpp
        DiffusionSolverSTL/ExplicitScheme.cpp
        DiffusionSolverSTL/ExplicitScheme.hpp
        DiffusionSolverSTL/ImplicitScheme.cpp
        DiffusionSolverSTL/ImplicitScheme.hpp
        DiffusionSolverSTL/CrankNicolsonScheme.cpp
        DiffusionSolverSTL/CrankNicolsonScheme.hpp
        DiffusionSolverSTL/HeatSolver.cpp
        DiffusionSolverSTL/HeatSolver.hpp
        DiffusionSolverSTL/SimulationParameters.cpp
        DiffusionSolverSTL/SimulationParameters.hpp
        DiffusionSolverSTL/Convergence.cpp
        DiffusionSolverSTL/Convergence.hpp
        DiffusionSolverSTL/Output.cpp
        DiffusionSolverSTL/Output.hpp
        DiffusionSolverSTL/Grid.cpp
        DiffusionSolverSTL/Grid.hpp
        DiffusionSolverSTL/SchemeType.hpp)
