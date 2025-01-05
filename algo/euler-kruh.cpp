/**
 * Ukážka Eulerovej metódy -- kruhový test
 * @see Opora IMS, strana 64-65
 * @author Petr Peringer
 * @editor onegen
 */

#include <cstdio>

double y[2] = { 1.0, 0.0 }; // Počiatočné podmienky
double y_in[2];             // Vstupy integrátorov
double time = 0;            // Modelový čas
double step = 0.01;         // Krok h

/* f(t,y) -- Výpočet vstupov integrátorov */
void Dynamic() {
    // y’’ + y = 0
    y_in[0] = y[1];  // y’
    y_in[1] = -y[0]; // y’’
}

/*
 * Výpočet jedného kroku integrácie cez Eulerovu metódu (RK1)
 *      y(t + h) = y(t) + hf(t,y(t))
 */
void EulerStep() {
    Dynamic();

    for (int i = 0; i < 2; i++) // Pre každý integrátor,
        y[i] += step * y_in[i]; // vypočítať nový stav

    time += step; // Posun modelového času
}

int main() {
    while (time < 20) {
        printf("%10f %10f\n", time, y[0]);
        EulerStep();
    }

    return 0;
}
