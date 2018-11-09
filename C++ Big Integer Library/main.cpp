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
#include "random_factory.h"

using namespace std;

int main(int argc, const char * argv[]) {    
    Random r(10);
    cout << r.generate() << endl;
    cout << r.generateI(10) << endl;
    cout << r.generateI(1239218939, 891239123938921) << endl;
    cout << r.generateIUpTo(1000) << endl;
    
    return 0;
}
