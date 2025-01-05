/**
 * Ukážka Monte Carlo na výpočet jednoúrovňového integrálu
 * @see Opora IMS, kapitola 4.1
 * @author onegen (https://github.com/onegentig)
 * @license MIT
 */

#include <cstdlib>
#include <cstdio>
#include <cmath>

double Uniform(double min, double max) {
    return min + (max - min) * ((double)std::rand() / RAND_MAX); // Ro(a;b) PRNG
}

double f(double x) {
    return std::sin(x);
}

/*
 * Výpočet jednoúrovňového určitého integrálu pomocou MC
 * @param *f Funkcia vnútri integrálu
 * @param a Spodná mez integrálu
 * @param b Horná mez integrálu
 * @oaram n Počet bodov na vygenerovanie
 * @returns Približný výsledok
 */
double mc_integrate(double (*f)(double), double a, double b, unsigned n) {
    double sum = 0.0; // Suma hodnot f(x) v náhodných x
    for (unsigned i = 0; i < n; i++) {
        double x = Uniform(a, b); // Náhodný bod
        sum += f(x);
    }

    double avg = sum / n; // Priemer
    double width = b - a; // Šírka rozsahu určitého integrálu
    return width * avg;
}

int main() {
    // V zadaní mǒže byť "chyba nesmie prekročiť 0,01".
    //      err = 1 / √N
    // =>
    //      N = 1 / err^2
    //      N = 1 / 0,01^2
    unsigned n = 10000;

    // Podľa opory počítame integrál sin(x) dx od 0 do pi.
    double res_mc = mc_integrate(f, 0.0, M_PI, n);
    double res_an = 2.0;  // Analytické riešenie

    printf("Výsledok Monte Carlo: %2f\n", res_mc);
    printf("Skutočný výsledok:    %2f\n", res_an);
    printf("Absolútna chyba:      %2f\n", std::abs(res_mc - res_an));

    return 0;
}
