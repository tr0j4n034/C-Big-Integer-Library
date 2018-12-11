//
//  rsa_mini.h
//  C++ Big Integer Library
//
//  Created by Mahmud on 12/11/18.
//  Copyright © 2018 Mahmud. All rights reserved.
//

#ifndef rsa_mini_h
#define rsa_mini_h


#endif /* rsa_mini_h */

#include <cstring>

const Integer MODULO_LOW_VALUE = powFastI(2, 100);

class RSA {
    Integer P, Q; // ~prime
    Integer privateKey;
    Integer phiN;
public:
    Integer N; // N = P * Q
    Integer publicKey; // ~prime
    
    RSA() {
        
    }
    RSA(Integer __private, Integer __public) {
        privateKey = __private;
        publicKey = __public;
        N = privateKey * publicKey;
        phiN = (publicKey - 1) * (privateKey - 1);
    }
    Integer getPrivateKey() {
        return privateKey;
    }
    string toString() {
        string data = "";
        data += "N = " + N.toString() + "\n";
        data += "public key = " + publicKey.toString() + "\n";
        data += "private key = " + privateKey.toString() + "\n";
        return data;
    }
    void getinfo(std::ostream &os) {
        os << "N = " << N.toString() << "\n";
        os << "public key = " + publicKey.toString() + "\n";
        os << "private key = " + privateKey.toString() + "\n";
    }
    void generateKeys(Integer low = MODULO_LOW_VALUE) {
        P = generateMillerRabinPrime(low);
        Q = generateMillerRabinPrime(low << 2);
        N = publicKey * privateKey;
        phiN = (publicKey - 1) * (privateKey - 1);
    }
    bool isValid() {
        return publicKey * privateKey == N
            &&
        (publicKey - 1) * (privateKey - 1) == phiN;
    }
};
