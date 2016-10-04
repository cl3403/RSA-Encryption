#ifndef NUMBERTHEORY_H
#define NUMBERTHEORY_H


template <class X>
bool isPrime(const X& num)
{
  if ((num == 0) || (num == 1))
  {
    return false;
  }

  else
  {
    for (unsigned long long i = 2; i <= num/2; i++)
    {
      if (num % i == 0)
      {
        return false;
      }
    }
    return true;
  }
}

template <class X>
X modPower(const X& base, const X& exponent, const X& modulus)
{
  if (base == 0)
  {
    return 0;
  }

  else if (exponent == 0)
  {
    if (modulus == 1)
    {
      return 0;
    }
    else
    {
      return 1;
    }
  }

  else
  {
    if (exponent == 1)
    {
      return base;
    }
    else
    {
      if (exponent % 2 == 0)
      {
        X partResult = modPower(base,exponent / 2,modulus);
        return partResult * partResult % modulus;
      }
      else
      {
        X partResult = modPower(base,exponent / 2,modulus);
        return base * partResult % modulus * partResult % modulus;
      }
    }
  }
}

template <class X>
X extendedEuclid(const X& a, const X& b, X& x, X& y)
{
  if (b == 0)
  {
    x = 1;
    y = 0;
    return a;
  }
  
  else
  {
    X gcd = extendedEuclid(b,a % b,x,y);
    X oldX = x;
    x = y;
    y = oldX - (a/b) * y;
    return gcd;
  }
}

#endif
