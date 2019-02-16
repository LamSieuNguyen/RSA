#ifndef NUMBER_THEORY
#define NUMBER_THEORY
#include "ReallyLongInt.h"
#include <cmath>

bool isPrime(const ReallyLongInt& num);
ReallyLongInt modPower(const ReallyLongInt& base, const ReallyLongInt& exponent, const ReallyLongInt& modulus) ;
ReallyLongInt extendedEuclid(const ReallyLongInt& a, const ReallyLongInt& b, ReallyLongInt& x, ReallyLongInt& y);

#endif
