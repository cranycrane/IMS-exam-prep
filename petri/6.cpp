#include <simlib.h>
#include <iostream>
#include <getopt.h>
#include <stdexcept>

double A, B, X;

// M/M/3 bez fronty, neobslozene transakce se vraci po X casovych jednotkach.

Store linka("linka", 3);

class Rob_neco : public Process {
    void Behavior() {
        while(1) {
            if(linka.Full()) {
                Wait(X);
            } else {
                Enter(linka);
                Wait(Exponential(B));
                Leave(linka);
                break;
            }
        }
    }
};

class Generator : public Event {
    void Behavior() {
        (new Rob_neco)->Activate();
        Activate(Time + Exponential(A));
    }
};

int main() {
    Init(10000);
    (new Generator)->Activate();
    Run();
    return 0;
}