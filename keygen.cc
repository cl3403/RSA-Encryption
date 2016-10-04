#include <fstream>
#include <iostream>
#include <cstdlib>
#include "numberTheory.h"
#include "ReallyLongInt.h"

using namespace std;


int main(int argc, char** argv)
{
  ReallyLongInt p(argv[1]);
  ReallyLongInt q(argv[2]);

  if ((p > 100000) || (q > 100000))
  {
    cout << "At least one number is larger than 100,000 so primality is not verified" << endl;
  }
  else
  {
    if ((!isPrime(p)) || (!isPrime(q)))
    {
      cout << "Error: at least one provided number is not prime" << endl;
      return 1;
    }
  }

  if (p == q)
  {
    cout << "Error: the algorithm doesn't work when p and q are the same number" << endl;
    return 1;
  }

  ReallyLongInt n = p * q;
  if (n < 256)
  {
    cout << "Error: n must be at least 256. Need larger provided numbers." << endl;
    return 1;
  }

  ReallyLongInt t = (p-1) * (q-1);

  ReallyLongInt e = 2;
  ReallyLongInt x,y;
 
  while (extendedEuclid(e,t,x,y) != 1)
  {
    e++;
  }
  
  ReallyLongInt d = 0; 
  if (x < 0) 
  {
    d = x + t;
  }
  else
  {
    d = x;
  }


  ofstream publicKey(argv[3]);
  ofstream privateKey(argv[4]);
  
  publicKey << e << " " << n << endl;
  privateKey << d << " " << n << endl;
   
}
