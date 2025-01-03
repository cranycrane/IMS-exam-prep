#include <simlib.h>
#include <iostream>
#include <getopt.h>
#include <stdexcept>

double A, B, X;

Store linka("Linka", 1);


class Rob_neco : public Process {
    void Behavior() override {
        Enter(linka);
        Wait(Exponential(B));
        Leave(linka);
    }
};

class Increase_cap : public Process {
    void Behavior() override {
        // nastaveni na 3 natrvalo
        if(linka.QueueLen() >= 5) {
            linka.SetCapacity(3);
        }
    }
};

class Generator_trans : public Event {
    void Behavior() override {
        (new Rob_neco)->Activate();
        (new Increase_cap)->Activate();
        Activate(Time + Exponential(A));
    }
};

int main() {
    Init(10000);
    (new Generator_trans)->Activate();
    Run();
}