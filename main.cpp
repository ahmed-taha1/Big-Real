//#include <bits/stdc++.h>
#include "BigReal.h"
#include "BigDecimalInt.h"
using namespace std;
/*
Names : Ahmed mohamed taha, adham tarek, ismail magdy
ID   : 20210033 - 20210051 - 20210069
task : group task 1 - assignment 1
last date modified : 10/20/2022
Description : this program is doing some operations in a big decimal integers which that normal data types can't store
*/

#include <bits/stdc++.h>
#include "BigReal.h"
using namespace std;

int main(){
    start:

    string s1, s2;
    // inputs window
     system("CLS");
     cout << "please enter the first number : ";
     cin >> s1;
     BigReal num1(s1);

     cout << "please enter the second number : ";
     cin >> s2;
     BigReal num2(s2);


     // calculations' window
     system("CLS");
     cout << "num 1 : " << num1 << "\n";
     cout << "num 2 : " << num2 << "\n";

     BigReal num3 = num1 + num2;
     cout << "num 1 + num 2 = " << num3 << '\n';

    BigReal num4 = num1 - num2;
     cout << "num1 - num 2 = " << num4 << '\n';

     if(num1 == num2)
         cout << "num1 = num2\n";
     else if(num1 > num2)
         cout << "num1 > num2\n";
     else
         cout << "num 1 < num2\n";

     // repeat window
     choose:
     cout << "do you want to exit ? (y/n) : ";
     char c;     cin >> c;

     if(c == 'y')
         exit(0);
     else if(c == 'n')
         goto start;
     else{
         cout << "invalid input please try again!\n";
         goto choose;
     }
}
