//
//  main.cpp
//  C++ Big Integer Library
//
//  Created by Mahmud on 10/28/18.
//  Copyright © 2018 Mahmud. All rights reserved.
//

#include <iostream>

#include "integer.h"

using namespace std;

int main(int argc, const char * argv[]) {
//    Integer a = -5;
//    Integer b = +16;
//    cout << a << " " << b << endl;
//    cout << a.getSign() << " " << a.getValue() << endl;
//    cout << b.getSign() << " " << b.getValue() << endl;
//    cout << a / b << endl;
//    cout << b / a << endl;
//
//    Integer c = a / b;
//    cout << a.getSign() << " " << a.getValue() << endl;
//    cout << b.getSign() << " " << b.getValue() << endl;
//    cout << c.getSign() << " " << c.getValue() << endl;
//
    
    Integer a = 13;
    cout << toBinary(a) << endl;
    Integer b = 1;
    cout << ((b >> 1) > 0) << endl;
    
    cout << !(1) << endl;

    return 0;
}
