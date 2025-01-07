#include <simlib.h>
#include <iostream>
#include <getopt.h>
#include <stdexcept>

double A, B, X;
int counter = 0;

// M/M/1 ktery demonstruje pouizit priority obsluhy kazde 10. transakce
// petriho sit + kod bez mainu a generatoru

Facility linka("linka");

class Rob_neco : public Process {
    void Behavior() {
        counter++;
        if(counter == 10) {
            Seize(linka, 1); // priorita obsluhy
        } else {
            Seize(linka);
        }

        Wait(Exponential(B));

        Release(linka);
    }
};