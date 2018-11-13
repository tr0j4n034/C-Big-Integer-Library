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

const int LIMIT = 1 << 7;
const int EXTRA_FERMAT_TRIALS = 2;

const int basePrimes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
const int baseSize = 15;

int _log(int length) {
    int l = 0;
    while (length) {
        ++l;
        length >>= 1;
    }
    return l;
}
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
    for (int i = 0; i < baseSize; i ++) {
        if (I == basePrimes[i]) {
            return true;
        } else if (I % basePrimes[i] == 0) {
            return false;
        }
    }
    for (int i = 0; i < baseSize; i ++) {
        if (FermatWitness(basePrimes[i], I)) {
            return false;
        }
    }
    Random rng(0xabc);
    for (int i = 0; i < EXTRA_FERMAT_TRIALS; i ++) {
        int base = rng.generate(19, 0xfff);
        if (FermatWitness(base, I)) {
            return false;
        }
    }
    return true;
}
Integer generatePrime(Integer low_bound = (1 << 10)) { // to slow
    Random rng(0xabc);
    Integer result = -1;
    while (result == -1) {
        result = rng.generateI(low_bound, low_bound << 3);
        if (!isPrime(result)) {
            result = -1;
        }
    }
    return result;
}
