#include <iomanip>
#include <iostream>
#include <PRNG.hpp>
#include <type_traits>

std::ostream& operator<<(std::ostream& out, std::vector<unsigned char> uc) {
    std::ios::fmtflags f = out.flags();

    out << std::hex << std::nouppercase;

    for (unsigned char u : uc) out << std::setw(2) << std::setfill('0') << static_cast<int>(u);

    out.flags(f);

    return out;
}

template <class T>
constexpr std::string_view type_name() {
    using namespace std;
#ifdef __clang__
    string_view p = __PRETTY_FUNCTION__;
    return string_view(p.data() + 34, p.size() - 34 - 1);
#elif defined(__GNUC__)
    string_view p = __PRETTY_FUNCTION__;
#  if __cplusplus < 201402
    return string_view(p.data() + 36, p.size() - 36 - 1);
#  else
    return string_view(p.data() + 49, p.find(';', 49) - 49);
#  endif
#elif defined(_MSC_VER)
    string_view p = __FUNCSIG__;
    return string_view(p.data() + 84, p.size() - 84 - 7);
#endif
}

template<typename T, typename = std::enable_if<std::is_integral_v<T>>>
void printInt(T Int) {
    std::cout << std::left << std::setw(24) << type_name<T>() << std::right << std::setw(24) << Int << "\n";
}

int main() {
    std::vector<unsigned char> randomBytes = PRNG::genBytes(32);

    int rInt = PRNG::genInteger<int>();
    unsigned int rUInt = PRNG::genInteger<unsigned int>();

    short rShort = PRNG::genInteger<short>();
    unsigned short rUShort = PRNG::genInteger<unsigned short>();

    long rLong = PRNG::genInteger<long>();
    unsigned long rULong = PRNG::genInteger<unsigned long>();

    long long rLLong = PRNG::genInteger<long long>();
    unsigned long long rULLong = PRNG::genInteger<unsigned long long>();

    std::cout << "Random bytes: " << randomBytes << "\nRandom Integers:\n\n" << std::left << std::setfill(' ') << std::setw(24) << "Type" << std::right << std::setw(24) << "Value";

    std::cout << "\n";

    printInt(rInt);
    printInt(rUInt);

    printInt(rShort);
    printInt(rUShort);

    printInt(rLong);
    printInt(rULong);

    printInt(rLLong);
    printInt(rULLong);
}