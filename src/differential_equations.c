#include "differential_equations.h"

static Status validate_ode_inputs(OdeFunction f, OdePoint initial,
                                  double step, size_t steps,
                                  OdePoint *result)
{
    (void)initial;
    if (!f || !result || step <= 0.0 || steps == 0)
        return STATUS_INVALID_INPUT;
    return STATUS_OK;
}

Status euler_step(OdeFunction f, OdePoint initial, double step,
                  size_t steps, OdePoint *result)
{
    Status status = validate_ode_inputs(f, initial, step, steps, result);
    if (status != STATUS_OK) return status;

    OdePoint p = initial;

    for (size_t i = 0; i < steps; ++i) {
        p.y += step * f(p.x, p.y);
        p.x += step;
    }

    *result = p;
    return STATUS_OK;
}

Status runge_kutta_2_step(OdeFunction f, OdePoint initial, double step,
                          size_t steps, OdePoint *result)
{
    Status status = validate_ode_inputs(f, initial, step, steps, result);
    if (status != STATUS_OK) return status;

    OdePoint p = initial;

    for (size_t i = 0; i < steps; ++i) {
        double k1 = f(p.x, p.y);
        double k2 = f(p.x + step, p.y + step * k1);

        p.y += step * 0.5 * (k1 + k2);
        p.x += step;
    }

    *result = p;
    return STATUS_OK;
}
