
#include <iostream>
#include <algorithm>
#include <atomic>   // Will prevent race conditions for throughput tracking
#include <chrono>   // Used to track the amount of iterations per second
#include <cstring>
#include <string>
#include <thread>   // Will be using threading to speed up iterations.
#include <vector>
#include <openssl/md5.h>

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
void bruteForce(std::string magic, std::string salt, std::string targetHash);

const std::string base64 = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
// will be used to determine number of passwords checked per second
std::atomic_int counter(0);

int main() {
    std::string targetHash, magic, salt;
    // Hash for team32
    targetHash = "zS6RayXs77bfZxpHqC1ur0";
    magic = "$1$";
    salt  = "4fTgjp6q";

    // Call at least 13 threads to check all possible 26^6 combinations
    // ASCII lowercase range: 97 - 122
    // by calling the bruteForce() function

    std::vector<std::thread> threads;
    int max_threads = std::thread::hardware_concurrency();

    auto start = std::chrono::high_resolution_clock::now();

    // Makes a low budget thread pool
    for (int i = 0; i < max_threads; ++i) {
        threads.push_back(std::thread(bruteForce, i));
    }

    // Convenient way to join all threads instead of insanity inducing statements
    for (auto &th : threads) {
        th.join();
    }

    // Threads are done, password has been found
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedTime = end - start;

    std::cout << "Elapsed time: " << elapsedTime.count() << " seconds\n";
    std::cout << counter << " passwords were checked\n";
    std::cout << "Average throughput: " << counter / elapsedTime << "passwords / second" << std::endl;

    return 0;
}

void bruteForce(std::string magic, std::string salt, std::string targetHash);