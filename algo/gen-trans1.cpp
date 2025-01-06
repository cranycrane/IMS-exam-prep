#include <cstdlib>
#include <cstdio>
#include <cmath>


// Předpokládejte kongruentní generátor unsigned int RND(); 
// Napíšte pseudokód programu, který transformuje výstup generátoru na rovnoměrné rozložení Uniform(2, 10). (10 bodov)


double trans() {
    unsigned int x = RND();
    double vysledek = (x / ((double) UINT_MAX + 1.0)) * 8.0 + 2.0;
    return vysledek;
}

// k UINT davame '+1' protoze kong. gen generuje '0 <= x < m' s rovn. rozložením (viz. opora)
// bez '+1' by to bylo <2,10> a ne <2,10)