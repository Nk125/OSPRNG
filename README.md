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

* `PRNG_USE_OPENSSL`

    Enable OpenSSL to be used as PRNG, described above, if OpenSSL isn't found in the system, search for the OS provided PRNG

* `PRNG_COMPILE_TEST`

    Compiles the test that shows an example byte vector of 32 bytes and a table of integer values got from the PRNG