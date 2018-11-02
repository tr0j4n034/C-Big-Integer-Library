//
//  main.cpp
//  C++ Big Integer Library
//
//  Created by Mahmud on 10/28/18.
//  Copyright © 2018 Mahmud. All rights reserved.
//

#include <iostream>

#include "integer.h"
#include "extra_integer_factory.h"
#include "prime_factory.h"

using namespace std;

int main(int argc, const char * argv[]) {
    Integer a = 42;
    Integer b = 24;
    cout << a % b << endl;
    cout << gcd(a, b) << endl;
    cout << lcm(a, b) << endl;
    
    return 0;
}
