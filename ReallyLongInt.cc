#include "ReallyLongInt.h"
#include <iostream>
#include <cmath>
#include <climits>

ReallyLongInt::ReallyLongInt()
{
  isNeg = false;
  digits = new unsigned char[1];
  digits[0] = 0;
  numDigits = 1;
}

ReallyLongInt::ReallyLongInt(const string& numStr)
{
  if (numStr[0] == '-')
  {
    isNeg = true;
    numDigits = numStr.size() - 1;
    digits = new unsigned char[numDigits];
    for (unsigned i = 0; i < numDigits; i++)
    {
      digits[i] = numStr[i+1] - 48;
    }
  }
 
  else
  {
    isNeg = false;
    numDigits = numStr.size();
    digits = new unsigned char[numDigits];
    for (unsigned i = 0; i < numDigits; i++)
    {
      digits[i] = numStr[i] - 48;
    }
  }

  removeLeadingZeros();
}

ReallyLongInt::ReallyLongInt(long long num)
{
  if (num == 0)
  {
    isNeg = false;
    numDigits = 1;
    digits = new unsigned char[1];
    digits[0] = 0;
  }

  else
  {
    if (num < 0)
    {
      isNeg = true;
      num = -num;
    }
 
    else
    {
      isNeg = false;
    }
    numDigits = 1 + log10(num);
    digits = new unsigned char[numDigits];
    unsigned digit;
    for (unsigned i = numDigits; i > 0; i--)
    {
      digit = num % 10;
      num = num / 10;
      digits[i-1] = digit;
    }
  }
}

void ReallyLongInt::removeLeadingZeros()
{
  unsigned count = 0;
  unsigned item = digits[count];
  unsigned lZeros = 0;
  while ((int(item) == 0) && (count != numDigits - 1))
  {
    lZeros += 1;
    item = digits[++count];
  }
  
  if ((lZeros == numDigits - 1) && (int(item) == 0))
  {  
    numDigits = 1;
  }
  else
  {
    numDigits -= lZeros;
  }
  
  if (lZeros != 0)
  {
    for (unsigned i = 0; i < numDigits; i++)
    {
      digits[i] = digits[i + lZeros];
    }
  }
}

ReallyLongInt::ReallyLongInt(bool isNeg, unsigned char* digits, unsigned numDigits)
{
  this->isNeg = isNeg;
  this->digits = digits;
  this->numDigits = numDigits;
  removeLeadingZeros();
}

ReallyLongInt::~ReallyLongInt()
{
  delete[] digits;
}

ostream& ReallyLongInt::print(ostream& out) const
{
  if ((isNeg == true) && (digits[0] != 0))
  {
    out << '-';
  }

  for (unsigned i = 0; i < numDigits; i++)
  {
    out << int(digits[i]);
  }
  
  return out;  
}

ostream& operator<<(ostream& out, const ReallyLongInt& x)
{
  x.print(out);
  return out;
}

ReallyLongInt::ReallyLongInt(const ReallyLongInt& other)
{
  isNeg = other.isNeg;
  numDigits = other.numDigits;
  digits = new unsigned char[numDigits];
  for (unsigned i = 0; i < numDigits; i++)
  {
    digits[i] = other.digits[i];
  }
}

ReallyLongInt& ReallyLongInt::operator=(const ReallyLongInt& other)
{
  ReallyLongInt copy(other);
  swap(this->isNeg,copy.isNeg);
  swap(this->numDigits,copy.numDigits);
  swap(this->digits,copy.digits);
 
  return *this; 
}

bool ReallyLongInt::equal(const ReallyLongInt& other) const
{  
  if (numDigits != other.numDigits)
  {
    return false;
  }
  else
  {
    for (unsigned i = 0; i < numDigits; i++)
    {
      if (digits[i] != other.digits[i])
      {
        return false;
      }
    }
  }

  if (isNeg != other.isNeg)
  {
    if (digits[0] != 0)
    {
      return false;
    }
  } 
  return true;
}

bool ReallyLongInt::absGreater(const ReallyLongInt& other) const
{
  if (numDigits > other.numDigits)
  {
    return true;
  }
  else if (numDigits < other.numDigits)
  {
    return false;
  }
  else
  {
    for (unsigned i = 0; i < numDigits; i++)
    {
      if (digits[i] < other.digits[i])
      {
        return false;
      }
      else if (digits[i] > other.digits[i])
      {
        return true;
      }
    }
    return false;
  }  
}

bool ReallyLongInt::greater(const ReallyLongInt& other) const
{
  if (isNeg != other.isNeg)
  {
    if ((digits[0] == 0) && (other.digits[0] == 0))
    {
      return false;
    }
    else if (isNeg == false)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  
  if (isNeg == true)
  {
    return !absGreater(other);
  }
  else
  {
    return absGreater(other);
  }
}

bool operator==(const ReallyLongInt& x, const ReallyLongInt& y)
{
  return x.equal(y);
}
bool operator!=(const ReallyLongInt& x, const ReallyLongInt& y)
{
  return !x.equal(y);
}
bool operator>(const ReallyLongInt& x, const ReallyLongInt& y)
{
  return x.greater(y);
}
bool operator<(const ReallyLongInt& x, const ReallyLongInt& y)
{
  return y.greater(x);
}
bool operator>=(const ReallyLongInt& x, const ReallyLongInt& y)
{
  return !y.greater(x);
}
bool operator<=(const ReallyLongInt& x, const ReallyLongInt& y)
{
  return !x.greater(y);
}

ReallyLongInt ReallyLongInt::absAdd(const ReallyLongInt& other) const
{
  unsigned sizeX = numDigits;
  unsigned sizeY = other.numDigits;
  unsigned arrSize = max(sizeX,sizeY) + 1;
  unsigned resultSize = arrSize;
  unsigned char* newArr = new unsigned char[resultSize];
  unsigned newDigit;
  unsigned addDigit = 0;
  while ((sizeX != 0) || (sizeY != 0))
  {
    if ((sizeX != 0) && (sizeY != 0))
    {
      newDigit = digits[sizeX-1] + other.digits[sizeY-1] + addDigit;
      if (newDigit >= 10)
      {
        newDigit -= 10;
        addDigit = 1;
      }
      else
      {
        addDigit = 0;
      }
      newArr[arrSize-1] = newDigit;
      sizeX--;
      sizeY--;
      arrSize--;   
    }

    else
    {
      if (sizeX != 0)
      {
        newDigit = digits[sizeX-1] + addDigit;
        if (newDigit >= 10)
        {
          newDigit -= 10;
          addDigit = 1;
        }
        else
        {
          addDigit = 0;
        }
        newArr[arrSize-1] = newDigit;
        sizeX--;
        arrSize--;
      }
      else
      {
        newDigit = other.digits[sizeY-1] + addDigit;
        if (newDigit >= 10)
        {
          newDigit -= 10;
          addDigit = 1;
        }
        else
        {
          addDigit = 0;
        }
        newArr[arrSize-1] = newDigit;
        sizeY--;
        arrSize--;
      }
    }
  }
  
  newArr[0] = addDigit;

  return ReallyLongInt(false,newArr,resultSize);
}

ReallyLongInt ReallyLongInt::absSub(const ReallyLongInt& other) const
{
  bool resultNeg;
  unsigned char* bigNum;
  unsigned char* smallNum;
  unsigned sizeBig;
  unsigned sizeSmall;
  
  if (absGreater(other))
  {
    resultNeg = false;
    bigNum = digits;
    smallNum = other.digits;
    sizeBig = numDigits;
    sizeSmall = other.numDigits;
  }
  else
  {
    resultNeg = true;
    bigNum = other.digits;
    smallNum = digits;
    sizeBig = other.numDigits;
    sizeSmall = numDigits;
  }

  unsigned arrSize = sizeBig;
  unsigned resultSize = arrSize;
  unsigned char* newArr = new unsigned char[resultSize];
  unsigned newDigit;
  unsigned minusDigit = 0;
  
  while (sizeBig != 0)
  {
    if (sizeSmall != 0)
    {
      if (bigNum[sizeBig-1] >= (minusDigit + smallNum[sizeSmall-1]))
      {
        newDigit = bigNum[sizeBig-1] - minusDigit - smallNum[sizeSmall-1];
        minusDigit = 0;
      }
      else
      {
        newDigit = bigNum[sizeBig-1] - minusDigit + 10 - smallNum[sizeSmall-1];
        minusDigit = 1;
      }
      newArr[arrSize-1] = newDigit;
      sizeBig--;
      sizeSmall--;
      arrSize--;   
    }

    else
    {
      if (bigNum[sizeBig-1] >= minusDigit)
      {
        newDigit = bigNum[sizeBig-1] - minusDigit;
        minusDigit = 0;
      }
      else
      {
        newDigit = bigNum[sizeBig-1] + 10 - minusDigit ;
        minusDigit = 1;
      }
      newArr[arrSize-1] = newDigit;
      sizeBig--;
      arrSize--;        
    }
  }
  
  return ReallyLongInt(resultNeg,newArr,resultSize);
}

void ReallyLongInt::flipSign()
{
  if (isNeg == true)
  {
    isNeg = false;
  }
  else
  {
    isNeg = true;
  }
}

ReallyLongInt ReallyLongInt::operator-() const
{ 
  ReallyLongInt copy(*this);
  copy.flipSign();
  return copy;  
}

ReallyLongInt ReallyLongInt::add(const ReallyLongInt& other) const
{
  ReallyLongInt newLongInt;
  if ((isNeg == false) && (other.isNeg == false))
  {
    newLongInt = absAdd(other);
  }
  else if ((isNeg == true) && (other.isNeg == true))
  {
    newLongInt = absAdd(other);
    newLongInt.flipSign();
  }
  else if ((isNeg == false) && (other.isNeg == true))
  {
    newLongInt = absSub(other);
  }
  else if ((isNeg == true) && (other.isNeg == false))
  {
    newLongInt = other.absSub(*this);
  }
  return newLongInt;
}

ReallyLongInt ReallyLongInt::sub(const ReallyLongInt& other) const
{
  ReallyLongInt newLongInt;
  if ((isNeg == false) && (other.isNeg == false))
  {
    newLongInt = absSub(other);
  }
  else if ((isNeg == true) && (other.isNeg == true))
  {
    newLongInt = absSub(other);
    newLongInt.flipSign();
  }
  else if ((isNeg == false) && (other.isNeg == true))
  {
    newLongInt = absAdd(other);
  }
  else if ((isNeg == true) && (other.isNeg == false))
  {
    newLongInt = absAdd(other);
    newLongInt.flipSign();
  }
  return newLongInt;
}

ReallyLongInt operator+(const ReallyLongInt& x, const ReallyLongInt& y)
{
  return x.add(y);
}

ReallyLongInt operator-(const ReallyLongInt& x, const ReallyLongInt& y)
{
  return x.sub(y);
}

ReallyLongInt& ReallyLongInt::operator+=(const ReallyLongInt& other)
{
  *this = *this + other;
  return *this; 
}

ReallyLongInt& ReallyLongInt::operator-=(const ReallyLongInt& other)
{
  *this = *this - other;
  return *this; 
}

ReallyLongInt& ReallyLongInt::operator++()
{
  *this += 1;
  return *this;
}

ReallyLongInt& ReallyLongInt::operator--()
{
  *this -= 1;
  return *this;
}

ReallyLongInt ReallyLongInt::operator--(int dummy)
{
  ReallyLongInt copy(*this);
  *this -= 1;
  return copy;
}

ReallyLongInt ReallyLongInt::operator++(int dummy)
{
  ReallyLongInt copy(*this);
  *this += 1;
  return copy;
}

ReallyLongInt ReallyLongInt::absMult(const ReallyLongInt& other) const
{
  unsigned resultSize = numDigits + other.numDigits;
  unsigned char* mulArr = new unsigned char[resultSize];
  unsigned newDigit;

  for (unsigned j = 0; j < resultSize; j++)
  {
    mulArr[j] = 0;
  }

  for (unsigned i = other.numDigits; i > 0; i--)
  {
    unsigned addDigit = 0;
    unsigned trackSize = resultSize - (other.numDigits - i);
    for (unsigned j = numDigits; j > 0;j--)
    {
      newDigit = digits[j-1] * other.digits[i-1] + addDigit + mulArr[trackSize-1];
      if (newDigit >= 10)
      {
        addDigit = newDigit / 10;
        newDigit = newDigit % 10;          
      }
      else
      {
        addDigit = 0;
      }
      mulArr[trackSize-1] = newDigit; 
      trackSize--;
    }
   
    if (addDigit != 0)
    {
      mulArr[trackSize-1] += addDigit;
    }
  }

  return ReallyLongInt(false,mulArr,resultSize);  
}

ReallyLongInt ReallyLongInt::mult(const ReallyLongInt& other) const
{
  ReallyLongInt newLongInt = absMult(other);
  if (this->isNeg != other.isNeg)
  {
    newLongInt.flipSign();
  }
  return newLongInt;
}

ReallyLongInt operator*(const ReallyLongInt& x, const ReallyLongInt& y)
{
  return x.mult(y);
}

ReallyLongInt&  ReallyLongInt::operator*=(const ReallyLongInt& other)
{
  *this = *this * other;
  return *this; 
}

void ReallyLongInt::absDiv(const ReallyLongInt& other, ReallyLongInt& quotient, ReallyLongInt& remainder) const
{
  unsigned char* quoArr = new unsigned char[numDigits];
  ReallyLongInt y(other);
  y.isNeg = false;
  ReallyLongInt r;
  unsigned d;
  for (unsigned i = 0; i < numDigits; i++)
  {
    r *= 10;
    r = r + digits[i];
    d = 0;
    
    while (r >= y)
    {
      r -= y;
      d += 1;
    }
    quoArr[i] = d;
  }
  quotient = ReallyLongInt(false,quoArr,numDigits);
  remainder = r;
} 
 
void ReallyLongInt::div(const ReallyLongInt& denominator, ReallyLongInt& quotient, ReallyLongInt& remainder) const
{
  absDiv(denominator,quotient,remainder);
  if (this->isNeg != denominator.isNeg)
  {
    quotient.flipSign();
  }

  if (this->isNeg == true)
  {
    remainder.flipSign();
  }
  
}

ReallyLongInt operator/(const ReallyLongInt& x, const ReallyLongInt& y)
{
  ReallyLongInt quotient;
  ReallyLongInt remainder;
  x.div(y,quotient,remainder);
  return quotient;
}

ReallyLongInt operator%(const ReallyLongInt& x, const ReallyLongInt& y)
{
  ReallyLongInt quotient;
  ReallyLongInt remainder;
  x.div(y,quotient,remainder);
  return remainder;
}

ReallyLongInt& ReallyLongInt::operator/=(const ReallyLongInt& other)
{
  *this = *this / other;
  return *this; 
}

ReallyLongInt& ReallyLongInt::operator%=(const ReallyLongInt& other)
{
  *this = *this % other;
  return *this; 
}

long long ReallyLongInt::toLongLong() const
{
  ReallyLongInt denominator = ReallyLongInt(LLONG_MAX);
  denominator += 1;
  ReallyLongInt resultLongInt = *this % denominator;
  long long resultNum = 0;
  unsigned long long power = 1;
  for (unsigned i = resultLongInt.numDigits; i > 0; i--)
  {
    resultNum += resultLongInt.digits[i-1] * power; 
    power *= 10;
  }

  if (resultLongInt.isNeg == true)
  {
    resultNum *= -1;
  }
  return resultNum;
}
