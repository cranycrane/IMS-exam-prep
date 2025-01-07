#include <simlib.h>
#include <iostream>
#include <getopt.h>
#include <stdexcept>

double A, B, X;
int counter = 0;

// M/M/1, kazdych exp(4h) udrzbar, pokud 10 obsluh od jeho posledni navstevy,
// tak pocka na dokonceni prave probihajici obsluhy a zahaji udrzbu na 20MIN
// jinak pokracuje v obchuzce

Facility linka("linka");

class Udrzbar : public Process {
    void Behavior() {
        while(1) {
            Wait(Exponential(4));
            if(counter == 10) {
                Priority = 100;
                Seize(linka);
                Wait(20);
                Release(linka);
            }
            counter = 0;

        }
    }
};

class Rob_neco : public Process {
    void Behavior() {

        Seize(linka);

        Wait(Exponential(B));

        Release(linka);
        counter++;
    }
};

class Generator : public Event {
    void Behavior() {
        (new Rob_neco)->Activate();
        Activate(Time + Exponential(A));
    }
};

int main() {
    Init(1000);

    (new Udrzbar)->Activate();
    (new Generator)->Activate();
    Run();
}