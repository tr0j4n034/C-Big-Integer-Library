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
const int BLOCK_SIZE = 64;

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
    Integer getPublicKey() {
        return publicKey;
    }
    Integer* getPrimeFactors() {
        Integer* factors = new Integer[2];
        factors[0] = P;
        factors[1] = Q;
        return factors;
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
    Integer encrypt(Integer message) {
        return modPowerI(message, publicKey, N);
    }
    Integer decrypt(Integer cipher) {
        return modPowerI(cipher, privateKey, N);
    }
    Integer sign(Integer message) {
        return modPowerI(message, privateKey, N);
    }
    bool verify(Integer original, Integer sent) {
        return original == modPowerI(sent, publicKey, N);
    }
    Integer encryptText(string message) {
        while ((int)message.size() % BLOCK_SIZE) {
            message = "0" + message;
        }
        Integer hash = 0;
        Integer seperator = powFastI(10, 64);
        for (int block = 0; block < (int)message.size(); block += BLOCK_SIZE) {
            string binaryBlock = "";
            for (int i = block; i < block + BLOCK_SIZE / 8; i ++) {
                binaryBlock += Integer((int)message[i]).toBitString();
            }
            hash = hash * seperator + encrypt(binaryToInteger(binaryBlock));
        }
        return hash;
    }
    string decryptText(Integer cipher) {
        string result = "";
        Integer seperator = powFastI(10, 64);
        vector<string> blocks;
        while (cipher > 0) {
            Integer part = cipher % seperator;
            string originalMessage = decrypt(part).toBitString();
            string current = "";
            for (int i = 0; i < (int)originalMessage.size(); i += BLOCK_SIZE / 8) {
                int letter = 0;
                for (int j = i; j < i + BLOCK_SIZE / 8; j ++) {
                    letter = (letter << 3) + (letter << 1) + originalMessage[i] - '0';
                }
                current += (char)(letter);
            }
            blocks.push_back(current);
        }
        reverse(blocks.begin(), blocks.end());
        for (auto part: blocks) {
            result += part;
        }
        return result;
    }
};
