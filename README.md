
# 2D Heat Conduction Simulation using Gauss-Seidel Method

This repository contains a numerical solution to the 2D heat conduction problem using the Gauss-Seidel method. The heat conduction equation is solved over a grid with specified boundary conditions, and the results are visualized using heatmaps and 3D surface plots. The method is based on the Finite Difference Method (FDM) for discretization of the 2D domain.

## Table of Contents

- [Project Overview](#project-overview)
- [Solution Approach](#solution-approach)
- [Installation](#installation)
- [How to Run](#how-to-run)
- [Code Explanation](#code-explanation)
  - [Main Functions](#main-functions)
  - [Numerical Method](#numerical-method)
- [Visualizations](#visualizations)
- [Convergence and Results](#convergence-and-results)
- [License](#license)

## Project Overview

This project solves the 2D heat conduction equation on a flat plate with specified boundary conditions using the **Gauss-Seidel method**. The simulation calculates the steady-state temperature distribution on the plate and visualizes the results through heatmaps and 3D surface plots.

### Problem Statement

The steady-state heat conduction equation for a 2D domain can be expressed as:

\[
\frac{\partial^2 T}{\partial x^2} + \frac{\partial^2 T}{\partial y^2} = 0
\]

where \( T(x, y) \) represents the temperature at a point on the plate, and the derivatives represent the change of temperature with respect to the spatial coordinates in the x and y directions.

The boundary conditions are:
- **Top boundary**: \( T(x, 0) = \) Top temperature
- **Bottom boundary**: \( T(x, ny) = \) Bottom temperature
- **Left boundary**: \( T(0, y) = \) Left temperature
- **Right boundary**: \( T(nx, y) = \) Right temperature

The solution is obtained iteratively using the Gauss-Seidel method.

## Solution Approach

1. **Finite Difference Method (FDM)**: The domain is discretized into a grid with grid points specified by the user. The second-order central difference approximation is used for the spatial derivatives in the x and y directions.
  
2. **Gauss-Seidel Iteration**: This method is applied to solve the system of equations resulting from the discretization of the heat conduction equation. The solution is iterated until convergence (when the change in the temperature grid is below a specified tolerance).

3. **Visualization**: After solving for the temperature distribution, the results are visualized using heatmaps and 3D surface plots to show the temperature variation across the domain.

## Installation

To run this simulation, you need to have the following tools installed:

1. **C Compiler**: This code is written in C, so you need a C compiler like `gcc` to compile and run the program.
   
2. **Gnuplot**: Gnuplot is required for plotting the temperature distribution in heatmap and 3D surface formats. You can download it from [gnuplot's official website](http://www.gnuplot.info/).

### Steps to Install:

1. **Clone the repository**:
   ```bash
   git clone https://github.com/ADVAYA1/Disease-prediction.git
   cd Disease-prediction
   ```

2. **Install Gnuplot** (if you haven't already):
   - On **Ubuntu**: 
     ```bash
     sudo apt-get install gnuplot
     ```
   - On **Windows**, download and install Gnuplot from the official website.

3. **Compile the C code**:
   ```bash
   gcc -o heat_conduction heat_conduction.c -lm
   ```

4. **Run the simulation**:
   ```bash
   ./heat_conduction
   ```

## How to Run

1. **Input Parameters**: When you run the program, you will be prompted to enter the following values:
   - **Number of grid points in the x and y directions** (`nx`, `ny`).
   - **Boundary temperatures** for the top, bottom, left, and right sides.
   - **Domain size** (`L`).
   - **Tolerance** for the Gauss-Seidel method to determine when to stop iterating.

2. **Output**: The program will output:
   - The temperature distribution on the grid.
   - The number of Gauss-Seidel iterations required for convergence.
   - A file `temperature_Flat.txt` containing the temperature distribution, which can be used for plotting.

3. **Visualization**: After the program has run, the temperature distribution is visualized in two ways:
   - **Heatmap**: A 2D map of the temperature distribution.
   - **3D Surface Plot**: A 3D plot showing the temperature distribution.

   These plots are generated using Gnuplot.

## Code Explanation

### Main Functions

1. **tempinit**: This function takes user inputs for grid sizes, boundary temperatures, and other parameters such as the domain size and tolerance.
   
2. **steady_gauss_method**: This function implements the Gauss-Seidel method for solving the heat conduction equation. It initializes the temperature grid, iterates to update the temperature at each grid point, and checks for convergence based on the specified tolerance.

3. **print_grid**: This function prints the temperature distribution on the grid to the console.

4. **save_temperature_data**: This function saves the temperature data to a file (`temperature_Flat.txt`) for later use in visualizations.

5. **plot_temperature_heatmap**: This function generates a heatmap of the temperature distribution using Gnuplot.

6. **plot_temperature_surface**: This function generates a 3D surface plot of the temperature distribution using Gnuplot.

7. **free_grid**: This function frees the allocated memory for the grid.

### Numerical Method

The main numerical method used in this program is the **Gauss-Seidel method**. The Gauss-Seidel method is an iterative method to solve the system of equations generated by the finite difference discretization of the heat conduction equation.

The temperature at each grid point is updated based on the values of neighboring grid points, and the iterations continue until the change in the temperature distribution is less than the specified tolerance.

The update equation for the temperature at grid point \((i, j)\) is:

\[
T_{i,j}^{new} = \frac{1}{k} \left( \frac{T_{i-1,j} + T_{i+1,j}}{dx^2} + \frac{T_{i,j-1} + T_{i,j+1}}{dy^2} \right)
\]

where \(dx\) and \(dy\) are the grid spacings in the x and y directions, respectively, and \(k\) is a constant factor based on the grid spacings.

## Visualizations

The program generates the following visualizations using Gnuplot:

1. **Heatmap**: A 2D representation of the temperature distribution over the grid, where the temperature at each point is represented by a color.
   
   To plot the heatmap, the following Gnuplot command is used:
   ```bash
   gnuplot -persistent -e "set pm3d map; splot 'temperature_Flat.txt' matrix with image"
   ```

2. **3D Surface Plot**: A 3D surface plot showing the temperature distribution across the grid. This gives a more intuitive view of how the temperature varies over the 2D domain.
   
   To plot the 3D surface, the following Gnuplot command is used:
   ```bash
   gnuplot -persistent -e "set pm3d; splot 'temperature_Flat.txt' matrix with pm3d"
   ```
   ![image](https://github.com/user-attachments/assets/1a6398cd-0629-4fc5-bb91-de81d356424b)

![image](https://github.com/user-attachments/assets/57eb15be-25f5-4cf1-9776-875761c70ab4)

## Convergence and Results

The solution converges when the change in temperature values between iterations is smaller than the specified tolerance. The program outputs the number of iterations required for convergence, which gives insight into the performance of the method.

The temperature distribution is saved in the file `temperature_Flat.txt`, which can be plotted using Gnuplot or any other plotting tool.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
