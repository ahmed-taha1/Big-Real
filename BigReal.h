//
// Created by bjabo on 10/30/2022.
//

#ifndef BIGREAL_BIGREAL_H
#define BIGREAL_BIGREAL_H

//#include <bits/stdc++.h>
#include <iostream>
#include "BigDecimalInt.h"

using namespace std;

class BigReal{
    friend ostream& operator << (ostream& out,const BigReal& num);
    friend istream& operator >> (istream& in, BigReal& num);
public:
    BigReal (const double &realNumber = 0.0);
    BigReal (const string &realNumber);
    BigReal (const BigDecimalInt &bigInteger);
    BigReal (const BigReal& other);
    BigReal& operator= (const BigReal& other);
    //BigReal (BigReal&& other);
    //BigReal& operator= (BigReal&& other);


    //BigReal operator+ (BigReal& other);
    //BigReal operator- (BigReal& other);
    bool operator< (const BigReal& anotherReal)const;
    bool operator> (const BigReal& anotherReal)const;
    bool operator== (const BigReal& anotherReal)const;

    int size();
    char sign();


private:
    BigDecimalInt whole;
    string fraction;

    static void matchFractionSize(string& LHS, string& RHS);
    void setFraction(const string &number);
    void setWhole(const string &number);
};


#endif //BIGREAL_BIGREAL_H
