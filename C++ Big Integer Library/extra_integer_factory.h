//
//  extra_integer_factory.h
//  C++ Big Integer Library
//
//  Created by Mahmud on 10/29/18.
//  Copyright © 2018 Mahmud. All rights reserved.
//

#ifndef extra_integer_factory_h
#define extra_integer_factory_h


#endif /* extra_integer_factory_h */

Integer absI(Integer I) {
    return Integer(I.getValue(), I.getSign() == -1 ? 1 : I.getSign());
}
Integer powI(Integer I, int exponent) {
    Integer result = I;
    while (exponent > 1) {
        result = result * I;
        exponent --;
    }
    return result;
}
Integer powFastI(Integer I, int exponent) {
    Integer result = 1, p = Integer(I);
    while (exponent > 0) {
        if (exponent & 1) {
            result *= p;
        }
        exponent >>= 1;
        p = p * p;
    }
    return result;
}
Integer modPowerI(Integer I, int exponent, Integer modulo) {
    Integer result = 1, p = Integer(I) % modulo;
    while (exponent > 0) {
        if (exponent & 1) {
            result = result * p % modulo;
        }
        exponent >>= 1;
        p = (p * p) % modulo;
    }
    return result;
}
Integer modPowerI(Integer I, Integer exponent, Integer modulo) {
    Integer result = 1, p = Integer(I) % modulo;
    while (exponent > 0) {
        if (exponent.isOdd()) {
            result = result * p % modulo;
        }
        exponent >>= 1;
        p = (p * p) % modulo;
    }
    return result;
}
Integer sqrtI(Integer I) {
    if (I < 0) {
        // may be changed to silent warning
        throw runtime_error("negative number fed into sqrt function");
    }
    // Newton-raphson method can be implemented
    // in place of the following binary search approach.
    
    Integer low = 0, high = powI(10, ((int)I.decimalValueLength() + 1) >> 1);
    Integer middle, best_approximation = Integer(I);
    // the above boundary can be further relaxed
    
    while (low <= high) {
        middle = (low + high) >> 1;
        if (middle * middle <= I) {
            best_approximation = Integer(middle);
            low = middle + 1;
        } else {
            high = middle - 1;
        }
    }
    return best_approximation;
}
Integer cbrtI(Integer I) {
    if (I < 0) {
        // may be changed to silent warning
        throw runtime_error("negative number fed into sqrt function");
    }
    // Newton-raphson method can be implemented
    // in place of the following binary search approach.
    
    Integer low = 0, high = powI(10, ((int)I.decimalValueLength() + 2) / 3);
    Integer middle, best_approximation = Integer(I);
    // the above boundary can be further relaxed
    
    while (low <= high) {
        middle = (low + high) >> 1;
        if (middle * middle * middle <= I) {
            best_approximation = Integer(middle);
            low = middle + 1;
        } else {
            high = middle - 1;
        }
    }
    return best_approximation;
}
Integer gcdI(Integer a, Integer b) {
    Integer posA = a.abs();
    Integer posB = b.abs();
    while (posA > 0) {
        posA %= posB;
        if (posA == 0) {
            return posB;
        }
        posB %= posA;
    }
    return posA;
}
Integer lcmI(Integer a, Integer b) {
    return Integer(a / gcdI(a, b) * b);
}
Integer factorialI(int number) {
    if (number < 0) {
        return 0;
    }
    Integer result = 1;
    for (int i = 2; i <= number; i ++) {
        result *= i;
    }
    return result;
}
int isFactorialI(Integer I) {
    if (I < 1) {
        return -1;
    } else {
        for (int i = 2; ; i ++) {
            if (I == 1) {
                return i - 1;
            } else if (I % i > 0) {
                return -1;
            } I /= i;
        }
    }
    // The early bird catches the worm.
    return -1;
}
Integer* factorialTable(int number) {
    if (number < 0 || number > (1 << 16)) {
        // change if needed
        throw runtime_error("not valid for computation");
    }
    Integer* table = new Integer[number + 1];
    table[0] = 1;
    for (int i = 1; i <= number; i ++) {
        table[i] = table[i - 1] * i;
    }
    return table;
}
