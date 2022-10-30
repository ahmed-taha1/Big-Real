#include <bits/stdc++.h>
#include "BigReal.h"
#include "BigDecimalInt.h"
using namespace std;

int main() {
    system("cls");
    BigReal h("12.007600");
    BigReal h2("12.07600");
    cout << h << " " << h2 << '\n';
    cout <<"equal : " << (h==h2) <<'\n';
    cout <<"greater than : " << (h>h2) <<'\n';
    cout <<"less than : " << (h<h2)  << '\n';
    cout << '\n';

    BigReal h3("12.76000000000000");
    BigReal h4("12.7600");
    cout << h3 << " " << h4 << '\n';
    cout <<"equal : " << (h3==h4) <<'\n';
    cout <<"greater than : " << (h3>h4) <<'\n';
    cout <<"less than : " << (h3<h4)  << '\n';
    cout << '\n';
    return 0;
}
