//
// Created by bjabo on 11/14/2022.
//

#ifndef BIGREAL_BIGREAL_H
#define BIGREAL_BIGREAL_H

#include <bits/stdc++.h>
#include <iostream>
#include "BigDecimalInt.h"

using namespace std;

class BigReal{
    friend ostream& operator << (ostream& out,const BigReal& num);
    friend istream& operator >> (istream& in, BigReal& num);
public:
    BigReal (double realNumber = 0.0);
    BigReal (const string &realNumber);
    BigReal (const BigDecimalInt &bigInteger);
    BigReal (const BigReal& other);
    BigReal& operator= (const BigReal& other);
    BigReal (const BigReal&& other);
    BigReal& operator= (const BigReal&& other);

    void setSign(char sign);

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

#endif //ASS_2_BIGREAL_H //BIGREAL_BIGREAL_H
