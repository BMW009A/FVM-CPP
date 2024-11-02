# Finite Volume Method Examples
This repo starts from the heat conduction equation, and end up with SIMPLE algorithm step by step. Also
there will be some detailed documents to describe the math process and coding structure in case the author
may forget something.
## 2D Diffusion equation
The govern equation is:

$$ \frac{\partial T}{\partial t} = \alpha \left( \frac{\partial^2 T}{\partial x^2} + \frac{\partial^2 T}{\partial y^2} \right) \quad (1) 
$$
The finite difference approximation for the 2D heat equation is:

$$ 
\frac{T^{n+1}_{i,j} - T^n_{i,j}}{\Delta t} = \alpha \left( \frac{T^n_{i+1,j} - 2T^n_{i,j} + T^n_{i-1,j}}{\Delta x^2} + \frac{T^n_{i,j+1} - 2T^n_{i,j} + T^n_{i,j-1}}{\Delta y^2} \right) \quad (2) 
$$
### Euler Explicit Scheme

$$ T^{n+1}_{i,j} = T^n_{i,j} + \alpha \Delta t \left( \frac{T^n_{i+1,j} - 2T^n_{i,j} + T^n_{i-1,j}}{\Delta x^2} + \frac{T^n_{i,j+1} - 2T^n_{i,j} + T^n_{i,j-1}}{\Delta y^2} \right) \quad (3)
$$

### Euler Implicit Scheme
$$
\frac{T^{n+1}_{i,j} - T^n_{i,j}}{\Delta t} = \alpha \left( \frac{T^{n+1}_{i+1,j} - 2T^{n+1}_{i,j} + T^{n+1}_{i-1,j}}{\Delta x^2} + \frac{T^{n+1}_{i,j+1} - 2T^{n+1}_{i,j} + T^{n+1}_{i,j-1}}{\Delta y^2} \right) \quad (4)
$$
### Crank-Nicolson Scheme
$$
\frac{T^{n+1}_{i,j} - T^n_{i,j}}{\Delta t} = \frac{\alpha}{2} \left( \frac{T^{n+1}_{i+1,j} - 2T^{n+1}_{i,j} + T^{n+1}_{i-1,j}}{\Delta x^2} + \frac{T^n_{i+1,j} - 2T^n_{i,j} + T^n_{i-1,j}}{\Delta x^2} \right) + \frac{\alpha}{2} \left( \frac{T^{n+1}_{i,j+1} - 2T^{n+1}_{i,j} + T^{n+1}_{i,j-1}}{\Delta y^2} + \frac{T^n_{i,j+1} - 2T^n_{i,j} + T^n_{i,j-1}}{\Delta y^2} \right) \tag{5}
$$

## 3D Diffusion equation
The govern equation is:
$$ 
\frac{\partial T}{\partial t} = \alpha \left( \frac{\partial^2 T}{\partial x^2} + \frac{\partial^2 T}{\partial y^2} + \frac{\partial^2 T}{\partial z^2} \right) \tag{6} 
$$
### Explicit Scheme
### Implicit Scheme

## Advection equation
$$ \frac{\partial \phi}{\partial t} + u \frac{\partial \phi}{\partial x} + v \frac{\partial \phi}{\partial y} + w \frac{\partial \phi}{\partial z} = 0 \tag{7} $$
## Advection-Diffusion equation
$$ \frac{\partial \phi}{\partial t} + u \frac{\partial \phi}{\partial x} + v \frac{\partial \phi}{\partial y} + w \frac{\partial \phi}{\partial z} = D \left( \frac{\partial^2 \phi}{\partial x^2} + \frac{\partial^2 \phi}{\partial y^2} + \frac{\partial^2 \phi}{\partial z^2} \right) \tag{8} $$

## Navier-Stokes equations in 2D under Cartesian Coordinates (SIMPLE algorithm)
$$
\rho \left( \frac{\partial \mathbf{u}}{\partial t} + (\mathbf{u} \cdot \nabla) \mathbf{u} \right) = -\nabla p + \mu \nabla^2 \mathbf{u} + \mathbf{f} \tag{9a}
$$

$$
\nabla \cdot \mathbf{u} = 0 \tag{9b}
$$

### Lid-Driven Cavity Flow
![Lid-Driven Cavity Flow]()
### Flow Over a Cylinder(an Airfoil)

### Backward Facing Step

## Numerical Linear Algebra (in C)
This module provides essential utility functions for linear algebra operations, implemented in C for efficiency and compatibility. 
These utilities support the main Finite Volume Method (FVM) part of the project, which is in C++. This module includes:

- Sparse Matrix Storage: Implements the Compressed Row Storage (CRS) format for efficient handling of sparse matrices.
- Matrix-Vector Multiplication: Optimized functions for performing matrix-vector multiplication, suitable for 
- both dense and sparse matrices.
- Linear System Solvers: Contains iterative solvers for linear systems, including Preconditioned Conjugate Gradient (PCG),
- Biconjugate Gradient Stabilized (BiCGSTAB), and Algebraic Multigrid (AMG) methods, designed to handle large, sparse matrices efficiently.

These utilities are optimized for performance and tailored to the matrix operations commonly encountered in FVM-based simulations.

### AT THE END ###
This project serves as a comprehensive practice ground for numerical simulation, C++ coding, and parallel computing 
techniques. My goal is to incorporate detailed documentation, both within the code and in supplementary descriptions, 
to provide clarity and aid understanding for myself and others who may review this project.

Feedback and suggestions are warmly welcome! If you have any ideas or improvements, please don’t hesitate to reach out.
