/**
 * Lineárny kongurentný generátor (LCG)
 * @author onegen (https://github.com/onegentig)
 * @license MIT
 */

#include <cstdio>
#include <climits>

// LCG počíta následujúce pseudonáhodné číslo vzorcom:
//
//      x_[x+1] = (a * x_i + b) mod m
//
// kde a,b,m sú vhodne zvolené konštanty. Dobré hodnoty
// sú napr. a=69069, b=1 a m=2^32 (RAND, z opory).
// Za m sa často určuje šírka dátového typu, napr. 2^32, čím je
// operácia mod implicitná (mod je celkom výpočetne náročné).
//
// LCG vracia hodnoty 0 ≤ x_i < m.
// Základom pseudonáhodných generátorov je generátor čísel
// medzi 0 a 1 (X ~ Ro(0;1)), čo získame vydelením x_i m-kom.

const unsigned A = 69069;
const unsigned B = 1;
const unsigned SEED = 2025;

class Kongr {
    unsigned x; // Aktuálne x
public:
    Kongr(unsigned seed) : x(seed) {}

    unsigned next() {
        this->x = A * this->x + B; // Implicitné modulo
        return this->x;            // 0 ≤ x_i < m
    }

    double next_double() {
        return this->next()/((double)UINT_MAX + 1.0); // 0 ≤ x_i < 1
    }

    // Z kongurentného generátoru je možné vytvoriť generátor
    // akéhokoľvek rovnomerného rozdelenia:
    //
    //     X ~ Ro(a;b) = (b-a) * Ro(0;1) + a
    //
    double uniform(double a, double b) {
        return (b-a) * this->next_double() + a;
    }
};

int main() {
    Kongr prng(SEED);
    for (unsigned i = 0; i < 5; i++)
        printf(" %.6f\n", prng.next_double());

    printf("=========\n", prng.next_double());

    for (unsigned i = 0; i < 5; i++)
        printf("%.6f\n", prng.uniform(50, 100));

    return 0;
}
