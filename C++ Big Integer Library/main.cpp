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
    
    Integer ff = Integer("83012452418357729491");
    Integer ss = Integer("10000000207");
    Integer r = ff % ss;
    cout << r << endl;
    cout << r.getSign() << " " << r.getValue() << endl;
    
//    clock_t t = clock();
//    cout << powFastI(2, int(2639)) << endl;
//    clock_t t2 = clock();
//    cout << 1. * (t2 - t) / CLOCKS_PER_SEC << endl;
//    return 0;
    
    //Random r(5);
    //cout << r.generate(1, 10) << endl;
    //cout << generatePrime() << endl;
    
    for (int i = 1; i < 50; i ++) {
        long long a;
        cin >> a;
        cout << isPrime(a) << endl;
    }
    
    
    
    return 0;
}
