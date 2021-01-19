
#include <iostream>
#include <algorithm>
#include <string>
#include <thread>   // Will be using threading to speed up iterations.
#include <chrono>   // Used to track the amount of iterations per second
#include "md5.h"

// Converts all characters in the given string to hexadecimal in the
// form "\xed\x7a\x53\x7\x58\x8e\x49\xed\x3a..." depending on the input string
std::string convertMD5(std::string intermediateZero);
// Compute the alternate sum, that is: md5(password + salt + password)
std::string alternateSum(std::string password, std::string salt);
// Compute the Intermediate_0
std::string intermediateZero(std::string magic, std::string password, std::string salt);
// Compute the Intermediate_1000
std::string loop(std::string intermediateZero, std::string password, std::string salt);
// Compute the final intermediate
std::string finalize(std::string finalSum);
// Encode the byte string with a special base64-type encoding
std::string toBase64(std::string hash, unsigned int x, unsigned int y, unsigned int z, int n);
// Overload encoding function for last byte
std::string toBase64(std::string hash, unsigned int x, unsigned int n);
// Main function to control hash generation
std::string hashGen(std::string magic, std::string password, std::string salt);
// Run the MD5 algorithm against all lowercase characters until the target hash is found
void bruteForce(std::string magic, std::string salt, std::string targetHash, int begin,
    int end);

const std::string base64 = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

int main() {
    std::string targetHash, magic, salt;
    // Hash for team32
    targetHash = "zS6RayXs77bfZxpHqC1ur0";
    magic = "$1$";
    salt  = "4fTgjp6q";

    // Call at least 13 threads to check all possible 26^6 combinations
    // ASCII lowercase range: 97 - 122
    // by calling the bruteForce() function

    std::string testHash = intermediateZero(magic, "zhgnnd", "hfT7jp2q");
    testHash = loop(testHash, "zhgnnd", "hfT7jp2q");
    testHash = finalize(testHash);

    std::cout << testHash << std::endl;
    std::cout << "cringe" << std::endl;

    return 0;
}

// Converts all characters in the given string to hexadecimal in the
// form "\xed\x7a\x53\x7\x58\x8e\x49\xed\x3a..."
std::string convertMD5(std::string intermediateZero) {
    std::string convert = "";
    std::string hexVal;
    int asciiVal;

    for (unsigned int i = 0; i < intermediateZero.size() - 1; i += 2) {
        // grabs 2 digit hex from string
        hexVal = intermediateZero.substr(i, 2);
        char hexArray[hexVal.size() + 1];
        strcpy(hexArray, hexVal.c_str());
        // grabs decimal ascii number from hex value in hexCharArr
        asciiVal = (int)(strtol(hexArray, NULL, 16));
        unsigned char character = (unsigned char)(asciiVal);
        convert += character;
        // output statement to check if conversion process is correct
        // std::cout << convert << "\n";
        //printf("%02x", asciiVal);
    }
    //std::cout << std::endl;

    return convert;
}

// Compute the alternate sum, that is: md5(password + salt + password)
std::string alternateSum(std::string password, std::string salt) {
    return md5(password + salt + password);
}

// Compute the Intermediate_0 sum
std::string intermediateZero(std::string magic, std::string password, std::string salt) {
    // Will contain the Intermediate_0 string
    std::string intermediate = "";
    std::string alternate = alternateSum(password, salt);
    int length = password.size();
    // Convert alternate to byte string
    alternate = convertMD5(alternate);

    // Completes steps 1 through 3
    intermediate = password + magic + salt;

    // Step 4
    // length(password) bytes of the alternateSum, repeated as necessary
    while (length > 0) {
        intermediate += alternate.substr(0, std::min(16, length));
        length -= 16;
    }


    // Step 5
    // For each bit in length(password), from low to high and stopping after the
    // most significant set bit
    for (unsigned int i = password.size(); i != 0; i >>= 1) {
        // if the bit is set, append a NULL byte
        if (i & 1) {
            intermediate += '\x00';
        }
        // if it's unset, append the first byte of the password
        else {
            intermediate += password[0];
        }
    }
    intermediate = md5(intermediate);
    intermediate = convertMD5(intermediate);

    return intermediate;
}

// Compute Intermediate_1000
std::string loop(std::string intermediateZero, std::string password, std::string salt) {
    std::string temp = "";

    for (unsigned int i = 0; i < 1000; ++i) {
        temp = "";
        if (i & 1) { temp += password; }
        else { temp += intermediateZero; }

        if (i % 3 != 0) { temp += salt; }

        if (i % 7 != 0) { temp += password; }

        if (i & 1) { temp += intermediateZero; }
        else { temp += password; }

        intermediateZero = md5(temp);
        intermediateZero = convertMD5(intermediateZero);
    }
    return intermediateZero;
}

// Compute the final intermediate
std::string finalize(std::string finalSum) {
    std::string finalFinalSum = "";
    finalFinalSum += toBase64(finalSum, 0, 6, 12, 4);
    finalFinalSum += toBase64(finalSum, 1, 7, 13, 4);
    finalFinalSum += toBase64(finalSum, 2, 8, 14, 4);
    finalFinalSum += toBase64(finalSum, 3, 9, 15, 4);
    finalFinalSum += toBase64(finalSum, 4, 10, 5, 4);
    finalFinalSum += toBase64(finalSum, 11, 2);

    return finalFinalSum;
}

std::string toBase64(std::string hash, unsigned int x, unsigned int y, unsigned int z, int n) {
    unsigned int h = ((unsigned char)hash[x] << 16) | ((unsigned char)hash[y] << 8) | ((unsigned char)hash[z]);
    std::string ret;


    for (int i = 1; i <= 4; ++i) {
        ret += base64[(h & 0x3f)];
        h >>= 6;
    }

    return ret;
}

std::string toBase64(std::string hash, unsigned int x, unsigned int n) {
    unsigned int h = (unsigned char)hash[x];
    std::string ret = "";

    for (int i = 1; i <= 2; ++i) {
        ret += base64[(h & 0x3f)];
        h >>= 6;
    }

    return ret;
}
