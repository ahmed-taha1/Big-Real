#include "BigReal.h"
//#include <bits/stdc++.h>
#include <iostream>
#include <regex>
using namespace std;



//***********************************************************************************************************
BigReal::BigReal (const string &realNumber){ // 12412+12412
    /// find (.)-> 120481390513875981327 if there is no '.'
    setWhole(realNumber);
    setFraction(realNumber);
}


//***********************************************************************************************************
BigReal::BigReal(const double& realNumber){
    string number = to_string(realNumber);
    /// (*this) = BigReal(number);       //////////////////////////////// KOSMEK
    this->whole = BigReal(number).whole;
    this->fraction = BigReal(number).fraction;
}

//***********************************************************************************************************
BigReal::BigReal (const BigDecimalInt& bigInteger){
    this->whole = bigInteger;
    this->fraction = "0";
}


//***********************************************************************************************************
BigReal::BigReal (const BigReal& other){
    this->whole = other.whole;
    this->fraction = other.fraction;
}


//***********************************************************************************************************
BigReal& BigReal::operator = (const BigReal& other){
    this->whole = other.whole;
    this->fraction = other.fraction;
    return *this;
}


//***********************************************************************************************************
int BigReal::size(){
    return fraction.size() + whole.size();  /////// KOSMEK anty kaman
}


//***********************************************************************************************************
char BigReal::sign(){
    return whole.getSign();
}




//***********************************************************************************************************
bool BigReal::operator==(const BigReal& anotherReal)const {
    string leftFraction = this->fraction;
    string rightFraction= anotherReal.fraction;
    matchFractionSize(leftFraction, rightFraction);
    return ((this->whole==anotherReal.whole)&&(leftFraction==rightFraction));
}

//***********************************************************************************************************
bool BigReal::operator<(const BigReal& anotherReal)const{
    if(this->whole==anotherReal.whole){
        return (this->fraction<anotherReal.fraction);
    }
    else
        return (this->whole<anotherReal.whole);
}


//***********************************************************************************************************
bool BigReal::operator>(const BigReal &anotherReal) const {
    if(this->whole==anotherReal.whole){
        return (this->fraction>anotherReal.fraction);
    }
    else
        return (this->whole>anotherReal.whole);
}


//***********************************************************************************************************
ostream& operator << ( ostream& out,const BigReal& num){
    out<<num.whole<<"." << num.fraction;
    return  out;
}


//***********************************************************************************************************
istream& operator >> (istream& in,BigReal& num){
    string str;
    in >> str;
    num = BigReal(str);
    return in;
}


//***********************************************************************************************************
void BigReal::setFraction(const string &number){
    int pointIdx = -1;
    string fractionPart;
    for (int i = 0; i <number.size(); ++i) {
        if (number[i] == '.'){
            pointIdx = i;
        }
        else if (pointIdx != -1){  // found the decimal point
            fractionPart+=number[i];
        }
    }

    if(pointIdx==-1 || fractionPart.empty() ||! regex_match(fractionPart, regex("\\d+") ) ){
        this->fraction ="0";
        return;
    }

    // remove trailing zeros
    for (int i = fractionPart.size()-1; i>=0 ; --i){
        if(fractionPart[i]!='0'){
            break;
        }
        fractionPart.erase(i,1);
    }

    if(fractionPart.empty())
        this->fraction = "0";
    else
        this->fraction = fractionPart;
}

//***********************************************************************************************************
void BigReal::setWhole(const string &number) {
    string wholePart ;
    for (const char& i : number) {
        if(i=='.')
            break;
        wholePart+=i;
    }
    this->whole = BigDecimalInt(wholePart);
}

//***********************************************************************************************************
void BigReal::matchFractionSize(string &LHS, string &RHS){
    long long diff = abs((long long)LHS.size()-(long long)RHS.size());
    for(long long i = 0; i < diff; i++){
        // add trailing zeros to the shorter number to facilitate operations
        if(RHS.size() > LHS.size()){
            LHS.push_back('0');
        }
        else{
            RHS.push_back('0');
        }
    }
}
