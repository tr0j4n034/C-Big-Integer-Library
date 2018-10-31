//
//  string_factory.h
//  C++ Big Integer Library
//
//  Created by Mahmud on 10/29/18.
//  Copyright © 2018 Mahmud. All rights reserved.
//

#ifndef string_factory_h
#define string_factory_h


#endif /* string_factory_h */

#include <cstring>

using namespace std;

const int SHORT_INT_RANGE = 1 << 27; // for faster division operations

int cmp(string &a, string b) {
    int la = (int)a.size();
    int lb = (int)b.size();
    if (la != lb) {
        return la < lb ? -1 : +1;
    }
    for (int i = 0; i < la; i ++) {
        if (a[i] != b[i]) {
            return a[i] < b[i] ? -1 : +1;
        }
    }
    return 0;
}
void insertTrailingZeros(string &a, int z) {
    for (int i = 0; i < z; i ++) {
        a += '0';
    }
}
