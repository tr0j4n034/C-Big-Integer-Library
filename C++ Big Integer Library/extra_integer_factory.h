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

using namespace std;

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
Integer sqrtI(Integer I) {
    if (I < 0) {
        // may be changed to silent warning
        throw runtime_error("negative number fed into sqrt function");
    }
    // TODO
    // newton-raphson or binary search will be implemented
    
    Integer low = 0, high = powI(10, ((int)I.decimalValueLength() >> 1) + 1);
    Integer middle, best_approximation = Integer(I);
    while (low <= high) {
        middle = (low + high) >> 1;
        cout << low << " " << high << " " << middle << " " << middle * middle << endl;
        
        if (middle * middle <= I) {
            best_approximation = Integer(middle);
            low = middle + 1;
        } else {
            high = middle - 1;
        }
    }
    return best_approximation;
}
