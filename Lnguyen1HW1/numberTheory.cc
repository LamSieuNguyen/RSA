#include <iostream>
#include <fstream>
#include "numberTheory.h"
#include "ReallyLongInt.h"
#include <cmath>
using namespace std;
ReallyLongInt modPower(const ReallyLongInt& base, const ReallyLongInt& exponent, const ReallyLongInt& modulus)
{
  if(exponent == 0)
   {
      return 1;
   }
   else if(exponent == 1)
   {
      return base % modulus;
   }
   else
   {
      ReallyLongInt sqR = modPower(base, exponent/2, modulus);
      ReallyLongInt sq = (sqR*sqR) % modulus;
      if(exponent % 2 == 0)
      {
	 return sq;
      }
      else
      {
	 return (sq*base) % modulus;
      }
   }

}
bool isPrime(const ReallyLongInt& num)
{
  // simple boolean to check if a number is prime.
  // multiple special cases to get out of the way.
  if (num==0 || num==1)
    {
   
      return false; 
      
    }
  else if (num == 2)
    {

      return true;
      
    }
  else if (num%2==0)
    {

      return false;
    }
 
  for (ReallyLongInt i = 2; i<=num/2;i++)
    {
      if (num%i==0)
	{
	  
	  return false;
	}
    }

  return true;

}
ReallyLongInt extendedEuclid(const ReallyLongInt& a, const ReallyLongInt& b, ReallyLongInt & x, ReallyLongInt &y)
{
  if(b == 0)
    {
      x = 1;
      y = 0;
      return a;
    }
  else
    {
      ReallyLongInt x2;
      ReallyLongInt y2;
      ReallyLongInt gcd = extendedEuclid(b, a%b, x2, y2);
      x = y2;
      y = x2 - (a/b)*y2;
      return gcd;
    }

      
}

