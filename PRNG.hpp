#pragma once
#ifdef PRNG_STD
    #include <algorithm>
    #include <random>
#elif defined(PRNG_OPENSSL)
    #include <openssl/rand.h>
#elif defined(PRNG_UNIX)
    #include <cstdio>

    #ifndef PRNG_UNIX_URANDOM
        #define PRNG_UNIX_URANDOM 1
    #endif

    #if !PRNG_UNIX_URANDOM
        #define PRNG_UNIX_RANDOM_DEVICE "/dev/random"
    #else
        #define PRNG_UNIX_RANDOM_DEVICE "/dev/urandom"
    #endif

    #define OpenRandomDevice() FILE* randomdv = fopen(PRNG_UNIX_RANDOM_DEVICE, "rb")

    #define ReadRandomDevice(to, size, quantity) fread(reinterpret_cast<void*>(to), size, quantity, randomdv)

    #define CloseRandomDevice() fclose(randomdv)

#elif defined(PRNG_WINDOWS)
    #include <windows.h>
    #include <bcrypt.h>
    #pragma comment(lib, "bcrypt")
#else
    #error PRNG Mode not selected
#endif

#include <type_traits>
#include <vector>

class PRNG {
public:
    static std::vector<unsigned char> genBytes(size_t size) {
        std::vector<unsigned char> rBytes(size);
        #ifdef PRNG_STD
        std::random_device rd;
        std::mt19937_64 mt(rd());
        std::uniform_int_distribution<int> uid(0, 255);

        std::generate_n(rBytes.begin(), size, [&]() {
            return static_cast<unsigned char>(uid(mt));
        });
        #elif defined(PRNG_OPENSSL)
        RAND_bytes(&rBytes[0], static_cast<int>(size));
        #elif defined(PRNG_UNIX)
        OpenRandomDevice();
        ReadRandomDevice(reinterpret_cast<void*>(&rBytes[0]), sizeof(unsigned char), size);
        CloseRandomDevice();
        #elif defined(PRNG_WINDOWS)
        BCryptGenRandom(NULL, &rBytes[0], size, BCRYPT_USE_SYSTEM_PREFERRED_RNG);
        #endif
        return rBytes;
    }

    template <typename T, typename = std::enable_if<std::is_integral_v<T>>>
    static T genInteger() {
        T myInteger;
        #ifdef PRNG_STD
        std::random_device rd;
        std::mt19937_64 mt(rd());
        std::uniform_int_distribution<T> uid;

        myInteger = uid(mt);
        #elif defined(PRNG_OPENSSL)
        RAND_bytes(reinterpret_cast<unsigned char*>(&myInteger), sizeof(T));
        #elif defined(PRNG_UNIX)
        OpenRandomDevice();
        ReadRandomDevice(reinterpret_cast<void*>(&myInteger), sizeof(T), 1);
        CloseRandomDevice();
        #elif defined(PRNG_WINDOWS)
        BCryptGenRandom(NULL, reinterpret_cast<unsigned char*>(&myInteger), sizeof(T), BCRYPT_USE_SYSTEM_PREFERRED_RNG);
        #endif
        return myInteger;
    }
};
