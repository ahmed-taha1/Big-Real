#include "BigReal.h"
#include <bits/stdc++.h>
using namespace std;

string extractFraction(string str){
    str = str.substr(str.find('.')+1, str.size());
    bool found = false;
    long long i = str.size() - 1;
    for(; i >= 0; i--)
        if(str[i] == '0')
            found = true;
        else
            break;
    if(found)
        str.erase( i  + 1, str.size());
    return str;
}

 BigReal::BigReal(double realNumber){
     int n = realNumber;
     BigDecimalInt wh(n);
     whole = wh;
     realNumber-=int(realNumber);
     string str = to_string(realNumber);
     str = extractFraction(str);
     BigDecimalInt fra(str);
     fraction = fra;
 }


// *************************
 BigReal::BigReal (string realNumber){
     string wholeStr = realNumber.substr(0, realNumber.find('.'));
     string fractionStr = extractFraction(realNumber);
     BigDecimalInt wh(wholeStr), fra(fractionStr);
     whole = wh;
     fraction = fra;
}


// // **************************
 BigReal::BigReal (BigDecimalInt bigInteger){
     whole = bigInteger;
}


// // **************************
 BigReal::BigReal (const BigReal& other){
     this->whole = other.whole;
     this->fraction = other.fraction;
}


// // **************************
 BigReal& BigReal::operator= (BigReal& other){
     this->whole = other.whole;
     this->fraction = other.fraction;
     return *this;
 }


// **************************
int BigReal::size(){
     return fraction.getSize() + whole.getSize();
 }


// **************************
char BigReal::sign(){
    return whole.getSign();
}


// **************************
//bool operator< (BigReal anotherReal){
//    if()
//}

ostream& operator << (ostream& out, BigReal num){
    out << num.whole << "." << num.fraction;
    return  out;
}
