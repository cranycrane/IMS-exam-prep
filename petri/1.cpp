#include <simlib.h>
#include <iostream>
#include <getopt.h>
#include <stdexcept>

double A, B;

Store linka("Linka", 1);


class Obsluha_linky : public Process {
    void Behavior() override {
        if (linka.QueueLen() > 5){
            linka.SetCapacity(2);
            Wait(Exponential(15));
            linka.SetCapacity(1);
        }
        Enter(linka);
        Wait(Exponential(B));
        Leave(linka);
    }
};

class Generator : public Event {
    void Behavior() override {
        (new Obsluha_linky)->Activate();
        Activate(Time + Exponential(A));
    }
};