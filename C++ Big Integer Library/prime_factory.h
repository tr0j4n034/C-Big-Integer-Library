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
const int EULER_TRIALS = 1 << 3; // slow
const int MAX_EULER_BASE = 1 << 30;
const int MILLER_RABIN_TRIALS = 10;

const int basePrimes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
const int baseSize = 15;

int _log(int length) { // helper log
    int l = 0;
    while (length) {
        ++l;
        length >>= 1;
    }
    return l;
}
bool FermatWitness(int base, int s, Integer d, Integer I) { // base-2 strong primality test
    Integer current = modPowerI(base, d, I);
    if (current == 1) {
        return false;
    }
    for (int i = 0; i < s; i ++) {
        if (current % I == (I - 1)) {
            return false;
        }
        current = (current * current) % I;
    }
    return true;
}
bool smallPrimesCheck(Integer I) { // I < 53^2
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
    return true;
}
bool isFermatPrime(Integer I, int __extra_trials = EXTRA_FERMAT_TRIALS) {
    if (!smallPrimesCheck(I)) {
        return false;
    }
    Integer N = I - 1;
    int s = 0;
    while (N.isEven()) {
        N >>= 1;
        s += 1;
    }
    Integer d = N;
    for (int i = 0; i < baseSize; i ++) {
        if (FermatWitness(basePrimes[i], s, d, I)) {
            return false;
        }
    }
    Random rng(0xabc);
    for (int i = 0; i < __extra_trials; i ++) {
        int base = rng.generate(19, 0xfff);
        if (FermatWitness(base, s, d, I)) {
            return false;
        }
    }
    return true;
}
bool isFermatPrime(Integer I, int* baseList) {
    Integer N = I - 1;
    int s = 0;
    while (N.isEven()) {
        N >>= 1;
        s += 1;
    }
    Integer d = N;
    for (int i = 0; i < (int)(sizeof(baseList)) / (int)sizeof(baseList[0]); i ++) {
        if (FermatWitness(baseList[i], s, d, I)) {
            return false;
        }
    }
    return true;
}
bool isCompositeByFermatTest(Integer I) {
    return !isFermatPrime(I);
}
Integer generateFermatPrime(Integer low_bound = (1 << 10)) {
    Random rng(0xabc);
    Integer result = -1;
    while (result == -1) {
        result = rng.generateLikelyPrimeI(low_bound, low_bound << 3);
        if (!isFermatPrime(result)) {
            result = -1;
        }
    }
    return result;
}
bool isEulerPrime(Integer I, int __trials = EULER_TRIALS) {
    if (!smallPrimesCheck(I)) {
        return false;
    }
    Random rng(0xabc);
    Integer exponent = Integer(I - 1) >> 1;
    for (int i = 0; i < __trials; i ++) {
        Integer base = rng.generateIUpTo(MAX_EULER_BASE);
        if (I % base == 0) {
            continue;
        }
        Integer halfPower = modPowerI(base, exponent, I);
        if (halfPower != -1 && halfPower != +1) {
            return false;
        }
    }
    return true;
}
bool isEulerPrime(Integer I, int* baseList) {
    Integer N = I - 1;
    int s = 0;
    while (N.isEven()) {
        N >>= 1;
        s += 1;
    }
    Integer exponent = Integer(I - 1) >> 1;
    for (int i = 0; i < (int)(sizeof(baseList)) / (int)sizeof(baseList[0]); i ++) {
        Integer base = baseList[i];
        if (I % base == 0) {
            continue;
        }
        Integer halfPower = modPowerI(base, exponent, I);
        if (halfPower != -1 && halfPower != +1) {
            return false;
        }
    }
    return true;
}
bool isCompositeByEulerTest(Integer I) {
    return !isEulerPrime(I);
}
Integer generateEulerPrime(Integer low_bound = (1 << 10)) { // slow
    Random rng(0xabc);
    Integer result = -1;
    while (result == -1) {
        result = rng.generateLikelyPrimeI(low_bound, low_bound << 3);
        if (!isEulerPrime(result)) {
            result = -1;
        }
    }
    return result;
}
bool isMillerRabinPrime(Integer I, int __trials = MILLER_RABIN_TRIALS, int __base_limit = MAX_EULER_BASE) {
    if (!smallPrimesCheck(I)) {
        return false;
    }
    int k = 0;
    Integer M = I - 1;
    while (M.isEven()) {
        k ++;
        M >>= 1;
    }
    Random rng(0xabc);
    Integer exponent = Integer(I - 1) >> 1;
    for (int i = 0; i < __trials; i ++) {
        Integer base = rng.generateI(3, min(Integer(__base_limit), I - 1));
        Integer b0 = modPowerI(base, M, I);
        Integer b1 = 0;
        for (int j = 0; j <= k; j ++) {
            b1 = b0 * b0 % I;
            if (b1 == 1) {
                break;
            }
            b0 = b1;
        }
        if (b1 != 1 || (b0 != 1 && b0 != I - 1)) {
            return false;
        }
    }
    return true;
}
bool isMillerRabinPrime(Integer I, int* baseList) {
    int k = 0;
    Integer M = I - 1;
    while (M.isEven()) {
        k ++;
        M >>= 1;
    }
    Integer exponent = Integer(I - 1) >> 1;
    for (int i = 0; i < (int)sizeof(baseList) / (int)sizeof(baseList[0]); i ++) {
        Integer base = baseList[i];
        Integer b0 = modPowerI(base, M, I);
        Integer b1 = 0;
        for (int j = 0; j <= k; j ++) {
            b1 = b0 * b0 % I;
            if (b1 == 1) {
                break;
            }
            b0 = b1;
        }
        if (b1 != 1 || (b0 != 1 && b0 != I - 1)) {
            return false;
        }
    }
    return true;
}
bool isCompositeByMillerRabinTest(Integer I) {
    return !isMillerRabinPrime(I);
}
Integer generateMillerRabinPrime(Integer low_bound = (1 << 10)) { // slow
    Random rng(0xabc);
    Integer result = -1;
    while (result == -1) {
        result = rng.generateLikelyPrimeI(low_bound, low_bound << 3);
        if (!isMillerRabinPrime(result)) {
            result = -1;
        }
    }
    return result;
}
Integer nextPrimeviaFermat(Integer I) {
    I += 1;
    while (!isFermatPrime(I)) {
        ++I;
    }
    return I;
}
Integer nextPrimeviaEuler(Integer I) {
    I += 1;
    while (!isEulerPrime(I)) {
        ++I;
    }
    return I;
}
Integer nextPrimeviaMillerRabin(Integer I) {
    I += 1;
    while (!isMillerRabinPrime(I)) {
        ++I;
    }
    return I;
}
