#include <cstdlib>
#include <cstdio>
#include <cmath>


// Bola zadana funkcia unsigned RND(), ktorá generuje pseudo nahod č. 
// Napísať pseudokód, ako zistiť dĺžku periódy kongruentného generátora tejto funkcie. (10 bodov)  


int perioda() {
    double first = RND();
    double x = RND();
    int count = 1;

    while (first != x) {
        x = RND();
        count++;
    }

    return count;
}