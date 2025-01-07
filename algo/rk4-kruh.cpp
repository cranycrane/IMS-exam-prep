/**
 * Ukážka Runge-Kutta 4. řádu -- kruhový test
 * @author Petr Peringer
 * @editor onegen
 */

#include <cstdio>

/** f(t,y) -- Výpočet vstupov integrátorov */
void Dynamic(double time, double* y_in, double* y) {
    // y’’ + y = 0
    y_in[0] = y[1];  // y’
    y_in[1] = -y[0]; // y’’
}

/*
 * Výpočet jedného kroku integrácie cez RK4
 *      k_1 = hf(t, y(t))
 *      k_2 = hf(t+h/2, y(t)+k_1/2)
 *      k_3 = hf(t+h/2, y(t)+k_2/2)
 *      k_4 = hf(t+h, y(t)+k_3)
 *      y(t+h) = y(t) + k_1/6 + k_2/3 * k_3/3 + k_4/6
 */
void RK4Step(double time, double step, double* y) {
    double k1[2], k2[2], k3[2], k4[2];
    double y_in[2];   // Vstupy integrátorov
    double y_init[2]; // Uchovanie počiatku
    for (int i = 0; i < 2; i++)
        y_init[i] = y[i];

    Dynamic(time, y_in, y); // y_in = f(t, y(t))

    for (int i = 0; i < 2; i++) {     // Pre každý integrátor,
        k1[i] = step * y_in[i];       // vypočítať nový stav
        y[i] = y_init[i] + k1[i] / 2;
    }

    Dynamic(time + step/2.0, y_in, y); // y_in = f(t+h/2, y(t)+k1/2)

    for (int i = 0; i < 2; i++) {
        k2[i] = step * y_in[i];
        y[i] = y_init[i] + k2[i] / 2;
    }

    Dynamic(time + step/2, y_in, y); // y_in = f(t+h/2, y(t)+k2/2)

    for (int i = 0; i < 2; i++) {
        k3[i] = step * y_in[i];
        y[i] = y_init[i] + k3[i];
    }

    Dynamic(time + step, y_in, y); // y_in = f(t+h, y(t)+k3)

    for (int i = 0; i < 2; i++) {
        k4[i] = step * y_in[i];

        // Finálny výsledok
        y[i] = y_init[i] + k1[i]/6 + k2[i]/3  + k3[i]/3 + k4[i]/6;
    }
}

int main() {
    const double t_start = 0.0;
    const double t_end = 20.0;

    double time = t_start;      // Modelový čas
    double step = 0.01;         // Krok h
    double y[2] = { 1.0, 0.0 }; // Počiatočné hodnoty

    while (time < t_end) {
        RK4Step(time, step, y);
        printf("%10f %10f\n", time, y[0]);

        if (time + step * 1.01 > t_end)
            step = t_end - time;

        time += step; // Posun modelového času
    }

    return 0;
}
