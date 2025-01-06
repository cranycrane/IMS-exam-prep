
#include <cstdlib>
#include <cstdio>
#include <cmath>


// y(t+h) = y(t) + h*f(t,y(t))
// Pro rovnici: y” - 5 + 2y’ = 0: 

#define N 2 // 2 integratory

void update(double *in, double *base) {
    in[0] = 5 + (-2 * base[0]);
    in[1] = base[0];
}

void euler_step(double *time, double step, double *y) {
    double in[2];
    update(in, y);

    for (int i = 0; i < N; i++) {
        y[i] = y[i] + in[i] * step; 
    }
    
    *time += step;
}

void main() {
    double y[2] = {1.0, 1.0};
    double step = 0.01;
    double time = 0.0;
    double max_time = 20.0;

    while (time < max_time) {
        if (time + step > max_time) {
            step = max_time - time;
        } 
        euler_step(&time, step, y);
    }

}