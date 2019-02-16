#include "ReallyLongInt.h"
#include "numberTheory.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
   ifstream keyIn(argv[1]);
   ifstream fin(argv[2]);
   ofstream fout(argv[3]);

   string str1;
   string str2;
   keyIn >> str1;
   keyIn >> str2;
   ReallyLongInt key1(str1);
   ReallyLongInt key2(str2);

   char c;
   while(fin.get(c))
   {
      ReallyLongInt encrypted = modPower(ReallyLongInt(c), key1, key2);
      fout << encrypted << endl;
   }
}
