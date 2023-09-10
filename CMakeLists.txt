cmake_minimum_required(VERSION 3.15)

project(osprng)

add_library(osprng INTERFACE)

target_include_directories(osprng INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(OS::PRNG ALIAS osprng)

option(PRNG_USE_OPENSSL "Use OpenSSL PRNG if available" OFF)

option(PRNG_COMPILE_TEST "Compile test program" OFF)

if (PRNG_COMPILE_TEST)
    add_subdirectory("Test")
endif()

if(${PRNG_USE_OPENSSL})
    find_package(OpenSSL QUIET)

    if (${OpenSSL_FOUND})
        target_compile_definitions(osprng INTERFACE PRNG_OPENSSL)
        
        message(STATUS "PRNG: Using OpenSSL RAND_bytes")
        
        return()
    else()
        message(STATUS "PRNG: OpenSSL not found, trying with OS PRNG's")
    endif()
endif()

if (WIN32)
    target_compile_definitions(osprng INTERFACE PRNG_WINDOWS)

    message(STATUS "PRNG: Using BCryptGenRandom")
elseif(UNIX)
    option(PRNG_USE_URANDOM "Use Cryptographically Secure Unix entropy source /dev/urandom, else /dev/random" ON)
    
    target_compile_definitions(osprng INTERFACE PRNG_UNIX)
    
    if (${PRNG_USE_URANDOM})
        target_compile_definitions(osprng INTERFACE PRNG_UNIX_URANDOM=1)

        message(STATUS "PRNG: Using /dev/urandom")
    else()
        target_compile_definitions(osprng INTERFACE PRNG_UNIX_URANDOM=0)

        message(STATUS "PRNG: Using /dev/random")
    endif()
else()
    target_compile_definitions(osprng INTERFACE PRNG_STD)

    message(WARNING "PRNG: Your OS isn't supported, using C++ STD version, this isn't a Cryptographically Secure source so please send an issue ASAP to add support to your OS")
endif()