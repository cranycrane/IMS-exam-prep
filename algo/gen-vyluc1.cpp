#include <cstdlib>
#include <cstdio>
#include <cmath>


// Majme spojitú náhodnú veličinu na intervale <0,1> 
// danú funkciou hustoty pravdepodobnosti f(x), 
// ktorá má rozsah funkčných hodnôt <0, 5). 
// Napíšte pseudokód generátora tejto náhodnej premennej s 
// použitím vylučovacej metódy a funkcie rnd() generujúcej 
// rovnomerné rozloženie na intervale <0, 1> . (10 bodov)  

 
double gen() {
    double x, y;

    while (1) {
        x = Random();
        y = Random() * 5;
        if(y < f(x)) {
            return x;
        } 
    }
}

// nebo do While (z bugdocu)

double generator() { 
    double x, y; 

    do { 
        x = Random();           // generate a random value from <0, 1> 
        y = Random() * 5;       // generate a random value and move it to range <0, 5> 
    } while (y > f(x));      // check if the value is under the curve of f(x) => if y lies under f(x) 
    
    return x; 
}	