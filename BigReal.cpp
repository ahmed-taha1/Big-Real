#include "BigReal.h"
//#include <bits/stdc++.h>
#include <iostream>
#include <regex>
using namespace std;



// **********************************************************************
BigReal::BigReal (const string &realNumber){ // 12412+12412
    string wholePart = realNumber.substr(0, realNumber.find('.'));
    this->fraction = extractFraction(realNumber);
    this->whole = BigDecimalInt(wholePart);
}

// **************************************************************************

BigReal::BigReal(const double& realNumber){
    string number = to_string(realNumber);
    // (*this) = BigReal(number);    ///////////////////////////////// KOSMEK
    this->whole = BigReal(number).whole;
    this->fraction = BigReal(number).fraction;
}

// // **************************
BigReal::BigReal (const BigDecimalInt& bigInteger){
    this->whole = bigInteger;
    this->fraction = "0";
}


// // **************************
BigReal::BigReal (const BigReal& other){
    this->whole = other.whole;
    this->fraction = other.fraction;
}


// **************************
BigReal& BigReal::operator = (const BigReal& other){
    this->whole = other.whole;
    this->fraction = other.fraction;
    return *this;
}


// **************************
int BigReal::size(){
    return fraction.size() + whole.getSize();  /////// KOSMEK anty kaman
}


// **************************
char BigReal::sign(){
    return whole.getSign();
}


// **************************
ostream& operator << ( ostream& out,const BigReal& num){
    out<<num.whole;
    out<<"." ;
    out<< num.fraction;
    return  out;
}


istream& operator >> (istream& in,BigReal& num){
    string str;
    in >> str;
    num = BigReal(str);
    return in;
}



bool BigReal::operator==(const BigReal& anotherReal)const {
    string leftFraction = this->fraction;
    string rightFraction= anotherReal.fraction;
    matchSize(leftFraction,rightFraction);
    return ((this->whole==anotherReal.whole)&&(leftFraction==rightFraction));
}


bool BigReal::operator<(const BigReal& anotherReal)const{
    if(this->whole==anotherReal.whole){
        return (this->fraction<anotherReal.fraction);
    }
    else
        return (this->whole<anotherReal.whole);
}

bool BigReal::operator>(const BigReal &anotherReal) const {
    if(this->whole==anotherReal.whole){
        return (this->fraction>anotherReal.fraction);
    }
    else
        return (this->whole>anotherReal.whole);
}



string BigReal::extractFraction(string number){

    number = number.substr(number.find('.')+1, number.size());

    if (! regex_match(number, regex("\\d+") ) ){
        return "0";
    }

    bool found = false;
    long long i = number.size() - 1;
    for(; i >= 0; i--){
        if(number[i] == '0')
            found = true;
        else
            break;
    }

    if(found)
        number.erase(i + 1, number.size());
    if(number.empty())
        number = "0";
    return number;
}


void BigReal::matchSize(string &LHS, string &RHS){
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