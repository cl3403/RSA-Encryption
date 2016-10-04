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

  ReallyLongInt d(first);
  ReallyLongInt n(second);

  ifstream input(argv[2]);
  ofstream output(argv[3]);
  
  unsigned long long x;
  input >> x;
  
  while (!input.eof())
  {  
    ReallyLongInt base(x);
    ReallyLongInt decryptedNum = modPower(base,d,n);
    long long intResult = decryptedNum.toLongLong();
    char result = intResult;
    output << result;  
    input >> x;     
  }
  
  
}
