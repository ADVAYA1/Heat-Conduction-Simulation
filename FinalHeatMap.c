#include <stdio.h>
#include <stdlib.h>

void tempinit(int *nx, int *ny, double *top_temp, double *bottom_temp, double *left_temp, double *right_temp) {
    printf("Enter no of grid points in x direction: ");
    scanf("%d", nx);
    printf("Enter no of grid points in y direction: ");
    scanf("%d", ny);
    printf("Enter boundary temperature for the top side: ");
    scanf("%lf", top_temp);
    printf("Enter boundary temperature for the bottom side: ");
    scanf("%lf", bottom_temp);
    printf("Enter boundary temperature for the left side: ");
    scanf("%lf", left_temp);
    printf("Enter boundary temperature for the right side: ");
    scanf("%lf", right_temp);
}

double** steady_gauss_method(int nx, int ny, double L, double tolerance, double top_temp, double bottom_temp, double left_temp, double right_temp) {    
    double dx = L / (nx - 1);
    double dy = L / (ny - 1);
    double k = (2 * (dx * dx + dy * dy)) / (dx * dx * dy * dy);

    double **temp_grid = (double **)malloc(nx * sizeof(double *));
    for (int i = 0; i < nx; i++) {
        temp_grid[i] = (double *)malloc(ny * sizeof(double));
    }

    // Initialize grid
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            if (i == 0) {
                temp_grid[i][j] = left_temp; // Left boundary
            } else if (i == nx - 1) {
                temp_grid[i][j] = right_temp; // Right boundary
            } else if (j == 0) {
                temp_grid[i][j] = bottom_temp; // Bottom boundary
            } else if (j == ny - 1) {
                temp_grid[i][j] = top_temp; // Top boundary
            } else {
                temp_grid[i][j] = 0; // Initial value for interior points
            }
        }
    }

    double **Told = (double **)malloc(nx * sizeof(double *));
    for (int i = 0; i < nx; i++) {
        Told[i] = (double *)malloc(ny * sizeof(double));
        for (int j = 0; j < ny; j++) {
            Told[i][j] = temp_grid[i][j];
        }
    }

    double error = 999;
    int g_iteration_number = 1;

    while (error > tolerance) {
        error = 0;
        for (int i = 1; i < nx - 1; i++) {
            for (int j = 1; j < ny - 1; j++) {
                temp_grid[i][j] = (1 / k) * (((temp_grid[i - 1][j] + Told[i + 1][j]) / (dx * dx)) +
                                             ((temp_grid[i][j - 1] + Told[i][j + 1]) / (dy * dy)));
                error += abs(temp_grid[i][j] - Told[i][j]);
            }
        }

        for (int i = 1; i < nx - 1; i++) {
            for (int j = 1; j < ny - 1; j++) {
                Told[i][j] = temp_grid[i][j];
            }
        }

        g_iteration_number++;
    }

    printf("Gauss-Seidel iteration count: %d\n", g_iteration_number);

    return temp_grid;
}

void print_grid(double **grid, int nx, int ny) {
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            printf("%8.2f  ", grid[i][j]);
        }
        printf("\n");
    }
}

void free_grid(double **grid, int nx) {
    for (int i = 0; i < nx; i++) {
        free(grid[i]);
    }
    free(grid);
}

void save_temperature_data(double **grid, int nx, int ny) {
    FILE *fp = fopen("temperature_Flat.txt", "w");
    if (fp == NULL) {
        printf("Error opening file for writing!\n");
        exit(1);
    }

    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            fprintf(fp, "%lf ", grid[i][j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}

void plot_temperature_heatmap(int nx, int ny) {
    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
    if (gnuplotPipe) {
        fprintf(gnuplotPipe, "set title 'Temperature Distribution Heatmap'\n");
        fprintf(gnuplotPipe, "set xlabel 'X'\n");
        fprintf(gnuplotPipe, "set ylabel 'Y'\n");
        fprintf(gnuplotPipe, "set pm3d map\n");
        fprintf(gnuplotPipe, "splot 'temperature_Flat.txt' matrix with image\n");
        fflush(gnuplotPipe);
    } else {
        printf("Error opening gnuplot pipe!\n");
    }
}
void plot_temperature_surface(int nx, int ny) {
    FILE *gnuplotPipe = popen("gnuplot -persistent", "w");
    if (gnuplotPipe) {
        fprintf(gnuplotPipe, "set title 'Temperature Distribution 3D Surface Plot'\n");
        fprintf(gnuplotPipe, "set xlabel 'X'\n");
        fprintf(gnuplotPipe, "set ylabel 'Y'\n");
        fprintf(gnuplotPipe, "set zlabel 'Temperature'\n");
        fprintf(gnuplotPipe, "set pm3d\n");
        fprintf(gnuplotPipe, "splot 'temperature_Flat.txt' matrix with pm3d\n");
        fflush(gnuplotPipe);
    } else {
        printf("Error opening gnuplot pipe!\n");
    }
}

int main() {
    int nx, ny;
    double top_temp, bottom_temp, left_temp, right_temp;
    printf("Enter the size of the domain (L): ");
    double L;
    scanf("%lf", &L);
    tempinit(&nx, &ny, &top_temp, &bottom_temp, &left_temp, &right_temp);
    printf("Enter tolerance value: ");
    double tolerance;
    scanf("%lf", &tolerance);

    printf(" Gauss-Seidel): ");
    
    double **temperature_g = steady_gauss_method(nx, ny, L, tolerance, top_temp, bottom_temp, left_temp, right_temp);
        save_temperature_data(temperature_g, nx, ny);
        
        plot_temperature_heatmap(nx, ny);  
        plot_temperature_surface(nx, ny);  
        print_grid(temperature_g, nx, ny);
        free_grid(temperature_g, nx);

    return 0;
}
