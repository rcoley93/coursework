// $Id: bigint.cpp,v 1.61 2014-06-26 17:06:06-07 - - $

#include <cstdlib>
#include <exception>
#include <limits>
#include <stack>
#include <stdexcept>
#include <string>
#include <cmath>
using namespace std;
using digit = int;

#include "bigint.h"
#include "debug.h"

bigint::bigint (long that) {
   DEBUGF ('~', this << " -> " << that)
   string strThat = to_string(that);
   int iEnd = 0;
   if(that < 0){
      ++iEnd;
      negative = true;
   }
   for(int i = strThat.size()-1;i>=iEnd;--i){
      big_value.push_back(strThat[i]);
   }
   
   //remove all leading zeros
   for(int i = big_value.size()-1;i>=0;--i){
      if(big_value.at(i) == 0) big_value.pop_back();
      else break;
   }
   
   //if zero make positive
   if(big_value.size() == 0) negative = false;
}

bigint::bigint (const string& that) {
   int iEnd = 0;
   if (that[iEnd] == '_') {
      negative = true;
      ++iEnd;
   }
   else negative = false;
   
   for(int i = that.size()-1;i>=iEnd;--i){
      big_value.push_back(that[i]-'0');
   }
   
   //remove all leading zeros
   for(int i = big_value.size()-1;i>=0;--i){
      if(big_value.at(i) == 0) big_value.pop_back();
      else break;
   }
   
   //if zero make positive
   if(big_value.size() == 0) negative = false;
   
   DEBUGF ('~', this << " -> " << that)
   
}

//returns whether the result of + or - will be pos or neg
//depending on the larger magnitude of the two
bool isNeg(const bigint& pos, const bigint& neg){
   if(pos.big_value.size() > neg.big_value.size()) return false;
   else if(pos.big_value.size() < neg.big_value.size()) return true;
   else{
      for(int i = pos.big_value.size()-1;i>=0;--i)
         if(pos.big_value.at(i) > neg.big_value.at(i)) return false;
   }
   return true;
}

bigint doSub(const bigint& left, const bigint& right,bool neg){
   //init newVal
   bigint newVal;
   newVal.negative = neg;
   
   vector<int> upper;
   vector<int> lower;
   
   //see which one has greater magnitude
   if(left.big_value.size() > right.big_value.size()){
      upper = left.big_value;
      lower = right.big_value;
   }else if(left.big_value.size() < right.big_value.size()){
      upper = right.big_value;
      lower = left.big_value;
   }else{
      bool rLg = false;
      for(int i = left.big_value.size()-1;i>=0;--i){
         if(left.big_value.at(i) < right.big_value.at(i)) {
            rLg = true;
            break;
         }
      }
      if(rLg){
         upper = right.big_value;
         lower = left.big_value;
      }else{
         upper = left.big_value;
         lower = right.big_value;
      }
   }
   
   //subtraction algorithm
   for(unsigned int i = 0; i<lower.size();++i){
      //carry over bits
      while(lower.at(i) > upper.at(i)){
         upper.at(i) += 10;
         if(i<upper.size()-1) upper.at(i+1) -= 1;
      }
      newVal.big_value.push_back(upper.at(i) - lower.at(i));
   }
   for(unsigned int i = lower.size();i<upper.size();++i){
      newVal.big_value.push_back(upper.at(i));
   }
   
   //remove all leading zeros
   for(int i = newVal.big_value.size()-1;i>=0;--i){
      if(newVal.big_value.at(i) == 0) newVal.big_value.pop_back();
      else break;
   }
  
   //if zero make positive
   if(newVal.big_value.size() == 0) newVal.negative = false;
   
   return newVal;
}

bigint doAdd(const bigint& left, const bigint& right,bool neg){
   //init newVal
   bigint newVal;
   newVal.negative = neg;
   
   vector<int> upper;
   vector<int> lower;
   
   //see which one is longer
   if(left.big_value.size() > right.big_value.size()){
      upper = left.big_value;
      lower = right.big_value;
   }else{
      upper = right.big_value;
      lower = left.big_value;
   }
   
   digit carry = 0;
   //add all the numbers in the same columns
   for(unsigned int i = 0;i<lower.size();++i){
      digit total = carry + lower.at(i) + upper.at(i);
      newVal.big_value.push_back(total % 10);
      carry = total / 10;
   }
   //add the rest of the columns
   for(unsigned int i = lower.size();i<upper.size();++i){
      if(carry > 0){
         digit total = carry + upper.at(i); 
         carry = total / 10;
         newVal.big_value.push_back(total % 10);
      }else newVal.big_value.push_back(upper.at(i));
   }
   
   //if there still is a carry add it to the end ie 99 + 1 = 100
   if(carry > 0) newVal.big_value.push_back(carry);
   
   return newVal;
}

bigint operator+ (const bigint& left, const bigint& right) {
   bigint newVal;
   //neg + neg
   if(left.negative && right.negative) 
      return doAdd(left,right,true);
   //pos + neg
   else if(!left.negative && right.negative) 
      return doSub(left,right,isNeg(left,right));
   //neg + pos
   else if(left.negative && !right.negative) 
      return doSub(left,right,isNeg(right,left));
   //pos + pos
   else if(!left.negative && !right.negative)
      return doAdd(left,right,false);
   return newVal;
}

bigint operator- (const bigint& left, const bigint& right) {
   bigint newVal;
   //neg - neg = neg + pos
   if(left.negative && right.negative) 
      return doSub(left,right,isNeg(right,left));
   //pos - neg = pos + pos
   else if(!left.negative && right.negative) 
      return doAdd(left,right,false);
   //neg - pos = neg + neg
   else if(left.negative && !right.negative) 
      return doAdd(left,right,true);
   //pos - pos = pos + neg
   else if(!left.negative && !right.negative) 
      return doSub(left,right,isNeg(left,right));
   return newVal;
}

bigint operator+ (const bigint& right) {
   return +right;
}

bigint operator- (const bigint& right) {
   return -right;
}

long bigint::to_long() const {
   long newVal = 0;
   if (*this <= bigint (numeric_limits<long>::min())
    or *this > bigint (numeric_limits<long>::max()))
               throw range_error ("bigint__to_long: out of range");
   for(unsigned int i = 0;i<this->big_value.size(); ++i){
      newVal += pow(this->big_value.at(i),i);
   }
   return newVal;
}

bool abs_less(const bigint& left, const bigint& right) {
   return left < right;
}

//
// Multiplication algorithm.
//
bigint operator* (const bigint& left, const bigint& right) {
   //initialize new bigint
   bigint newVal;
   int length = 
   static_cast<int>(left.big_value.size() + right.big_value.size()+1);
   for(int i = 0;i<length;++i) newVal.big_value.push_back(0);
   newVal.negative = (left.negative == right.negative) ? false : true;
   
   //do multiplication
   for(unsigned int i = 0;i<left.big_value.size();++i){
      digit carry = 0;
      for(unsigned int j = 0;j<right.big_value.size();++j){
         digit total = newVal.big_value.at(i+j) + 
         (right.big_value.at(j) * left.big_value.at(i)) + carry;
         newVal.big_value.at(i+j) = total % 10;
         carry = total / 10;
      }
      newVal.big_value.at(i+right.big_value.size()) = carry;
   }
   
   //remove all leading zeros
   for(int i = newVal.big_value.size()-1;i>=0;--i){
      if(newVal.big_value.at(i) == 0) newVal.big_value.pop_back();
      else break;
   }
   
   //if zero make positive
   if(newVal.big_value.size() == 0) newVal.negative = false;
   
   return newVal;
}

//
// Division algorithm.
//

void multiply_by_2 (bigint& unumber_value) {
   for(auto d : unumber_value.big_value)
      d *= 2;
}

void divide_by_2 (bigint& unumber_value) {
   for(auto d : unumber_value.big_value)
      d /= 2;
}

bigint::quot_rem divide (const bigint& left, const bigint& right) {
   if (right == 0) throw domain_error ("divide by 0");
   static bigint zero = 0;
   if (right == 0) throw domain_error ("bigint::divide");
   bigint divisor = right;
   bigint quotient = 0;
   bigint remainder = left;
   bigint power_of_2 = 1;
   while (abs_less (divisor, remainder)) {
      multiply_by_2 (divisor);
      multiply_by_2 (power_of_2);
   }
   while (abs_less (zero, power_of_2)) {
      if (not abs_less (remainder, divisor)) {
         remainder = remainder - divisor;
         quotient = quotient + power_of_2;
      }
      divide_by_2 (divisor);
      divide_by_2 (power_of_2);
   }
   
   return {quotient, remainder};
}

bigint operator/ (const bigint& left, const bigint& right) {
   return divide (left, right).first;
}

bigint operator% (const bigint& left, const bigint& right) {
   return divide (left, right).second;
}

//are they the same
bool operator== (const bigint& left, const bigint& right) {
   if(left.negative != right.negative) return false;
   if(left.big_value.size() != right.big_value.size()) return false;
   else{
      for(unsigned int i = 0;i<left.big_value.size();++i)
         if(left.big_value.at(i) != right.big_value.at(i)) 
            return false;
   }
   return true;
}

//is left < right
bool operator< (const bigint& left, const bigint& right) {
   if(left.negative && right.negative){
      if(left.big_value.size() > right.big_value.size())
         return true;
      else if(left.big_value.size() < right.big_value.size())
         return false;
      else{
         for(unsigned int i = 0;i<left.big_value.size();++i){
            if(left.big_value.size() < right.big_value.size())
               return false;
         }
      }
   }else if(!left.negative && !right.negative){
      if(left.big_value.size() > right.big_value.size())
         return false;
      else if(left.big_value.size() < right.big_value.size())
         return true;
      else{
         for(unsigned int i = 0;i<left.big_value.size();++i){
            if(left.big_value.size() > right.big_value.size())
               return false;
         }
      }
   }else if(left.negative && !right.negative){
      return true;
   }else if(!left.negative && right.negative){
      return false;
   }
   return true;
}

//output the bigint
ostream& operator<< (ostream& out, const bigint& that) {
   if(that.negative) out << "-";
   int colCount = 0;
   for (int i = that.big_value.size()-1;i>=0;--i){
      out << that.big_value[i];
      ++colCount;
      if(colCount % 70 == 0){
         cout<<"\\"<<endl;
         colCount = 0;
      }
   }
   return out;
}

bigint pow (const bigint& base, const bigint& exponent) {
   DEBUGF ('^', "base = " << base << ", exponent = " << exponent);
   if (base == 0) return 0;
   bigint base_copy = base;
   long expt = exponent.to_long();
   bigint result = 1;
   if (expt < 0) {
      base_copy = 1 / base_copy;
      expt = - expt;
   }
   while (expt > 0) {
      if (expt & 1) { //odd
         result = result * base_copy;
         --expt;
      }else { //even
         base_copy = base_copy * base_copy;
         expt /= 2;
      }
   }
   DEBUGF ('^', "result = " << result);
   return result;
}
