//
//  Number.h
//  C++ Big Integer Library
//
//  Created by Mahmud on 10/28/18.
//  Copyright © 2018 Mahmud. All rights reserved.
//

#ifndef integer_h
#define integer_h


#endif /* Number_h */

#include <cstring>
#include <type_traits>

#include "operators.h"
#include "extra_integer_factory.h"

using namespace std;

class Integer {
    int sign;
    string value;
    
public:
    Integer() {
        
    }
    Integer(string arg) {
        if (arg[0] == '0') {
            sign = 0;
            value = "0";
        } else if (arg[0] == '-'){
            sign = -1;
            value = arg.substr(1);
        } else {
            sign = +1;
            value = arg;
        }
    }
    Integer(string arg, int __sign) {
        value = arg;
        sign = __sign;
    }
    template<typename T, // for real values
    typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    Integer(T arg) {
        if (arg == 0) {
            sign = 0;
            value = "0";
        } else if (arg < 0) {
            sign = -1;
            value = to_string(-arg);
        } else {
            sign = +1;
            value = to_string(arg);
        }
    }
    Integer(int arg) {
        if (arg == 0) {
            sign = 0;
            value = "0";
        } else if (arg < 0) {
            sign = -1;
            value = to_string(-arg);
        } else {
            sign = +1;
            value = to_string(arg);
        }
    }

    ~Integer() {
        
    }
    string toString(){
        if (this -> isZero()) {
            return "0";
        } else {
            return (sign == +1 ? "" : "-") + value;
        }
    }
    int getSign() {
        return sign;
    }
    string getValue() {
        return value;
    }
    int length() {
        return (int)value.size();
    }
    int digitAt(int position) {
        if (position < this->length()) {
            return value[position] - '0';
        } else {
            return -1;
        }
    }
    bool isZero() {
        return (!value.empty() && value[0] == '0') || sign == 0;
    }
    void negate() {
        if (!this->isZero()) {
            sign *= -1;
        }
    }
    bool operator == (Integer arg) {
        return sign == arg.getSign() && value == arg.getValue();
    }
    bool operator != (Integer arg) {
        return !(*this == arg);
    }
    bool operator < (Integer arg) {
        if (sign != arg.getSign()) {
            return sign < arg.getSign();
        }
        int l = this->length();
        int lArgv = arg.length();
        if (l < lArgv) {
            return sign == 1;
        } else if (l > lArgv) {
            return sign == -1;
        }
        for (int i = 0; i < l; i ++) {
            if (value[i] - '0' != arg.digitAt(i)) {
                return value[i] - '0' < arg.digitAt(i) && sign == 1;
            }
        }
        return false;
    }
    bool operator <= (Integer arg) {
        return *this == arg || *this < arg;
    }
    bool operator > (Integer arg) {
        return !(*this <= arg);
    }
    bool operator >= (Integer arg) {
        return !(*this < arg);
    }
    void operator = (Integer arg) {
        sign = arg.getSign();
        value = arg.getValue();
    }
    template <class T>
    void operator = (T arg) {
        if (arg == 0) {
            sign = 0;
            value = "0";
        } else if (arg < 0){
            sign = -1;
            value = to_string(-arg);
        } else {
            sign = +1;
            value = to_string(arg);
        }
    }
    Integer abs() {
        return Integer(value, sign == -1 ? 1 : sign);
    }
    Integer operator + (Integer addend) {
        string result = "0";
        int __sign = sign;
        if (isZero()) {
            result = addend.getValue();
            __sign = addend.getSign();
        } else if (addend.isZero()) {
            result = value;
        } else if (sign == addend.getSign()) {
            result = add(value, addend.getValue());
        } else if (cmp(value, addend.getValue()) == +1){
            result = subtract(value, addend.getValue());
        } else {
            __sign *= -1;
            result = subtract(addend.getValue(), value);
        }
        return Integer(result, __sign);
    }
    void operator += (Integer addend) {
        *this = *this + addend;
    }
    Integer operator - (Integer subtrahend) {
        string result = "0";
        int __sign = sign;
        if (isZero()) {
            result = subtrahend.getValue();
            sign = -subtrahend.getSign();
        } else if (subtrahend.isZero()) {
            result = value;
        } else if (sign == subtrahend.getSign()) {
            if (value == subtrahend.getValue()) {
                result = "0";
            } else if (cmp(value, subtrahend.getValue()) == -1) {
                result = subtract(subtrahend.getValue(), value);
                __sign *= -1;
            } else {
                result = subtract(value, subtrahend.getValue());
            }
        } else {
            result = add(value, subtrahend.getValue());
        }
        return Integer(result, __sign);
    }
    Integer operator * (Integer multiplier) {
        if (this->isZero() || multiplier.isZero()) {
            return Integer("0");
        } else {
            string result = multiply(value, multiplier.getValue());
            return Integer(result, (multiplier.getSign() ? +1 : -1));
        }
    }
    void operator *= (Integer multiplier) {
        *this = *this * multiplier;
    }
    Integer operator / (Integer divisor) {
        if (divisor.isZero()) {
            throw runtime_error("Division by zero");
        } else if (isZero()) {
            return Integer("0");
        } else {
            return Integer(divide(value, divisor.getValue()), (sign == divisor.getSign() ? +1 : -1));
        }
        return *this;
    }
    void operator /= (Integer divisor) {
        *this = *this / divisor;
    }
    Integer operator >> (int shift) {
        Integer I = abs();
        bool negative = (sign == -1);
        while (shift) {
            if (negative && I.isOdd()) {
                I += 1;
            }
            cout << I.value << endl;
            I = I / 2;
            shift --;
        }
        return I;
    }
    void operator >>= (int shift) {
        *this = *this >> shift;
    }
    Integer operator << (int shift) {
        Integer I = *this;
        while (shift > 0) {
            I = I + I;
            shift --;
        }
        return I;
    }
    void operator <<= (int shift) {
        if (isNegative()) {
            throw runtime_error("shifting negative number.");
        }
        *this = *this << shift;
    }
    
    // BITWISE operators section
    
    Integer operator & (Integer operand) {
        // TODO
        return *this;
    }
    void operator &= (Integer operand) {
        // TODO
    }
    Integer operator | (Integer operand) {
        // TODO
        return *this;
    }
    void operator |= (Integer operand) {
        // TODO
    }
    Integer operator ^ (Integer operand) {
        // TODO
        return *this;
    }
    void operator ^= (Integer operand) {
        // TODO
    }
    
    
    // EXTRA
    bool isPositive() {
        return sign == +1;
    }
    bool isNegative() {
        return sign == -1;
    }
    bool isEven() {
        return !value.empty() && (!((int)value.back() & 1));
    }
    bool isOdd() {
        return !value.empty() && ((int)value.back() & 1);
    }
};

std::ostream &operator << (std::ostream &os, Integer i) {
    return os << i.toString();
}



/*
 MATH FUNCTIONS
 ...
 */

Integer abs(Integer i) {
    return Integer(i.getValue(), i.getSign() == -1 ? 1 : i.getSign());
}
Integer pow(Integer i, int exponent) {
    // TODO
    return i;
}
