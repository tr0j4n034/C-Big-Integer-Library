//
//  main.cpp
//  C++ Big Integer Library
//
//  Created by Mahmud on 10/28/18.
//  Copyright © 2018 Mahmud. All rights reserved.
//

#include <iostream>
#include <vector>

#include "integer.h"
#include "extra_integer_factory.h"
#include "random_factory.h"
#include "prime_factory.h"

using namespace std;

int main(int argc, const char * argv[]) {
    Integer a = Integer(31);
    cout << a << endl;
    vector<char> v = a.toBitArray();
    for (char i: v) {
        cout << i;
    }
    cout << endl;
    
    return 0;
}
