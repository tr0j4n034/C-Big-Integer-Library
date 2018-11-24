//
//  random_factory.h
//  C++ Big Integer Library
//
//  Created by Mahmud on 11/2/18.
//  Copyright © 2018 Mahmud. All rights reserved.
//

#ifndef random_factory_h
#define random_factory_h


#endif /* random_factory_h */

#include <ctime>
#include <random>

const int DEFAULT_INTEGER_LENGTH = 20;
const int PRIME_LIKELIHOOD_TRIALS = 10;

class Random {
private:
    int range;
    std::random_device rd;
    std::mt19937 generator;
    std::uniform_int_distribution<int> dist;
public:
    Random() {}
    Random(int __range):
        range(__range), generator(rd()),
        dist(std::uniform_int_distribution<>(0, __range - 1)){
            generator.seed(unsigned(time((NULL))));
    }
    int generate() {
        return dist(generator);
    }
    int generate(int low, int high) {
        return low + dist(generator) % (high - low + 1);
    }
    Integer generateI(int length = DEFAULT_INTEGER_LENGTH) {
        string digits = "";
        for (int i = 0; i < length; i ++) {
            int __d = generate();
            if (!i && !__d) {
                --i;
                continue;
            }
            digits += char(__d + '0');
        }
        return Integer(digits, (generate() & 1) ? +1 : -1);
    }
    Integer generateIUpTo(Integer top) {
        string result = "";
        for (int i = 0; i < (int)top.getValue().size(); i ++) {
            int __d = generate(0, 9);
            if (__d > 0 || !result.empty()) {
                result += (char)(__d + '0');
            } if (cmp(result, top.getValue()) == +1) {
                result.pop_back();
            }
        }
        if (result.empty()) {
            result = "0";
        }
        return result;
    }
    Integer generateI(Integer low, Integer high) {
        return low + generateIUpTo(high - low + 1);
    }
    Integer generateLikelyPrimeI(Integer low, Integer high) { // change later, may be out of bounds
        Integer I = low + generateIUpTo(high - low + 1);
        for (int trials = 0; trials < PRIME_LIKELIHOOD_TRIALS; trials ++) {
            int lastDigit = generate(0, 3);
            if (lastDigit == 0) {
                I.setLastDigit(1);
            } else if (lastDigit == 1) {
                I.setLastDigit(3);
            } else if (lastDigit == 2) {
                I.setLastDigit(7);
            } else {
                I.setLastDigit(9);
            }
            if (digitalRoot(I) % 3 != 0) {
                return I;
            }
        }
        return I;
    }
};
