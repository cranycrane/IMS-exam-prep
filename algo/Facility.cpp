#include <cstdlib>
#include <cstdio>
#include <cmath>

// basic facility bez priorit

class Facility {
    Process *p = NULL;
    Queue q;

    void Seize(Process *np) {
        if (p != NULL) {
            q.add(np);
        } else {
            p = np;
        }
    }

    void Release() {
        p = NULL;
        if (q.len() > 0) {
            p = q.first();
        }
    }

    bool isBusy() {
        if (p == NULL) 
            return false;
        else
            return true;
    }
}