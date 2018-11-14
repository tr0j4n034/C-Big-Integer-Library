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
bool FermatWitness(int base, int s, Integer d, Integer I) { // base-2 strong primality test
    if (modPowerI(base, d, I) == 1) {
        return false;
    }
    cout << "s = " << s << ", d = " << d << endl;
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
    clock_t t0 = clock();
    for (int i = 0; i < baseSize; i ++) {
        if (I == basePrimes[i]) {
            return true;
        } else if (I % basePrimes[i] == 0) {
            return false;
        }
    }
    clock_t t1 = clock();
    Integer N = I - 1;
    int s = 0;
    while (N.isEven()) {
        N >>= 1;
        s += 1;
    }
    Integer d = N;
    cout << "elapsed_1: " << double(t1 - t0) / CLOCKS_PER_SEC << endl;
    for (int i = 0; i < baseSize; i ++) {
        if (FermatWitness(basePrimes[i], s, d, I)) {
            return false;
        }
    }
    clock_t t2 = clock();
    cout << "elapsed_2: " << double(t2 - t1) / CLOCKS_PER_SEC << endl;
    
    Random rng(0xabc);
    for (int i = 0; i < EXTRA_FERMAT_TRIALS; i ++) {
        int base = rng.generate(19, 0xfff);
        if (FermatWitness(base, s, d, I)) {
            return false;
        }
    }
    clock_t t3 = clock();
    cout << "elapsed_3: " << double(t3 - t2) / CLOCKS_PER_SEC << endl;
    return true;
}
Integer generatePrime(Integer low_bound = (1 << 10)) { // to slow
    Random rng(0xabc);
    Integer result = -1;
    while (result == -1) {
        result = rng.generateLikelyPrimeI(low_bound, low_bound << 3);
        cout << "to check: " << result << endl;
        if (!isPrime(result)) {
            result = -1;
        }
    }
    return result;
}
