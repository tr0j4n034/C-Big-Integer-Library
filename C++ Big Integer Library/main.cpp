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
    Integer a = -5;
    Integer b = +15;
    cout << a << " " << b << endl;
    cout << a.getSign() << " " << a.getValue() << endl;
    cout << b.getSign() << " " << b.getValue() << endl;
    cout << a + b << endl;
    
    cout << a * b << endl;
    cout << a * -1 << endl;
    cout << b << endl;

    return 0;
}
