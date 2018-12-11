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
    Integer phiN; // can be changed to Carmichael totient
public:
    Integer N; // N = P * Q
    Integer publicKey; // ~prime
    
    RSA() {
        
    }
    RSA(Integer p, Integer q) {
        P = p;
        Q = q;
        N = P * Q;
        phiN = (p - 1) * (q - 1);
        Random rng(0x12345);
        publicKey = rng.generateCoprime(phiN, phiN);
        privateKey = modularInverse(publicKey, phiN);
    }
    Integer getPrivateKey() {
        return privateKey;
    }
    string toString() {
        string data = "";
        data += "N = " + N.toString() + "\n";
        data += "P = " + P.toString() + "\n";
        data += "Q = " + Q.toString() + "\n";
        data += "Euler phi of N = " + phiN.toString() + "\n";
        data += "public key = " + publicKey.toString() + "\n";
        data += "private key = " + privateKey.toString() + "\n";
        string validity = (isValid() ? "" : "not ");
        data += "Scheme is " + validity + "valid.\n";
        return data;
    }
    void getinfo(std::ostream &os) {
        os << "N = " << N.toString() << "\n";
        os << "P = " + P.toString() + "\n";
        os << "Q = " + Q.toString() + "\n";
        os << "Euler phi of N = " + phiN.toString() + "\n";
        os << "public key = " + publicKey.toString() + "\n";
        os << "private key = " + privateKey.toString() + "\n";
        os << "Scheme is " << (isValid() ? "" : "not ") << "valid." << "\n";
    }
    void generateKeys(Integer low = MODULO_LOW_VALUE) {
        P = generateMillerRabinPrime(low);
        Q = generateMillerRabinPrime(low << 2);
        N = publicKey * privateKey;
        phiN = (publicKey - 1) * (privateKey - 1);
        Random rng(0x12345);
        publicKey = rng.generateCoprime(phiN, phiN - 1);
        privateKey = modularInverse(publicKey, phiN);
    }
    bool isValid() {
        return P * Q == N
            && (P - 1) * (Q - 1) == phiN
            && gcdI(publicKey, privateKey) == 1
            && publicKey * privateKey % phiN == 1;
    }
};
