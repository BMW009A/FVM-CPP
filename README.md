# Finite Volume Method Examples
This repo starts from the heat conduction equation, and end up with SIMPLE algorithm step by step. Also
there will be some detailed documents to describe the math process and coding structure in case the author
may forget something.
## 2D Diffusion equation (STL version)
The govern equation is:
$$ \frac{\partial T}{\partial t} = \alpha \left( \frac{\partial^2 T}{\partial x^2} + \frac{\partial^2 T}{\partial y^2} \right) \tag{1} $$
The finite difference approximation for the 2D heat equation is:
$$
\frac{T^{n+1}_{i,j} - T^n_{i,j}}{\Delta t} = \alpha \left( \frac{T^n_{i+1,j} - 2T^n_{i,j} + T^n_{i-1,j}}{\Delta x^2} + \frac{T^n_{i,j+1} - 2T^n_{i,j} + T^n_{i,j-1}}{\Delta y^2} \right) \tag{2}
$$
### Euler Explicit Scheme
$$ 
T^{n+1}_{i,j} = T^n_{i,j} + \alpha \Delta t \left( \frac{T^n_{i+1,j} - 2T^n_{i,j} + T^n_{i-1,j}}{\Delta x^2} + \frac{T^n_{i,j+1} - 2T^n_{i,j} + T^n_{i,j-1}}{\Delta y^2} \right) \tag{3}
$$
### Euler Implicit Scheme
$$
\frac{T^{n+1}_{i,j} - T^n_{i,j}}{\Delta t} = \alpha \left( \frac{T^{n+1}_{i+1,j} - 2T^{n+1}_{i,j} + T^{n+1}_{i-1,j}}{\Delta x^2} + \frac{T^{n+1}_{i,j+1} - 2T^{n+1}_{i,j} + T^{n+1}_{i,j-1}}{\Delta y^2} \right) \tag{4}
$$
### Crank-Nicolson Scheme
$$
\frac{T^{n+1}_{i,j} - T^n_{i,j}}{\Delta t} = \frac{\alpha}{2} \left( \frac{T^{n+1}_{i+1,j} - 2T^{n+1}_{i,j} + T^{n+1}_{i-1,j}}{\Delta x^2} + \frac{T^n_{i+1,j} - 2T^n_{i,j} + T^n_{i-1,j}}{\Delta x^2} \right) + \frac{\alpha}{2} \left( \frac{T^{n+1}_{i,j+1} - 2T^{n+1}_{i,j} + T^{n+1}_{i,j-1}}{\Delta y^2} + \frac{T^n_{i,j+1} - 2T^n_{i,j} + T^n_{i,j-1}}{\Delta y^2} \right) \tag{5}
$$

## 3D Diffusion equation (STL version)
The govern equation is:
$$ \frac{\partial T}{\partial t} = \alpha \left( \frac{\partial^2 T}{\partial x^2} + \frac{\partial^2 T}{\partial y^2} + \frac{\partial^2 T}{\partial z^2} \right) \tag{6} $$
### Explicit Scheme
### Implicit Scheme

## 2D Diffusion equation (Eigen version)
### Explicit Scheme
### Implicit Scheme
Sort equation (4) into matrix form:

## 3D Diffusion equation (Eigen version)
### Explicit Scheme
### Implicit Scheme

Below code will only use Eigen.
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

Lid-Driven Cavity Flow

![Lid-Driven Cavity Flow From Comsol](https://cdn.comsol.com/wordpress/2018/05/lid-driven-cavity-problem-results.png)
Flow Over a Cylinder(an Airfoil)

Backward Facing Step

