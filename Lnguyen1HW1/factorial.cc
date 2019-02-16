#include <iostream>
#include <fstream>
#include <string>
#include "ReallyLongInt.h"
#include "numberTheory.h"
using namespace std;

ReallyLongInt factorial(ReallyLongInt x)
{
 
  if(x > 1)
    {
    return x * factorial(x - 1);
    }
  else
    {
      return 1;
    }
  
}
int main()
{
  cout<<factorial(6)<<endl;
}
