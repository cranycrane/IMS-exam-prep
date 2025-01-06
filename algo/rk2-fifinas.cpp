/**
 * Runge Kutta 2nd order
 *   k1 = f(t, y(t))
 *   k2 = f(t + 0.75h, y(t) + 0.75 * h * t)
 *   y(t + h) = y(t) + h * (0.33 * k1 + 0.67 * k2)
 *
 * Source: https://www.youtube.com/watch?v=OAD8-GjuVC8&t=5880s (Fifinas)
 *
 * Compare with
 * https://www.fit.vut.cz/person/peringer/public/IMS/priklady/rk4-test.c.html
 * (black page) but note that's 4th order RK and the function parameters are
 * in different order and named differently
 */

#define SIZE 3  // third order ODE

/**
 * Equation: y''' - 7y' +2 = 0
 * see rk2-fifinas.jpg for the block diagram
 */
void Dynamic(double t, double *in, double *y) {
    in[2] = 7.0 * y[1] - 2.0;
    in[1] = y[2];
    in[0] = y[1];
}

/**
 * @brief 2nd order Runge Kutta step
 * @param t time
 * @param h step
 * @param y state values e.g. y(t)
 */
void RK2Step(double t, double h, double *y) {

    double ystart[SIZE];  // y(t)
    double in[SIZE];      // integrator inputs

    double k1[SIZE];
    double k2[SIZE];

    /* save y(t) */
    for (int i = 0; i < SIZE; i++) {
        ystart[i] = y[i];
    }

    Dynamic(t, in, y);
    for (int i = 0; i < SIZE; i++) {
        k1[i] = in[i];
        y[i] = ystart[i] + 0.75 * h * k1[i];  // for the next call of Dynamic
    }

    Dynamic(t + 0.75 * h, in, y);
    for (int i = 0; i < SIZE; i++) {
        k2[i] = in[i];
        y[i] = ystart[i] + h * ((1.0 / 3.0) * k1[i] + (2.0 / 3.0) * k2[i]);
    }

}

/**
 * @brief simulation control
 */
int main() {

    /* define start and end */
    double t_start = 0.0;
    double t_end = 20.0;

    /* step */
    double h = 0.01;

    /* initial values */
    double y[] = {3.0, 2.0, 1.0};

    double t = t_start;
    while (t < t_end) {
        RK2Step(t, h, y);

        // print state values / do whatever

        /* end precisely at t_end */
        if (t + h * 1.01 > t_end) {
            h = t_end - t;
        }

        /* important: increment simulation time */
        t += h;
    }
}
