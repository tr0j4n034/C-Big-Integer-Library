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
#include "random_factory.h"
#include "prime_factory.h"

using namespace std;

int main(int argc, const char * argv[]) {
    Integer a = 3;
    Integer b = 17;
    
//    cout << b / a << endl;
//    Integer c = Integer("0") - b / a;
//    cout << c << endl;
    cout << modularInverse(a, b) << endl;
    Integer cc = modularInverse(a, b);
    cout << cc << endl;
    
    return 0;
}
