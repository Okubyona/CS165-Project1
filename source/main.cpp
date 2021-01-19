
#include <iostream>
#include <algorithm>
#include <string>
#include <thread>   // Will be using threading to speed up iterations.
#include <time.h>   // Used to track the amount of iterations per second
#include "md5.h"

// Converts all characters in the given string to hexadecimal in the
// form "\xed\x7a\x53\x7\x58\x8e\x49\xed\x3a..." depending on the input string
std::string convertMD5(std::string intermediateZero);
// Compute the alternate sum, that is: md5(password + salt + password)
std::string alternateSum(std::string password, std::string salt);
// Compute the Intermediate_0 sum
std::string intermediateZero(std::string magic, std::string password, std::string salt);
// Compute the Intermediate_1000 sum
std::string FinalSum(/*TODO*/);
// Run the MD5 algorithm against all lowercase characters
void bruteForce(/*TODO*/);


// Compute the alternate sum, that is: md5(password + salt + password)
std::string alternateSum(std::string &password, std::string &salt);
// Compute the Intermediate_0 sum
std::string intermediateZero(std::string magic, std::string &password, std::string & salt);
// Compute the Intermediate_1000 sum
std::string FinalSum(/*TODO*/);
// Run the MD5 algorithm against all lowercase characters
void bruteForce(/*TODO*/);


int main() {
    std::string hash, magic, salt;
    // Hash for team32
    hash  = "zS6RayXs77bfZxpHqC1ur0";
    magic = "$1$";
<<<<<<< HEAD
    salt  = "4fTgjp6q";

    std::string alternate = alternateSum("zhgnnd", "hfT7jp2q");
    std::cout << alternate << "\n";

    std::string intermediateZ = intermediateZero(magic, "zhgnnd", "hfT7jp2q");
    std::cout << intermediateZ << "\n";

    std::string converted = convertMD5(intermediateZ);
    //std::cout << converted << "\n";

    // Call at least 13 threads to check all possible 26^6 combinations
    // by calling the bruteForce() function

=======
    salt  = "4fTgjp6q"
    // Call at least 13 threads to check all possible 26^6 combinations
    // by calling the bruteForce() function

>>>>>>> b7b118d57fffc04b8192471880bd95c3bea9212c
    /* TODO */

    return 0;
}

// Compute the alternate sum, that is: md5(password + salt + password)
<<<<<<< HEAD
std::string alternateSum(std::string password, std::string salt) {
    std::string alternateSum = md5(password + salt + password);
    return alternateSum;
}

// Compute the Intermediate_0 sum
std::string intermediateZero(std::string magic, std::string password, std::string salt) {
    // Will contain the Intermediate_0 string
    std::string result = "";
    std::string alternate = alternateSum(password, salt);
=======
std::string alternateSum(std::string &password, std::string &salt) {
    return md5(password + salt + password);
}

// Compute the Intermediate_0 sum
std::string intermediateZero(std::string magic, std::string &password, std::string salt) {
    // Will contain the Intermediate_0 string
    std::string result = "";
    std::string alternateSum = alternateSum(password, salt);
>>>>>>> b7b118d57fffc04b8192471880bd95c3bea9212c
    int length = password.size();

    // Completes steps 1 through 3
    result = password + magic + salt;

    // Step 4
    // length(password) bytes of the alternateSum, repeated as necessary
    while (length > 0) {
<<<<<<< HEAD
        result = result + alternate.substr(0, std::min(alternate.size(), password.size()));
        length -= alternate.size();
=======
        result = result + alternateSum.substr(0, std::min(alternateSum.size(), password.size()))
        length -= alternateSum.size();
>>>>>>> b7b118d57fffc04b8192471880bd95c3bea9212c
    }

    // Step 5
    // For each bit in length(password), from low to high and stopping after the
    // most significant set bit
    for (unsigned int i = password.size(); i != 0; i >>= 1) {
        // if the bit is set, append a NULL byte
        if (i & 1) {
            result += '\x00';
        }
        // if it's unset, append the first byte of the password
        else {
            result += password[0];
        }
    }
<<<<<<< HEAD
    // Returns the intermediateZero string where each character is its hex escape
    return md5(result);
}

// Converts all characters in the given string to hexadecimal in the
// form "\xed\x7a\x53\x7\x58\x8e\x49\xed\x3a..." depending on the input string
std::string convertMD5(std::string intermediateZero) {
    std::string convert = "";
    std::string hexChar;
    char hexCharArr[hexChar.size() + 1];
    int asciiChar;

    for (int i = 0; i < intermediateZero.size() - 1; i += 2) {
        // grabs hex code from intermediateZero
        hexChar = intermediateZero.substr(i, 2);
        strcpy(hexCharArr, hexChar.c_str());
        // grabs decimal ascii number from hex value in hexCharArr
        asciiChar = (int)(strtol(hexCharArr, NULL, 16));
        convert += asciiChar;
        // output statement to check if conversion process is correct
        // printf("%02x", asciiChar);
    }

    return convert;
=======

    return md5(result);
>>>>>>> b7b118d57fffc04b8192471880bd95c3bea9212c
}
