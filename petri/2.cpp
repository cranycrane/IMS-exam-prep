#include <simlib.h>
#include <iostream>
#include <getopt.h>
#include <stdexcept>

double A, B, X;

Facility linka("Linka");


class Rob_neco : public Process {
    void Behavior() override {
        Seize(linka);
        double process_time = Exponential(B);

        if (process_time > X) {
            Wait(X);
        } else {
            Wait(process_time);
        }

        Release(linka);
    }
};

class Generator : public Event {
    void Behavior() override {

        Activate(Time + Exponential(A));
    }
};