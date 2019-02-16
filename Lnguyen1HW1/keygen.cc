#include "ReallyLongInt.h"
#include "numberTheory.h"

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

using namespace std;

int main(int argc, char** argv)
{
   ReallyLongInt p(argv[1]);
   ReallyLongInt q(argv[2]);

   if(p < 100000 && !isPrime(p))
   {
      cout << p << " is not prime!" << endl;
      exit(1);
   }

   if(q < 100000 && !isPrime(q))
   {
      cout << q << " is not prime!" << endl;
      exit(1);
   }
   
   ofstream publicOut(argv[3]);
   ofstream privateOut(argv[4]);
   
   ReallyLongInt product = p*q;
   ReallyLongInt phi = (p - 1)*(q - 1);

   ReallyLongInt e(0);
   ReallyLongInt x;
   ReallyLongInt y;
   for(ReallyLongInt i = 2; i < phi && e.isZero(); i++)
   {
      if(extendedEuclid(i, phi, x, y) == 1)
      {
	 e = i;
      }
   }

   ReallyLongInt d;
   if(x < 0)
   {
      d = phi + x;
   }
   else
   {
      d = x;
   }

   if(d < e)
   {
      ReallyLongInt tmp = e;
      e = d;
      d = tmp;
   }

   publicOut << e << " " << product << endl;
   privateOut << d << " " << product << endl;
}
