#include <cstdlib>
#include <cstdio>
#include <cmath>

// Majme kružnicu o polomere r=20. Napíšte pseudokód funkcie,
//  ktorá vypočíta obsah zadaného kruhu metódou Monte Carlo tak,
//   aby chyba metody dosahovala 5 % (zdôvodnite nastavenie presnosti metódy). (10 bodov) 


// Err = 1/sqrt(N) => 0.05 = 1/20 = 1/sqrt(400)


double obsah_kruznice(int r) { 
   int N = 400; 
   int count = 0; 
   double x, y, p;

   for(int i = 0; i < N; i++){ 
     y = Random() * 20; 
     x = Random() * 20;

     if(x*x + y*y < r*r) {
       count++; 
     }
   } 

   p = count / N; 

   return (p * r * r) * 4; 
} 