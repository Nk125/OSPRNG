## Operating System - Pseudo Random Number Generator

This is a header-only library that adds support to common OS PRNGs and OpenSSL

Supports:
* Windows
* Unix
* Anything compatible with OpenSSL 1.1
* C++11 (`<random>` header)

## Options

Inside the .hpp file, the options are the next:

* `PRNG_USE_STD`

    Use the `<random>` header described before as PRNG, only enable it if any of the other PRNGs supplied aren't available on the system

* `PRNG_USE_OPENSSL`

    Use `RAND_bytes()` function as PRNG

* `PRNG_UNIX`

    Use Unix provided PRNG, but also this have a sub-option:

    * `PRNG_UNIX_URANDOM`

        If set to true /dev/urandom is used as PRNG, else fallbacks to /dev/random

        Should be /dev/urandom preferred than /dev/random unless concrete and rare cases that you'll know you need /dev/random
    
        If you don't know what you're doing set it to true
    
* `PRNG_WINDOWS`

    Use `BCryptGenRandom()` function as PRNG

Now with CMake Options:

* `PRNG_USE_OPENSSL` (Default: false)

    Enable OpenSSL to be used as PRNG, described above, if OpenSSL isn't found in the system, search for the OS provided PRNG

* `PRNG_USE_URANDOM` (Only for **Unix**, Default: true)

    If set to true, enable /dev/urandom, else use /dev/random

* `PRNG_COMPILE_TEST` (Default: false)

    Compiles the test that shows an example byte vector of 32 bytes and a table of integer values got from the PRNG

## How to use

* In CMake

    Simply download the lib and then link like this:

    ```cmake
    include(FetchContent)

    FetchContent_Declare(
        Nk125PRNG
        GIT_REPOSITORY "https://github.com/Nk125/OSPRNG"
        GIT_TAG "main"
    )

    FetchContent_MakeAvailable(Nk125PRNG)

    target_link_libraries(myexe PRIVATE osprng)

    # OR

    target_link_libraries(myexe PRIVATE OS::PRNG)
    ```

    In your cpp file:

    ```cpp
    // Ready to use
    #include <PRNG.hpp>
    ```

* Standalone header

    Start by setting the options above (OS to be working on) and then just

    ```cpp
    // Assuming you're on Unix
    #define PRNG_UNIX
    #define PRNG_UNIX_URANDOM true
    // or in Windows
    #define PRNG_WINDOWS
    // or you want to use OpenSSL
    #define PRNG_OPENSSL
    // or you want to use <random> header
    #define PRNG_STD

    // Assuming you added to include path
    #include <PRNG.hpp>
    // or
    #include "PRNG.hpp"
    ```
