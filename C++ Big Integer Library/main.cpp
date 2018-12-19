//
//  main.cpp
//  C++ Big Integer Library
//
//  Created by Mahmud on 10/28/18.
//  Copyright © 2018 Mahmud. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <vector>
#include <ctime>

#include "integer.h"
#include "extra_integer_factory.h"
#include "random_factory.h"
#include "prime_factory.h"

#include "rsa_mini.h"

using namespace std;

int main(int argc, const char * argv[]) {
    Integer a = 96;
    cout << isFermatPrime(a) << endl;
    cout << smallPrimesCheck(a) << endl;
    cout << isEulerPrime(a) << endl;
    cout << isMillerRabinPrime(a) << endl;
    
    
    return 0;
}
