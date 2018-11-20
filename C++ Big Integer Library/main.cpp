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
    Random r(5);
    cout << r.generate(1, 10) << endl;
    Integer lowBound = powFastI(2, 100);
    
    cout << generatePrime(lowBound) << endl;
    
    return 0;
}
