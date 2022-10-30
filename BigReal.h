//
// Created by bjabo on 10/30/2022.
//

#ifndef BIGREAL_BIGREAL_H
#define BIGREAL_BIGREAL_H

using namespace std;
#include <bits/stdc++.h>
#include "BigDecimalInt.h"

class BigReal{
    public:
        BigReal (double realNumber = 0.0);
        BigReal (string realNumber);
        BigReal (BigDecimalInt bigInteger);
        BigReal (const BigReal& other);
        BigReal& operator= (BigReal& other);
//        BigReal& operator= (BigReal&& other);
//        BigReal operator+ (BigReal& other);
//        BigReal operator- (BigReal& other);
//        bool operator< (BigReal anotherReal);
//        bool operator> (BigReal anotherReal);
//        bool operator== (BigReal anotherReal);
        int size();
        char sign();
        friend ostream& operator << (ostream& out, BigReal num);
//        friend istream& operator >> (istream& out, BigReal num);

    private:
        BigDecimalInt whole;
        BigDecimalInt fraction;

};


#endif //BIGREAL_BIGREAL_H
