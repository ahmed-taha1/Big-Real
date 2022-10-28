#include <bits\stdc++.h>
#include "BigDecimalInt.h"
#include "BigDecimalInt.cpp"

using namespace std;

class BigReal{
    public:
        BigReal (double realNumber = 0.0);
        BigReal (string realNumber);
        BigReal (BigDecimalInt bigInteger);
        BigReal (const BigReal& other);
        BigReal& operator= (BigReal& other);
        BigReal& operator= (BigReal&& other); 
        BigReal operator+ (BigReal& other);
        BigReal operator- (BigReal& other);
        bool operator< (BigReal anotherReal);
        bool operator> (BigReal anotherReal);
        bool operator== (BigReal anotherReal);
        int size();
        int sign();
        friend ostream& operator << (ostream& out, BigReal num);
        friend istream& operator >> (istream& out, BigReal num);

    private:
        BigDecimalInt whole, fraction;

};