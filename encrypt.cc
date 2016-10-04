#include <fstream>
#include <iostream>
#include "numberTheory.h"
#include "ReallyLongInt.h"

using namespace std;


int main(int argc, char** argv)
{
  ifstream infile(argv[1]);
  string first;
  string second;
  infile >> first;
  infile >> second;

  ReallyLongInt e(first);
  ReallyLongInt n(second);

  ifstream input(argv[2]);
  ofstream output(argv[3]);
  
  char x;
  
  while (input.get(x))
  {  
    ReallyLongInt base = x;
    ReallyLongInt encryptedNum = modPower(base,e,n);
    output << encryptedNum << endl;
  }
  
  
}
