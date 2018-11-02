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
};
