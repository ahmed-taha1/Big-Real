//
// Created by Ismail Magdy on 04/11/2022.
//

#ifndef BIGREAL_BIGDECIMALINT_H
#define BIGREAL_BIGDECIMALINT_H

//#include <bits/stdc++.h>
#include <iostream>
#include <deque>
using namespace std;


class BigDecimalInt {

    // cout operator overloading function
    friend ostream& operator<<(ostream& out,const BigDecimalInt& bigint);

public:

    // constructors
    BigDecimalInt(const string& num);
    BigDecimalInt(const long long int &num=0);
    BigDecimalInt(const BigDecimalInt& num);

    // getter functions
    int size()const;
    char getSign()const;

    // setter
    void setSign(const char &sign);

    // operator overloading functions
    BigDecimalInt& operator=(const BigDecimalInt& num);
    BigDecimalInt operator+(const BigDecimalInt& num)const;
    BigDecimalInt operator-(const BigDecimalInt& other)const;
    bool operator< (const BigDecimalInt& anotherDec)const;
    bool operator> (const BigDecimalInt& anotherDec)const;

    bool operator==(const BigDecimalInt& anotherDec)const;
private:
    deque<char> digits; // for storing digits from the string

    char sign;  // to store the sign
    void validate(const string &num); // helper /utility function
    static void matchSize(BigDecimalInt& LHS,BigDecimalInt& RHS);// helper /utility function
};
#endif //ASS_2_BIGDECIMALINT_H
