//
//  prime_factory.h
//  C++ Big Integer Library
//
//  Created by Mahmud on 11/2/18.
//  Copyright © 2018 Mahmud. All rights reserved.
//

#ifndef prime_factory_h
#define prime_factory_h


#endif /* prime_factory_h */

using namespace std;

// TODO

// to implement:
// https://en.wikipedia.org/wiki/Baillie-PSW_primality_test

const int LIMIT = 1 << 7;
const int FERMAT_TRIALS = 50;

bool FermatWitness(int base, Integer I) { // base-2 strong primality test
    Integer N = I - 1;
    int s = 0;
    while (N.isEven()) {
        N >>= 1;
        s += 1;
    }
    Integer d = N;
    if (modPowerI(base, d, I) == 1) {
        return false;
    }
    Integer current = powFastI(base, d);
    for (int i = 0; i < s; i ++) {
        if (current % I == (I - 1)) {
            return false;
        }
        current = (current * current) % I;
    }
    return true;
}
bool isPrime(Integer I) {
    if (I < 2) {
        return false;
    }
    for (int i = 2; i < LIMIT; i ++) {
        if (I == i) {
            return true;
        } else if (I % i == 0) {
            return false;
        }
    }
    Random rng(0xabc);
    for (int i = 0; i < FERMAT_TRIALS; i ++) {
        int base = rng.generate(2, 0xfff);
        if (FermatWitness(base, I)) {
            return false;
        }
    }
    return true;
}

