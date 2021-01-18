
#include <iostream>
#include <algorithm>
#include <string>
#include <thread>   // Will be using threading to speed up iterations.
#include <time.h>   // Used to track the amount of iterations per second
#include "md5.h"


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
    salt  = "4fTgjp6q"
    // Call at least 13 threads to check all possible 26^6 combinations
    // by calling the bruteForce() function

    /* TODO */

    return 0;
}

// Compute the alternate sum, that is: md5(password + salt + password)
std::string alternateSum(std::string &password, std::string &salt) {
    return md5(password + salt + password);
}

// Compute the Intermediate_0 sum
std::string intermediateZero(std::string magic, std::string &password, std::string salt) {
    // Will contain the Intermediate_0 string
    std::string result = "";
    std::string alternateSum = alternateSum(password, salt);
    int length = password.size();

    // Completes steps 1 through 3
    result = password + magic + salt;

    // Step 4
    // length(password) bytes of the alternateSum, repeated as necessary
    while (length > 0) {
        result = result + alternateSum.substr(0, std::min(alternateSum.size(), password.size()))
        length -= alternateSum.size();
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

    return md5(result);
}
