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
#include <vector>
#include <algorithm>
#include <type_traits>

#include "operators.h"


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
    template<typename T, // for integer values
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
        // TODO
    }
    void operator = (int arg) {
        value = to_string(arg);
    }
    void operator = (long long arg) {
        value = to_string(arg);
    }
    string toString(){ // string converter
        if (this -> isZero()) {
            return "0";
        } else {
            return (sign == +1 ? "" : "-") + value;
        }
    }
    int getSign() { // sign of the integer
        return sign;
    }
    string getValue() { // value part of the integer (without sign)
        return value;
    }
    int length() { // length of the value part in decimal
        return (int)value.size();
    }
    int digitAt(int position) { // digit at specific position
        if (position < this->length()) {
            return value[position] - '0';
        } else {
            return -1;
        }
    }
    void negate() { // negate the integer
        if (!this->isZero()) {
            sign *= -1;
        }
    }
    void setLastDigit(int digit) { // modify last digit
        value.back() = (char)(digit + '0');
    }
    bool operator == (Integer arg) { // equal operator
        return (sign == arg.getSign() || isZero()) && value == arg.getValue();
    }
    bool operator == (int arg) { // equal operator for int
        return *this == Integer(arg);
    }
    bool operator != (Integer arg) { // not equal operator
        return !(*this == arg);
    }
    bool operator != (int arg) { // not equal operator for int
        return *this != Integer(arg);
    }
    bool operator < (Integer arg) { // less than operator
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
    bool operator < (int arg) { // lass than operator for int
        return *this < Integer(arg);
    }
    bool operator <= (Integer arg) { // less or equal operator
        return *this == arg || *this < arg;
    }
    bool operator <= (int arg) { // less or equal operator for int
        return *this <= Integer(arg);
    }
    bool operator > (Integer arg) { // greater operator
        return !(*this <= arg);
    }
    bool operator > (int arg) { // greator operator for int
        return *this > Integer(arg);
    }
    bool operator >= (Integer arg) { // greater or equal operator
        return !(*this < arg);
    }
    bool operator >= (int arg) { // greator or equal operator for int
        return *this >= Integer(arg);
    }
    void operator = (Integer arg) { // set to new value
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
    operator int(){ // to int converter
        int v = 0;
        for (char &digit: value) {
            v = (v << 3) + (v << 1) + digit - '0';
        } // correct if the value fits into int range
        return v * sign;
    }
    Integer operator -() { // getting negative of the integer
        return Integer(value, sign == -1 ? +1 : sign);
    }
    Integer abs() { // absolute value
        return Integer(value, sign == -1 ? 1 : sign);
    }
    Integer operator + (Integer addend) { // addition of two integers
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
        return Integer(result, result[0] == '0' ? 0 : __sign);
    }
    Integer operator + (int addend) { // addition of two integers
        return *this + Integer(addend);
    }
    void operator += (Integer addend) { // addition operator
        *this = *this + addend;
    }
    void operator += (int addend) { // addition operator
        *this = *this + Integer(addend);
    }
    Integer operator - (Integer subtrahend) { // subtraction of two integers
        string result = "0";
        int __sign = sign;
        if (isZero()) {
            result = subtrahend.getValue();
            __sign = -subtrahend.getSign();
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
        return Integer(result, result[0] == '0' ? 0 : __sign);
    }
    Integer operator - (int subtrahend) { // subtraction of two integers
        return *this - Integer(subtrahend);
    }
    void operator -= (Integer subtrahend) { // subtraction operator
        *this = *this - subtrahend;
    }
    void operator -= (int subtrahend) { // subtraction operator
        *this = *this - Integer(subtrahend);
    }
    Integer operator * (Integer multiplier) { // multiplication of two integers
        if (this->isZero() || multiplier.isZero()) {
            return Integer("0");
        } else {
            string result = multiply(value, multiplier.getValue());
            return Integer(result, (sign == multiplier.getSign() ? +1 : -1));
        }
    }
    Integer operator * (int multiplier) { // multiplication of two integers
        return *this * Integer(multiplier);
    }
    void operator *= (Integer multiplier) { // multiplication operator
        *this = *this * multiplier;
    }
    void operator *= (int multiplier) { // multiplication operator
        *this = *this * Integer(multiplier);
    }
    Integer operator / (Integer divisor) { // integer division of two integers
        if (divisor.isZero()) {
            throw runtime_error("Division by zero");
        } else if (isZero()) {
            return Integer("0");
        } else {
            return Integer(divide(value, divisor.getValue()), (sign == divisor.getSign() ? +1 : -1));
        }
    }
    Integer operator / (int divisor) {
        return *this / Integer(divisor);
    }
    void operator /= (Integer divisor) { // integer division operator
        *this = *this / divisor;
    }
    void operator /= (int divisor) { // integer division operator
        *this = *this / Integer(divisor);
    }
    Integer operator % (Integer dividend) { // modulo of two integers
        if (dividend.isZero()) {
            throw runtime_error("Division by zero");
        } else if (isZero()) {
            return Integer("0");
        } else {
            return Integer(modulo(value, dividend.getValue()), (sign == dividend.getSign() ? +1 : -1));
        }
    }
    Integer operator % (int dividend) { // modulo of two integers
        return *this % Integer(dividend);
    }
    void operator %= (Integer dividend) { // modulo operator
        *this = *this % dividend;
    }
    void operator %= (int dividend) { // modulo operator
        *this = *this % Integer(dividend);
    }
    Integer& operator ++ () { // preincrement operator
        *this += 1;
        return *this;
    }
    Integer operator ++ (int) { // postincrement operator
        Integer result = Integer(*this);
        ++ (*this);
        return result;
    }
    Integer operator -- () {
        *this -= 1;
        return *this;
    }
    Integer operator -- (int) {
        Integer result = Integer(*this);
        -- (*this);
        return result;
    }
    Integer operator >> (int shift) { // right shift
        Integer I = abs();
        bool negative = (sign == -1);
        while (shift) {
            if (negative && I.isOdd()) {
                I += 1;
            }
            I = I / 2;
            shift --;
        }
        return I;
    }
    void operator >>= (int shift) { // right shift operator
        *this = *this >> shift;
    }
    Integer operator << (int shift) { // left shift
        Integer I = *this;
        while (shift > 0) {
            I = I + I;
            shift --;
        }
        return I;
    }
    void operator <<= (int shift) { // left shift operator
        if (isNegative()) {
            // maybe changed to a silent warning
            throw runtime_error("shifting negative number.");
        }
        *this = *this << shift;
    }
    
    // BITWISE operators section
    // Please, modify if negative numbers will be used in these operations
    
    Integer operator !() { // NOT operator
        return Integer(isZero() ? 1 : 0);
    }
    Integer operator & (Integer operand) { // AND of two integers
        Integer a = Integer(*this);
        Integer b = Integer(operand);
        Integer result = 0, power = 1;
        while (a > 0 && b > 0) {
            if (a.isOdd() && b.isOdd()) {
                result += power;
            }
            a >>= 1;
            b >>= 1;
            power <<= 1;
        }
        return result;
    }
    void operator &= (Integer operand) { // AND operator
        *this = *this & operand;
    }
    Integer operator | (Integer operand) { // OR of two integers
        Integer a = Integer(*this);
        Integer b = Integer(operand);
        Integer result = 0, power = 1;
        while (a > 0 || b > 0) {
            if (a.isOdd() || b.isOdd()) {
                result += power;
            }
            a >>= 1;
            b >>= 1;
            power <<= 1;
        }
        return result;
    }
    void operator |= (Integer operand) { // OR operator
        *this = *this | operand;
    }
    Integer operator ^ (Integer operand) { // XOR of two integers
        Integer a = Integer(*this);
        Integer b = Integer(operand);
        Integer result = 0, power = 1;
        while (a > 0 || b > 0) {
            if (a.isOdd() != b.isOdd()) {
                result += power;
            }
            a >>= 1;
            b >>= 1;
            power <<= 1;
        }
        return result;
    }
    void operator ^= (Integer operand) { // XOR operator
        *this = *this ^ operand;
    }
    int getLowestSetBit() { // getting lowest setbit (=1)
        int bit = 0;
        Integer I = abs();
        while (I > 0) {
            if (I.isOdd()) {
                break;
            }
            I >>= 1;
            bit ++;
        }
        return bit;
    }
    bool isKthBitSet(int k) { // checking if k-th bit is set (=1)
        Integer v = abs();
        while (k --) {
            v >>= 1;
        }
        return v.isOdd();
    }
    int setBitCount() { // counting the set (=1) bits
        int ones = 0;
        Integer v = abs();
        while (v > 0) {
            if (v.isOdd()) {
                ones ++;
            }
            v >>= 1;
        }
        return ones;
    }
    Integer setKthBit(int k) { // setting k-th bit to 1
        if (isKthBitSet(k)) {
            return Integer(*this);
        } else {
            return Integer(*this + (Integer("1") << k));
        }
    }
    Integer clearKthBit(int k) { // resetting k-th bit
        if (!isKthBitSet(k)) {
            return Integer(*this);
        } else {
            return Integer(*this - (Integer("1") << k));
        }
    }
    Integer flipKthBit(int k) { // flipping k-th bit
        if (isKthBitSet(k)) {
            return Integer(*this - (Integer("1") << k));
        } else {
            return Integer(*this + (Integer("1") << k));
        }
    }
    vector<char> toBitVector() { // for positive integers so far
        vector<char> bits;
        Integer v = value;
        while (v > 0) {
            bits.push_back((char)(v.isOdd() + '0'));
            v >>= 1;
        }
        reverse(bits.begin(), bits.end());
        return bits;
    }
    string toBitString() { // converting to binary bit string
        string bitString = "";
        Integer v = value;
        while (v > 0) {
            bitString += (char)(v.isOdd() + '0');
            v >>= 1;
        }
        reverse(bitString.begin(), bitString.end());
        return bitString;
    }
    string toHexString() { // converting to hex string
        string hexString = "";
        Integer v = value;
        while (v > 0) {
            int digit = int(v % 16);
            hexString += (char)(digit < 10 ? digit + '0' : digit + 'A' - 10);
            v >>= 4;
        }
        reverse(hexString.begin(), hexString.end());
        return hexString;
    }
    bool isZero() { // checking equality to zero
        return (!value.empty() && value[0] == '0') || sign == 0;
    }
    bool isPositive() { // checking positiveness
        return sign == +1;
    }
    bool isNegative() { // checking negativeness
        return sign == -1;
    }
    bool isEven() { // checking evenness
        return !value.empty() && (!((int)value.back() & 1));
    }
    bool isOdd() { // checking oddness
        return !value.empty() && ((int)value.back() & 1);
    }
    int decimalValueLength() { // length in decimal notation
        return (int)value.size();
    }
};

std::ostream &operator << (std::ostream &os, Integer i) {
    return os << i.toString();
}

Integer binaryToInteger(string binary) { // binary to integer converter
    Integer result = 0;
    Integer power = 1;
    for (int i = (int)binary.size() - 1; i >= 0; i --) {
        if (binary[i] == '1') {
            result += power;
        } else if (binary[i] != '0'){
            // maybe changed to a warning
            throw runtime_error("not a binary string is fed");
        }
        power <<= 1;
    }
    return result;
}
