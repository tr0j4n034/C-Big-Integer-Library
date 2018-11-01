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

using namespace std;

int main(int argc, const char * argv[]) {
    //cout << sqrtI(Integer(81)) << endl;
    cout << (Integer(20) >> 1) << endl;
    cout << Integer("10") * Integer("10") << endl;
    cout << sqrtI(Integer(81)) << endl;
    
    return 0;
}
