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
    cout << generatePrime() << endl;
    
    for (int i = 2; i < 50; i ++) {
        int a;
        cin >> a;
        cout << isPrime(a) << endl;
    }
    
    
    
    return 0;
}
