/**
 * Príklad na Monte Carlo s 3D objektom zo skúšky.
 * @author Kalábovi (https://kalabovi.org/pitel:ims:simlib)
 * @author onegen (https://github.com/onegentig)
 * @license CC BY-SA 4.0
 */

#include <cstdlib>
#include <cstdio>
#include <cmath>

// Metodou Monte Carlo vypočtěte objem složitého tělesa v 3D prostoru
// za předpokladu, že znáte funkci `bool BodJeUvnitrTelesa(double x, double y, double z)`
// a rozsah mezí integrálu ve všech 3 osách je uložen v polích `double min[3]`
// a `double max[3]`. Funkci pro výpočet integrálu napište v ISO C:
// `double integMC(long POCET_EXPERIMENTU, double xmin[3], double xmax[3])`.
// Nesmíte použít žádnou funkci kromě double Random() vracející pseudonáhodné číslo
// v rozsahu 0…1. Rozsah kódu je maximálně 15 řádků.

// UTILITKY //

bool BodJeUvnitrTelesa(double x, double y, double z) {
    return (x*x + y*y + z*z) <= 1.0; // Spoiler: teleso je guľa s r=1
}

double Random() {
    return (double)std::rand() / RAND_MAX; // Ro(0;1) PRNG
}

// KONIEC UTILITIEK //
// RIEŠENIE //

double integMC(long n_exp, double xmin[3], double xmax[3]) {
    double cnt = 0; // Počet bodov, ktoré boli vnútri telesa
    double x[3];    // Náhodný bod
    for (unsigned i = 0; i < n_exp; i++) {
        for (unsigned j = 0; j < 3; j++)
            x[j] = (xmax[j] - xmin[j]) * Random() + xmin[j]; // Nový náh. bod
        if (BodJeUvnitrTelesa(x[0], x[1], x[2])) cnt++;
    }
    double pr = 1; // Produkt rozsahov
    for (unsigned i = 0; i < 3; i++)
        pr *= xmax[i] - xmin[i];
    double p = cnt / n_exp;
    return p * pr;
}

// KONIEC RIEŠENIA //

int main() {
    // Ako hranice viacúrovňového integrálu si určím kocku,
    // ktorá celá obsahuje skúmané teleso.
    double xmin[3] = {-1.0, -1.0, -1.0};
    double xmax[3] = {1.0, 1.0, 1.0};

    double res_mc = integMC(1000000, xmin, xmax);
    double res_an = 4.0/3.0 * M_PI; // Analytické riešenie

    printf("Výsledok Monte Carlo: %.6f\n", res_mc);
    printf("Skutočný výsledok:    %.6f\n", res_an);
    printf("Absolútna chyba:      %.6f\n", std::abs(res_mc - res_an));

    return 0;
}
