#include <cmath>
#include <string>
#include <iostream>
#include <climits>

#include "ReallyLongInt.h"

using namespace std;

ReallyLongInt::ReallyLongInt()
{
   isNeg = false;
   digits = new unsigned char[1];
   digits[0] = 0;
   numDigits = 1;
}

ReallyLongInt::ReallyLongInt(const ReallyLongInt& other)
{
   isNeg = other.isNeg;
   numDigits = other.numDigits;
   digits = new unsigned char[numDigits];
   for(unsigned i = 0; i < numDigits; i++)
   {
      digits[i] = other.digits[i];
   }
}

ReallyLongInt::ReallyLongInt(long long num)
{
   isNeg = false;
   if(num < 0)
   {
      isNeg = true;
      num = -num;
   }

   if(num == 0)
   {
      numDigits = 1;
   }
   else
   {
      numDigits = log10(num) + 1;
   }

   digits = new unsigned char[numDigits];
   for(int i = numDigits - 1; i >= 0; i--)
   {
      digits[i] = num % 10;
      num /= 10;
   }
}

ReallyLongInt::ReallyLongInt(const string& numString)
{
   unsigned start = 0;
   isNeg = false;
   if(numString[0] == '-')
   {
      start = 1;
      isNeg = true;
   }

   numDigits = numString.size() - start;

   digits = new unsigned char[numDigits];
   
   for(unsigned i = start; i < numString.size(); i++)
   {
      digits[i - start] = numString[i] - '0';
   }

   removeLeadingZeros();
}

ReallyLongInt::ReallyLongInt(bool isNeg, unsigned char* digits, unsigned numDigits)
{
   this->isNeg = isNeg;
   this->numDigits = numDigits;
   this->digits = digits;

   removeLeadingZeros();
}

void ReallyLongInt::removeLeadingZeros()
{
   //Remove any leading zeros
   unsigned start = 0;
   while(digits[start] == 0 && start < numDigits - 1)
   {
      start++;
   }

   if(start > 0)
   {
      for(unsigned i = start; i < numDigits; i++)
      {
	 digits[i - start] = digits[i];
      }
      numDigits -= start;
   }   
}

ReallyLongInt::~ReallyLongInt()
{
   delete[] digits;
}

void ReallyLongInt::flipSign()
{
   isNeg = !isNeg;
}

bool ReallyLongInt::absGreater(const ReallyLongInt& other) const
{
   if(numDigits > other.numDigits)
   {
      return true;
   }
   else if(numDigits < other.numDigits)
   {
      return false;
   }
   else 
   {
      for(unsigned i = 0; i < numDigits; i++)
      {
	 if(digits[i] > other.digits[i])
	 {
	    return true;
	 }
	 else if(digits[i] < other.digits[i])
	 {
	    return false;
	 }
      }
      //If we are here, they are equal
      return false;
   }
}

bool ReallyLongInt::equal(const ReallyLongInt& other) const
{
   if(numDigits != other.numDigits)
   {
      return false;
   }
   else if(isNeg != other.isNeg)
   {
      return isZero() && other.isZero();
   }
   else
   {
      for(unsigned i = 0; i < numDigits; i++)
      {
	 if(digits[i] != other.digits[i])
	 {
	    return false;
	 }
      }
      //If we are here, they are equal
      return true;
   }
}

bool operator==(const ReallyLongInt& x, const ReallyLongInt& y)
{
   return x.equal(y);
}

bool ReallyLongInt::greater(const ReallyLongInt& other) const
{
   if(!isNeg && other.isNeg)
   {
      return !isZero() || !other.isZero();
   }
   else if(isNeg && !other.isNeg) 
   {
      return false;
   }
   else if(!isNeg)
   {
      return absGreater(other);
   }
   else
   {
      return other.absGreater(*this);
   }
}

bool operator>(const ReallyLongInt& x, const ReallyLongInt& y)
{
   return x.greater(y);
}

bool operator<(const ReallyLongInt& x, const ReallyLongInt& y)
{
   return y > x;
}

bool operator!=(const ReallyLongInt& x, const ReallyLongInt& y)
{
   return !(x == y);
}

bool operator>=(const ReallyLongInt& x, const ReallyLongInt& y)
{
   return !(x < y);
}

bool operator<=(const ReallyLongInt& x, const ReallyLongInt& y)
{
   return !(x > y);
}

ReallyLongInt& ReallyLongInt::operator=(const ReallyLongInt& other)
{
   ReallyLongInt tmp(other);
   std::swap(isNeg, tmp.isNeg);
   std::swap(digits, tmp.digits);
   std::swap(numDigits, tmp.numDigits);
   return *this;
}

ReallyLongInt ReallyLongInt::absAdd(const ReallyLongInt& other) const
{
   unsigned newSize = max(numDigits, other.numDigits) + 1;
   unsigned char* result = new unsigned char[newSize];

   char carry = 0;
   for(unsigned place = 1; place <= newSize; place++)
   {
      char sum = carry;
      if(place <= numDigits)
      {
	 sum += digits[numDigits - place];
      }   
      if(place <= other.numDigits)
      {
	 sum += other.digits[other.numDigits - place];
      }

      carry = sum/10;
      result[newSize - place] = sum%10;
   }

   ReallyLongInt res(false, result, newSize);
   return res;
}

ReallyLongInt ReallyLongInt::absSub(const ReallyLongInt& other) const
{
   unsigned newSize = max(numDigits, other.numDigits);
   unsigned char* result = new unsigned char[newSize];
   bool newNeg;

   const unsigned char* top;
   unsigned topSize;
   const unsigned char* bottom;
   unsigned bottomSize;
   if(absGreater(other))
   {
      top = digits;
      topSize = numDigits;
      bottom = other.digits;
      bottomSize = other.numDigits;
      newNeg = false;
   }
   else
   {
      top = other.digits;
      topSize = other.numDigits;
      bottom = digits;
      bottomSize = numDigits;
      newNeg = true;
   }

   char borrow = 0;
   for(unsigned place = 1; place <= newSize; place++)
   {
      char sub = -borrow;
      if(place <= topSize)
      {
	 sub += top[topSize - place];
      }   
      if(place <= bottomSize)
      {
	 sub -= bottom[bottomSize - place];
      }

      if(sub < 0)
      {
	 borrow = 1;
	 sub += 10;
      }
      else
      {
	 borrow = 0;
      }
      result[newSize - place] = sub;
   }

   ReallyLongInt res(newNeg, result, newSize);
   return res;
}

ReallyLongInt ReallyLongInt::add(const ReallyLongInt& other) const
{
   if(isNeg == other.isNeg)
   {
      ReallyLongInt result = absAdd(other);
      if(isNeg)
      {
	 result.flipSign();
      }
      return result;
   }
   else if(!isNeg && other.isNeg)
   {
      return absSub(other);
   }
   else 
   {
      return other.absSub(*this);
   }
}

ReallyLongInt operator+(const ReallyLongInt& x, const ReallyLongInt& y)
{
   return x.add(y);
}

ReallyLongInt& ReallyLongInt::operator+=(const ReallyLongInt& other)
{
   *this = *this + other;
   return *this;
}

ReallyLongInt ReallyLongInt::sub(const ReallyLongInt& other) const
{
   ReallyLongInt result;
   if(isNeg == other.isNeg)
   {
      result = absSub(other);
   }
   else
   {
      result = absAdd(other);
   }

   if(isNeg)
   {
      result.flipSign();
   }

   return result;
}

ReallyLongInt operator-(const ReallyLongInt& x, const ReallyLongInt& y)
{
   return x.sub(y);
}

ReallyLongInt& ReallyLongInt::operator-=(const ReallyLongInt& other)
{
   *this = *this - other;
   return *this;
}

ReallyLongInt ReallyLongInt::absMult(const ReallyLongInt& other) const
{
   unsigned newSize = numDigits + other.numDigits;
   unsigned char* result = new unsigned char[newSize];
   for(unsigned i = 0; i < newSize; i++)
   {
      result[i] = 0;
   }

   for(unsigned xPlace = 0; xPlace < numDigits; xPlace++)
   {
      char carry = 0;
      for(unsigned yPlace = 0; yPlace < other.numDigits; yPlace++)
      {
	 char prod = digits[numDigits - 1 - xPlace]*other.digits[other.numDigits - 1 - yPlace];
	 char sum = result[newSize - 1 - xPlace - yPlace] + prod + carry;
	 result[newSize - 1 - xPlace - yPlace] = sum % 10;
	 carry = sum / 10;
      }
      result[newSize - 1 - xPlace - other.numDigits] += carry;
   }

   ReallyLongInt res(false, result, newSize);
   return res;
}

ReallyLongInt ReallyLongInt::mult(const ReallyLongInt& other) const
{
   ReallyLongInt result = absMult(other);
   if(isNeg != other.isNeg)
   {
      result.flipSign();
   }
   return result;
}

ReallyLongInt operator*(const ReallyLongInt& x, const ReallyLongInt& y)
{
   return x.mult(y);
}

ReallyLongInt& ReallyLongInt::operator*=(const ReallyLongInt& other)
{
   *this = *this * other;
   return *this;
}

void ReallyLongInt::absDiv(const ReallyLongInt& denominator, ReallyLongInt& quotient, ReallyLongInt& remainder) const
{
   quotient = 0;
   remainder = 0;
   
   for(unsigned place = 0; place < numDigits; place++)
   {
      remainder = (remainder*10) + digits[place];

      char quot = 0;
      while(!denominator.absGreater(remainder))
      {
	 remainder = remainder.absSub(denominator);
	 quot++;
      }

      quotient = quotient*10 + quot;
   }
}

void ReallyLongInt::div(const ReallyLongInt& denominator, ReallyLongInt& quotient, ReallyLongInt& remainder) const
{
   absDiv(denominator, quotient, remainder);
   
   if(denominator.isNeg != isNeg)
   {
      quotient.flipSign();
   }
   
   if(isNeg)
   {
      remainder.flipSign();
   }
}

ReallyLongInt operator/(const ReallyLongInt& x, const ReallyLongInt& y)
{
   ReallyLongInt quotient;
   ReallyLongInt remainder;
   x.div(y, quotient, remainder);
   return quotient;
}

ReallyLongInt& ReallyLongInt::operator/=(const ReallyLongInt& other)
{
   *this = *this / other;
   return *this;
}

ReallyLongInt operator%(const ReallyLongInt& x, const ReallyLongInt& y)
{
   ReallyLongInt quotient;
   ReallyLongInt remainder;
   x.div(y, quotient, remainder);
   return remainder;
}

ReallyLongInt& ReallyLongInt::operator%=(const ReallyLongInt& other)
{
   *this = *this % other;
   return *this;
}

ReallyLongInt& ReallyLongInt::operator++()
{
   *this += 1;
   return *this;
}

ReallyLongInt ReallyLongInt::operator++(int dummy)
{
   ReallyLongInt tmp(*this);
   *this += 1;
   return tmp;
}

ReallyLongInt& ReallyLongInt::operator--()
{
   *this -= 1;
   return *this;
}

ReallyLongInt ReallyLongInt::operator--(int dummy)
{
   ReallyLongInt tmp(*this);
   *this -= 1;
   return tmp;
}

ReallyLongInt ReallyLongInt::operator-()
{
   ReallyLongInt neg(*this);
   neg.flipSign();
   return neg;
}

ostream& ReallyLongInt::print(ostream& out) const
{
   if(isNeg && !isZero())
   {
      out << '-';
   }

   for(unsigned i = 0; i < numDigits; i++)
   {
      out << (int)digits[i];
   }

   return out;
}

ostream& operator<<(ostream& out, const ReallyLongInt& x)
{
   return x.print(out);
}

long long ReallyLongInt::toLongLong() const
{
   ReallyLongInt max = LLONG_MAX;
   ReallyLongInt rem = *this % (max + 1);

   long long val = 0;
   for(unsigned i = 0; i < rem.numDigits; i++)
   {
      val *= 10;
      val += rem.digits[i];
   }
   if(rem.isNeg)
   {
      val = -val;
   }

   return val;
}
