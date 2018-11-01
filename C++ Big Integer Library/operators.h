//
//  operators.h
//  C++ Big Integer Library
//
//  Created by Mahmud on 10/28/18.
//  Copyright © 2018 Mahmud. All rights reserved.
//

#ifndef operators_h
#define operators_h


#endif /* operators_h */

#include "string_factory.h"

#include <cstring>

using namespace std;

string add(string a, string b) { // addition of two numbers in linear time
    string sum = "";
    int i = (int)a.size() - 1;
    int j = (int)b.size() - 1;
    int r = 0;
    while (i >= 0 || j >= 0) {
        int state = r;
        if (i >= 0) state += a[i] - '0';
        if (j >= 0) state += b[j] - '0';
        if (state > 9) {
            state -= 10;
            r = 1;
        } else {
            r = 0;
        }
        i --;
        j --;
        sum += (char)(state + '0');
    }
    if (r > 0) {
        sum += (char)(r + '0');
    }
    while ((int)sum.size() > 1 && sum.back() == '0') {
        sum.pop_back();
    }
    reverse(sum.begin(), sum.end());
    return sum;
}
string subtract(string a, string b) { // assuming a >= b, subtraction in linear time
    string difference = "";
    int i = (int)a.size() - 1;
    int j = (int)b.size() - 1;
    int r = 0;
    while (i >= 0) {
        int state = a[i] - '0' - r;
        if (j >= 0) {
            state -= b[j] - '0';
        }
        if (state < 0) {
            state += 10;
            r = 1;
        } else {
            r = 0;
        }
        i --;
        j --;
        difference += (char)(state + '0');
    }
    while ((int)difference.size() > 1 && difference.back() == '0') {
        difference.pop_back();
    }
    reverse(difference.begin(), difference.end());
    return difference;
}
void split(string &a, string &l, string &r) {
    int length = (int)a.size();
    int half = length >> 1;
    l = a.substr(0, half);
    r = a.substr(half);
}
void normalize(string &a, string &b) { // making the lengths equal to 2's power
    int la = (int)a.size();
    int lb = (int)b.size();
    int to = -1;
    for (int i = 0; ; i ++) {
        if ((1 << i) >= la && (1 << i) >= lb) {
            to = (1 << i);
            break;
        }
    }
    if (la < to) {
        reverse(a.begin(), a.end());
        while (la < to) {
            a += '0';
            la ++;
        }
        reverse(a.begin(), a.end());
    }
    if (lb < to) {
        reverse(b.begin(), b.end());
        while (lb < to) {
            b += '0';
            lb ++;
        }
        reverse(b.begin(), b.end());
    }
    
}
string defaultMultiplier(string a, string b) {
    int aValue = stoi(a);
    int bValue = stoi(b);
    return to_string(aValue * bValue);
}
string karatsuba(string a, string b) {
    if ((int)a.size() < 3) { // if small string lengths achieved, use integer multiplication
        return defaultMultiplier(a, b);
    }
    //    if (isZero(a) || isZero(b)) {
    //        return "0";
    //    }
    normalize(a, b);
    string leftA, rightA;
    string leftB, rightB;
    split(a, leftA, rightA);
    split(b, leftB, rightB);
    string p1 = karatsuba(leftA, leftB);
    string p2 = karatsuba(rightA, rightB);
    string aSum = add(leftA, rightA);
    string bSum = add(leftB, rightB);
    string p3 = karatsuba(aSum, bSum);
    string p4 = subtract(subtract(p3, p1), p2);
    insertTrailingZeros(p1, (int)a.size());
    insertTrailingZeros(p4, (int)a.size() >> 1);
    return add(p1, add(p2, p4));
}
string multiply(string a, string b) {
    //    considering that this code assumes only positive numbers,
    //    you can handle negative numbers as well (even big decimals).
    //    Why not change to FFT?
    return karatsuba(a, b);
}
string _divide(string a, string b) {
    string result = "";
    string current = "";
    for (char ch: a) {
        current += ch;
        if (!result.empty() || cmp(current, b) != -1) {
            int wheel = 0;
            while (cmp(current, b) != -1) {
                wheel ++;
                current = subtract(current, b);
            }
            result += (char)(wheel + '0');
        }
    }
    if (result.empty()) {
        result = "0";
    }
    return result;
}
string divideFast(string a, int b) {
    string result = "";
    int current = 0;
    for (char ch: a) {
        current = (current << 1) + (current << 3) + ch - '0';
        if (!result.empty() || current >= b) {
            result += (char)(current / b + '0');
            current %= b;
        }
    }
    if (result.empty()) {
        result = "0";
    }
    return result;
}
string _modulo(string a, string b) {
    string result = "";
    string current = "";
    for (char ch: a) {
        current += ch;
        if (cmp(current, b) != -1) {
            int wheel = 0;
            while (cmp(current, b) != -1) {
                wheel ++;
                current = subtract(current, b);
            }
            result += (char)(wheel + '0');
        }
    }
    return current;
}
string moduloFast(string a, int b) {
    string result = "";
    int current = 0;
    for (char ch: a) {
        current = (current << 1) + (current << 3) + ch - '0';
        if (current >= b) {
            result += (char)(current / b + '0');
            current %= b;
        }
    }
    return to_string(current);
}
string divide(string a, string b) {
    int bValue = stoi(b);
    if (bValue <= SHORT_INT_RANGE) {
        return divideFast(a, bValue);
    } else {
        return _divide(a, b);
    }
}
string modulo(string a, string b) {
    int bValue = stoi(b);
    if (bValue <= SHORT_INT_RANGE) {
        return moduloFast(a, bValue);
    } else {
        return _modulo(a, b);
    }
}
