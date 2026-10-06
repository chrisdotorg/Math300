#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "differential_equations.h"
#include "input.h"
#include "integration.h"
#include "interpolation.h"
#include "matrix.h"
#include "output.h"
#include "root_finding.h"

/* Original functions from the 2020 program, kept as explicit mathematical
   functions rather than hidden global state. */
static double equation(double x)
{
    return x - 2.0 * tan(x) + 1.0;
}

static double equation_derivative(double x)
{
    double c = cos(x);
    return 1.0 - 2.0 / (c * c);
}

static double fixed_point_function(double x)
{
    return 2.0 * tan(x) - 1.0;
}

static double ode_function(double x, double y)
{
    (void)x;
    (void)y;
    return (x - 1.0) * (x - 1.0);
}

static SolverConfig default_config(void)
{
    SolverConfig config = {
        DEFAULT_MAX_ITERATIONS,
        EPSILON
    };
    return config;
}

static void print_header(void)
{
    printf("\n============================================\n");
    printf("       NUMERICAL ANALYSIS - REFACTORED\n");
    printf("============================================\n");
}

static void root_finding_menu(void)
{
    int choice;
    SolverConfig config = default_config();

    printf("\n--- Root finding ---\n");
    printf("1. Bisection\n");
    printf("2. Newton\n");
    printf("3. Fixed point\n");
    printf("4. Regula Falsi\n");
    printf("5. Secant\n");

    input_choice("Choice: ", 1, 5, &choice);

    RootResult result;

    switch (choice) {
        case 1: {
            double a, b;
            input_double("a = ", &a);
            input_double("b = ", &b);
            result = bisection_method(equation, a, b, config);
            break;
        }

        case 2: {
            double x0;
            input_double("Initial guess = ", &x0);
            result = newton_method(
                equation, equation_derivative, x0, config);
            break;
        }

        case 3: {
            double x0;
            input_double("Initial guess = ", &x0);
            result = fixed_point_method(
                fixed_point_function, x0, config);
            break;
        }

        case 4: {
            double a, b;
            input_double("a = ", &a);
            input_double("b = ", &b);
            result = regula_falsi_method(equation, a, b, config);
            break;
        }

        case 5: {
            double x0, x1;
            input_double("x0 = ", &x0);
            input_double("x1 = ", &x1);
            result = secant_method(equation, x0, x1, config);
            break;
        }

        default:
            return;
    }

    print_root_result(&result);
}

static bool read_linear_system(Matrix *A, double *b)
{
    if (!A || !b) return false;

    for (size_t i = 0; i < A->rows; ++i) {
        for (size_t j = 0; j < A->cols; ++j) {
            char prompt[64];
            snprintf(prompt, sizeof(prompt),
                     "A[%zu][%zu] = ", i, j);
            if (!input_double(prompt, &A->data[i * A->cols + j]))
                return false;
        }

        char prompt[64];
        snprintf(prompt, sizeof(prompt), "b[%zu] = ", i);
        if (!input_double(prompt, &b[i]))
            return false;
    }

    return true;
}

static void print_solver_result(Status status, const double *x, size_t n)
{
    print_status(status);

    if (status == STATUS_OK || status == STATUS_MAX_ITERATIONS)
        print_vector(x, n);
}

static void linear_system_menu(void)
{
    size_t n;

    if (!input_size("Matrix order n = ", &n))
        return;

    Matrix A = matrix_create(n, n);
    double *b = calloc(n, sizeof(*b));
    double *x = calloc(n, sizeof(*x));

    if (!A.data || !b || !x) {
        printf("Memory allocation failed.\n");
        matrix_destroy(&A);
        free(b);
        free(x);
        return;
    }

    if (!read_linear_system(&A, b)) {
        printf("Invalid input.\n");
        matrix_destroy(&A);
        free(b);
        free(x);
        return;
    }

    printf("\nMatrix:\n");
    matrix_print(&A);

    int choice;
    printf("\n--- Linear systems ---\n");
    printf("1. Gaussian elimination\n");
    printf("2. Gauss-Jordan\n");
    printf("3. Cholesky\n");
    printf("4. Crout\n");
    printf("5. Doolittle\n");
    printf("6. Jacobi\n");
    printf("7. Gauss-Seidel\n");

    input_choice("Choice: ", 1, 7, &choice);

    Status status = STATUS_INVALID_INPUT;

    switch (choice) {
        case 1:
            status = gauss_solve(&A, b, x);
            break;
        case 2:
            status = gauss_jordan_solve(&A, b, x);
            break;
        case 3:
            status = cholesky_solve(&A, b, x);
            break;
        case 4:
            status = crout_solve(&A, b, x);
            break;
        case 5:
            status = doolittle_solve(&A, b, x);
            break;
        case 6:
            status = jacobi_solve(
                &A, b, x, DEFAULT_MAX_ITERATIONS, EPSILON);
            break;
        case 7:
            status = gauss_seidel_solve(
                &A, b, x, DEFAULT_MAX_ITERATIONS, EPSILON);
            break;
    }

    printf("\nResult:\n");
    print_solver_result(status, x, n);

    matrix_destroy(&A);
    free(b);
    free(x);
}

static void interpolation_menu(void)
{
    size_t n;

    if (!input_size("Number of points = ", &n))
        return;

    double *x = calloc(n, sizeof(*x));
    double *y = calloc(n, sizeof(*y));

    if (!x || !y) {
        free(x); free(y);
        printf("Memory allocation failed.\n");
        return;
    }

    for (size_t i = 0; i < n; ++i) {
        char px[64], py[64];
        snprintf(px, sizeof(px), "x[%zu] = ", i);
        snprintf(py, sizeof(py), "y[%zu] = ", i);

        if (!input_double(px, &x[i]) ||
            !input_double(py, &y[i])) {
            free(x); free(y);
            printf("Invalid input.\n");
            return;
        }
    }

    int choice;
    printf("\n--- Interpolation ---\n");
    printf("1. Lagrange\n");
    printf("2. Newton\n");
    printf("3. Least squares\n");
    input_choice("Choice: ", 1, 3, &choice);

    double point;
    input_double("Evaluation point = ", &point);

    if (choice == 1 || choice == 2) {
        double value;
        Status status;

        if (choice == 1)
            status = lagrange_evaluate(x, y, n, point, &value);
        else
            status = newton_interpolation_evaluate(
                x, y, n, point, &value);

        print_status(status);

        if (status == STATUS_OK)
            printf("P(%.10f) = %.10f\n", point, value);
    } else {
        size_t degree;
        if (!input_size("Polynomial degree = ", &degree)) {
            free(x); free(y);
            return;
        }

        double *coeff = calloc(degree + 1, sizeof(*coeff));

        if (!coeff) {
            free(x); free(y);
            printf("Memory allocation failed.\n");
            return;
        }

        Status status = polynomial_least_squares(
            x, y, n, degree, coeff);

        print_status(status);

        if (status == STATUS_OK) {
            printf("Coefficients (constant first):\n");
            print_vector(coeff, degree + 1);
        }

        free(coeff);
    }

    free(x);
    free(y);
}

static void integration_menu(void)
{
    double a, b;
    size_t n;

    input_double("a = ", &a);
    input_double("b = ", &b);
    input_size("Number of subintervals = ", &n);

    int choice;
    printf("\n--- Numerical integration ---\n");
    printf("1. Left rectangles\n");
    printf("2. Right rectangles\n");
    printf("3. Midpoint\n");
    printf("4. Trapezoidal\n");
    input_choice("Choice: ", 1, 4, &choice);

    double result = 0.0;

    switch (choice) {
        case 1: result = left_rectangle_rule(
            equation, a, b, n); break;
        case 2: result = right_rectangle_rule(
            equation, a, b, n); break;
        case 3: result = midpoint_rule(
            equation, a, b, n); break;
        case 4: result = trapezoidal_rule(
            equation, a, b, n); break;
    }

    printf("Integral approximation = %.12f\n", result);
}

static void ode_menu(void)
{
    double x0, y0, h;
    size_t steps;

    input_double("x0 = ", &x0);
    input_double("y0 = ", &y0);
    input_double("Step h = ", &h);
    input_size("Number of steps = ", &steps);

    int choice;
    printf("\n--- Differential equations ---\n");
    printf("1. Euler\n");
    printf("2. Runge-Kutta 2\n");
    input_choice("Choice: ", 1, 2, &choice);

    OdePoint result;
    OdePoint initial = { x0, y0 };
    Status status;

    if (choice == 1)
        status = euler_step(ode_function, initial, h, steps, &result);
    else
        status = runge_kutta_2_step(
            ode_function, initial, h, steps, &result);

    print_status(status);

    if (status == STATUS_OK)
        printf("Final point: x = %.10f, y = %.10f\n",
               result.x, result.y);
}

static void about(void)
{
    printf("\nNumerical Analysis - refactored version\n");
    printf("Original project: numerical-analysis program written around 2020.\n");
    printf("Refactoring goals: modularity, testability, safer memory usage,\n");
    printf("clear APIs, consistent indexing and separation of UI from algorithms.\n");
}

int main(void)
{
    bool running = true;

    print_header();

    while (running) {
        int choice;

        printf("\n================ MAIN MENU ================\n");
        printf("1. Non-linear equations\n");
        printf("2. Linear systems\n");
        printf("3. Interpolation\n");
        printf("4. Numerical integration\n");
        printf("5. Differential equations\n");
        printf("6. About\n");
        printf("7. Exit\n");

        input_choice("Choice: ", 1, 7, &choice);

        switch (choice) {
            case 1: root_finding_menu(); break;
            case 2: linear_system_menu(); break;
            case 3: interpolation_menu(); break;
            case 4: integration_menu(); break;
            case 5: ode_menu(); break;
            case 6: about(); break;
            case 7: running = false; break;
        }
    }

    printf("\nGoodbye.\n");
    return 0;
}
