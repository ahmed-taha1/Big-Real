//
// Created by Ismail Magdy on 04/11/2022.
//

#ifndef ASS_2_BIGREAL_H
#define ASS_2_BIGREAL_H

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

    void setSign(const char& sing);

    BigReal operator+ (const BigReal& other)const;
    BigReal operator- (const BigReal& other)const;
    bool operator< (const BigReal& anotherReal)const;
    bool operator> (const BigReal& anotherReal)const;
    bool operator== (const BigReal& anotherReal)const;

    int size()const;
    char sign()const;

private:
    BigDecimalInt whole;
    string fraction;

    static void matchFractionSize(string& LHS, string& RHS);
    void setFraction(const string &number);
    void setWhole(const string &number);
};

#endif //ASS_2_BIGREAL_H
