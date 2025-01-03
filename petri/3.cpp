#include <simlib.h>
#include <iostream>
#include <getopt.h>
#include <stdexcept>

double A, B, X;

Facility linka("Linka");


class Rob_neco : public Process {
    void Behavior() override {
        Seize(linka);
        Wait(Exponential(B));
        Release(linka);
    }
};

class Rob_poruchu : public Process {
    void Behavior() override {
        // idk jestli je tohle spravne, protoze vytvarim novou transakci,
        // misto abych vratil tu puvodni do fronty
        if(linka.Busy()) {
            Release(linka);
            (new Rob_neco)->Activate();
        }
    }
};


class Generator_trans : public Event {
    void Behavior() override {
        (new Rob_neco)->Activate();
        Activate(Time + Exponential(A));
    }
};

class Generator_poruch : public Event {
    void Behavior() override {
        (new Rob_poruchu)->Activate();
        Activate(Time + Exponential(X));
    }
};

int main() {
    Init(10000);
    (new Generator_trans)->Activate();
    (new Generator_poruch)->Activate();
    Run();
}