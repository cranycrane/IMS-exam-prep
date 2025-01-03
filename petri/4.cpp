#include <simlib.h>
#include <iostream>
#include <getopt.h>
#include <stdexcept>

double A, B, X;

Facility linka("Linka");


class Rob_neco : public Process {
    void Behavior() override {
        // netrpeliva transakce
        if(linka.Busy()) {
            return;
        }
        Seize(linka);
        Wait(Exponential(B));
        Release(linka);
    }
};


class Generator_trans : public Event {
    void Behavior() override {
        (new Rob_neco)->Activate();
        Activate(Time + Exponential(A));
    }
};

int main() {
    Init(10000);
    (new Generator_trans)->Activate();
    Run();
}