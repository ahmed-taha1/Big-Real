//#include <bits/stdc++.h>
#include "BigDecimalInt.h"
#include <regex>
using namespace std;


// ******************************** String Constructor **************************************
BigDecimalInt::BigDecimalInt(const string& num) {
    // validating (sign,digits ,etc....)
    validate(num);
}


// ***************************** Copy Constructor ***********************************************
BigDecimalInt::BigDecimalInt(const BigDecimalInt &other) {

    // extracting  digits
    for (int i = 0; i < other.size(); ++i) {
        this->digits.push_back(other.digits[i]);
    }
    //setting sign
    setSign(other.getSign());
}

// ******************************** Int Constructor **************************************
BigDecimalInt::BigDecimalInt(const long long int &num) {
    int temp=num;
    if(num==0) {
        digits.push_back('0');
        setSign('+');
    }
    else if(num<0) {
        setSign('-');
        temp*=-1;
    }
    else
        setSign('+');
    while(temp) {
        int digit=temp%10;
        temp/=10;
        digits.push_front(digit + '0');
    }
}


// ******************************* Assignment "=" Operator  ***************************************
BigDecimalInt& BigDecimalInt::operator=(const BigDecimalInt &num) {
    if(this == &num)
        return *this;

    this->digits.clear(); // clear the object
    this->setSign(num.getSign()); // copy the sign

    // copy the digits
    for (const char& i : num.digits) {
        digits.push_back(i);
    }
    return *this;
}


// ******************************* Size Getter Function ************************************************
int BigDecimalInt::size() const {
    // return deque's size
    return  digits.size();
}


// ******************************* Sign Getter Function *************************************************
char BigDecimalInt::getSign() const {
    return  sign;
}


// ******************************** Sign Setter Function ************************************************
void BigDecimalInt::setSign(const char& sign) {
    if(!isdigit(sign)) {
        this->sign = sign;
    }
    else
        this->sign = '+';
}



// ******************************** Addition "+" Operator ****************************
BigDecimalInt BigDecimalInt::operator+(const BigDecimalInt &num)const {

    // if they not have the same signs change the operate to subtract
    // (1 + -2) == (1 - 2)
    if(this->getSign() != num.getSign()){
        BigDecimalInt temp(num);
        temp.setSign(this-> getSign());
        return *this-temp;
    }


    BigDecimalInt result;
    result.digits.clear();
    result.setSign(this->getSign());

    BigDecimalInt LHS = *this;
    BigDecimalInt RHS = num;

    // add leading zeros to facilitate Addition
    matchSize(LHS,RHS);

    int carry = 0 ;
    for (int i = LHS.size() - 1; i >= 0 ; --i) {
        int lhsDigit = LHS.digits[i] - '0';
        int rhsDigit = RHS.digits[i] - '0';
        int sum = lhsDigit + rhsDigit + carry;

        // if the sum of two digits will make overflow("greater than 9") we add carry to the next digit's sum
        if(sum>9) {
            carry = 1;
            // take the last digit to add it to the object
            sum%=10;
        }
        else
            carry = 0;
        result.digits.push_front(sum + '0');
    }
    if(carry)
        result.digits.push_front(carry + '0');

    return  result;
}



// ***************************** Subtraction "-" Operator *****************************************
BigDecimalInt BigDecimalInt::operator-(const BigDecimalInt &other)const{
    /* call add operator if they have non equal signs and set their add sign to the first number
       (-3 - 2) = -(3 + 2) || (3 - -6) = (3 + 6)
    */
    if(this->getSign() != other.getSign()) {
        BigDecimalInt temp(other);
        temp.setSign(this-> getSign());
        return *this+temp;
    }

    BigDecimalInt result,bigger,smaller;

    bigger.setSign('+');
    result.digits.clear();


    smaller = *this;
    char smallerSign = this->getSign(); // save old sign
    smaller.setSign('+');

    bigger = other;
    if(bigger.getSign()=='+') // flip sign (1 - +6) == (1 - 6)
        bigger.setSign('-');
    else
        bigger.setSign('+'); // (1 - -6) == (1 + 6)

    char biggerSign = bigger.getSign(); // save old sign
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
        return BigDecimalInt("0");
    }


    //add leading zeros to facilitate subtraction
    matchSize(smaller,bigger);


    // subtraction
    for (int i = bigger.size() - 1 ; i >= 0; i--) {
        // if the bigger's number digit less than the smaller's number digit borrow from it's left neighbor one
        if(bigger.digits[i] < smaller.digits[i]) {
            bigger.digits[i-1]--;
            bigger.digits[i] += 10;
        }
        // subtract them and store the result in the object
        result.digits.push_front('0' + bigger.digits[i] - smaller.digits[i]);
    }
    return result;
}



// ******************************* Less Than "<" Operator ************************************************
bool BigDecimalInt::operator< (const BigDecimalInt& anotherDec)const{
    // if the first number have a negative sign and the second number have positive sign function will return true
    if(this->getSign()=='-'&&anotherDec.getSign()=='+')
        return true;
    // if the first number have a positive sign and the second number have negative sign function will return false
    if(this->getSign()=='+'&&anotherDec.getSign()=='-')
        return false;

    BigDecimalInt LHS = *this;
    BigDecimalInt RHS = anotherDec;

    /* if they both have negative signs we will take their abs and compare them with less than operate
       (-2 < -3) ? --> (2 > 3) ? "no" // (-5 < -3) ? --> (5 > 3) ? "yes"
    */
    if(this->getSign()=='-' && anotherDec.getSign()=='-') {
        LHS.setSign('+');
        RHS.setSign('+');
        return (LHS>RHS);
    }

    // add leading zeros to facilitate comparison
    matchSize(LHS,RHS);

    // if they are equal in digits number we will compare each digit from the left to the right
    for(long long i = 0; i < RHS.size(); i++){
        if(RHS.digits[i] > LHS.digits[i])
            return true;
        else if(RHS.digits[i] < LHS.digits[i])
            return false;
    }
    return false;
}


// ****************************** Greater Than ">" Operator ************************************************
bool BigDecimalInt::operator> (const BigDecimalInt& anotherDec)const{

    // if the first number have a negative sign and the second number have positive sign function will return false
    if(this->getSign()=='-' && anotherDec.getSign()=='+')
        return false;
    // if the first number have a positive sign and the second number have negative sign function will return true
    if(this->getSign()=='+' && anotherDec.getSign()=='-')
        return true;



    BigDecimalInt LHS = *this;
    BigDecimalInt RHS = anotherDec;

    /* if they both have negative signs we will take their abs and compare them with less than operate
       (-2 > -3) ? --> (2 < 3) ? "yes" // (-5 > -3) ? --> (5 < 3) ? "no"
    */
    if(this->getSign()=='-' && anotherDec.getSign()=='-') {
        LHS.setSign('+');
        RHS.setSign('+');
        return (LHS<RHS);
    }


    // add leading zeros to facilitate comparison
    matchSize(LHS,RHS);


    // if they are equal in digits number we will compare each digit from the left to the right
    for(long long i = 0; i < anotherDec.size(); i++){
        if(LHS.digits[i] > RHS.digits[i])
            return true;
        else if(LHS.digits[i] < RHS.digits[i])
            return false;
    }

    // if they are equal
    return false;
}


// ****************************** Equality "==" Operator****************************************************
bool BigDecimalInt::operator==(const BigDecimalInt& anotherDec) const {
    // if the first not greater than the second and not less than the second that means that the two numbers are equal
    return (!(*this < anotherDec) && !(*this > anotherDec));
}


// ****************************** Output Operator "<<" Overloading  **************************************

ostream& operator<<(ostream& out,const BigDecimalInt& bigint) {
    // if the object negative from check it's sign output the sign first
    if(bigint.getSign()=='-')
        out << '-';
    // then output the digits
    for (char i : bigint.digits) {
        out << i ;
    }
    return out;
}



// ****************************** Validating number **************************************************

void BigDecimalInt::validate(const string &num){
    bool valid = true;
    bool leadingZero = true;
    // check if sign exist only once or not and check if the string contain numbers only using regex
    if (! regex_match(num, regex("(\\+|-)?\\d+") ) )
        valid = false;
        // push back the numbers into the object and skip zeros in the left
    else {
        if(isdigit(num[0]) && num[0] != '0') {
            digits.push_back(num[0]);
            leadingZero = false;
        }
        for (int i = 1; i <num.size() ; ++i) {
            if(num[i] == '0' && leadingZero)
                continue;
            leadingZero = false;
            digits.push_back(num[i]);
        }
    }
    // if the string not valid set the object with deafult value zero
    if(!valid || leadingZero) {
        digits.push_back('0');
        setSign('+');
    }
        // set number's sign if valid using setSign function
    else
        setSign(num[0]);
}


//****************************** Add leading zeros to facilitate Operations *******************************
void BigDecimalInt::matchSize(BigDecimalInt& LHS,BigDecimalInt& RHS){
    long long diff = abs(RHS.size() - LHS.size() );
    for(long long i = 0; i < diff; i++){
        // add leading zeros to the shorter number to facilitate operations
        if(RHS.size() > LHS.size()){
            LHS.digits.push_front('0');
        }
        else{
            RHS.digits.push_front('0');
        }
    }
}
//**********************************************************************************************************
