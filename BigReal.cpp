#include "BigReal.h"
//#include <bits/stdc++.h>
#include <iostream>
#include <regex>
using namespace std;



//***********************************************************************************************************
BigReal::BigReal (const string &realNumber){
    setWhole(realNumber);
    setFraction(realNumber);
}

//***********************************************************************************************************
BigReal::BigReal(const double& realNumber){
    string number = to_string(realNumber);
    *this = BigReal(number);
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


BigReal::BigReal(const BigReal &&other) {
    this->whole = other.whole;
    this->fraction = other.fraction;
}

//***********************************************************************************************************
BigReal &BigReal::operator=(const BigReal&& other) {
    if(this == &other)
        return *this;
    this->whole = other.whole;
    this->fraction = other.fraction;
    return *this;
}

//***********************************************************************************************************
BigReal& BigReal::operator = (const BigReal& other){
    if(this == &other)
        return *this;
    this->whole = other.whole;
    this->fraction = other.fraction;
    return *this;
}

//***********************************************************************************************************
int BigReal::size()const{
    return fraction.size() + whole.size();  /////// KOSMEK anty kaman
}

//***********************************************************************************************************
char BigReal::sign()const{
    return whole.getSign();
}

void BigReal::setSign(const char &sign) {
    whole.setSign(sign);
}


//***********************************************************************************************************
bool BigReal::operator==(const BigReal& anotherReal)const {
    string leftFraction = this->fraction;
    string rightFraction= anotherReal.fraction;
    matchFractionSize(leftFraction, rightFraction); // 13.3500
    return ((this->whole==anotherReal.whole)&&(leftFraction==rightFraction));
}

//***********************************************************************************************************
BigReal BigReal::operator+(const BigReal& other)const{

    if(this->sign() != other.sign()){
        BigReal temp(other);
        temp.whole.setSign(this->sign());
        return *this-temp;
    }

    // fraction part addition
    string LHS = this->fraction;
    string RHS = other.fraction;

    matchFractionSize(LHS,RHS);

    string fractionResult;
    fractionResult.resize(LHS.size());
    int fractionCarry = 0 ;

    for (int i = LHS.size() - 1; i >= 0 ; --i) {
        int lhsDigit = LHS[i] - '0';
        int rhsDigit = RHS[i] - '0';
        int sum = lhsDigit + rhsDigit + fractionCarry;

        // if the sum of two digits will make overflow("greater than 9") we add fractionCarry to the next digit's sum
        if(sum>9) {
            fractionCarry = 1;
            sum%=10;
        }
        else{
            fractionCarry = 0;
        }
        fractionResult[i] = sum+'0';
    }
    // whole part addition
    BigDecimalInt wholeResult  = this->whole + other.whole;

    wholeResult = wholeResult+fractionCarry;

    BigReal result;
    result.whole = wholeResult;
    result.fraction = fractionResult;
    result.setSign(this->sign());

    return result;
}

//***********************************************************************************************************
BigReal BigReal::operator-(const BigReal& other) const {
    if(this->sign() != other.sign()) {
        BigReal temp(other);
        temp.whole.setSign(this->sign());
        return *this+temp;
    }

    BigReal bigger,smaller,result;

    result.whole = bigger.whole-smaller.whole;

    bigger.setSign('+');

    smaller = *this;
    char smallerSign = this->sign(); // save old sign
    smaller.setSign('+');

    bigger = other;
    if(bigger.sign()=='+') // flip sign (1 - +6) == (1 - 6)
    {
        bigger.setSign('-');
    }
    else {
        bigger.setSign('+');
    } // (1 - -6) == (1 + 6)

    char biggerSign = bigger.sign(); // save old sign
    bigger.setSign('+'); // get abs value


    if(smaller > bigger) { // assign the bigger and the smaller value and the result's sign
        result.setSign(smallerSign);
        swap(bigger,smaller);
    }
    else if(bigger > smaller) { // assign the bigger and the smaller value and the result's sign
        result.setSign(biggerSign);
    }
    else { // if they are equal return 0 (50 - 50) = 0
        result.setSign('+');
        return BigReal("0.0");
    }

    string biggerFraction = bigger.fraction;
    string smallerFraction = smaller.fraction;

    if(smallerFraction>biggerFraction){
        bigger = bigger - 1;
        biggerFraction[0]+=10;
    }

    matchFractionSize(biggerFraction,smallerFraction);
    result.fraction.resize(biggerFraction.size());

    for (int i = result.fraction.size() - 1 ; i >= 0; i--) {
        if(biggerFraction[i] < smallerFraction[i]) {
            biggerFraction[i-1]--;
            biggerFraction[i] += 10;
        }
        result.fraction[i] = biggerFraction[i]-smallerFraction[i]+'0';
    }
    return result;
}

//***********************************************************************************************************
bool BigReal::operator<(const BigReal& anotherReal)const{

    if(this->sign()=='-'&&anotherReal.sign()=='+')
        return true;
    // if the first number have a positive sign and the second number have negative sign function will return false
    if(this->sign()=='+'&&anotherReal.sign()=='-')
        return false;


    string LHSFraction = this->fraction;
    string RHSFraction = anotherReal.fraction;
    matchFractionSize(LHSFraction,RHSFraction); // add zeros to the right

    if(this->whole==anotherReal.whole){
        if(this->sign()=='-')
            return (LHSFraction > RHSFraction);
        else
            return (LHSFraction < RHSFraction);
    }
    else{
        return (this->whole<anotherReal.whole);
    }
}

//***********************************************************************************************************
bool BigReal::operator>(const BigReal &anotherReal)const{
    if(this->sign()=='-'&&anotherReal.sign()=='+')
        return false;
    // if the first number have a positive sign and the second number have negative sign function will return false
    if(this->sign()=='+'&&anotherReal.sign()=='-')
        return true;

    string LHSFraction = this->fraction;
    string RHSFraction = anotherReal.fraction;
    matchFractionSize(LHSFraction,RHSFraction);

    if(this->whole==anotherReal.whole){
        if(this->sign()=='-')
            return (LHSFraction < RHSFraction);
        else
            return (LHSFraction > RHSFraction);
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
        if (number[i] == '.' && pointIdx == -1){
            pointIdx = i;
        }
        else if (pointIdx != -1){  // found the decimal point
            fractionPart+=number[i];
        }
    }

    if(pointIdx==-1 || fractionPart.empty() || !regex_match(fractionPart, regex("\\d+") ) ){
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
//***********************************************************************************************************
