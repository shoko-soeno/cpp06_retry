#include "ScalarConverter.h"

// int main(int argc, char **argv)
// {
//     if (argc != 2)
//     {
//         std::cout << "Usage: " << argv[0] << " <literal>" << std::endl;
//         return 1;
//     }
//     ScalarConverter::convert(argv[1]);
//     return 0;
// }

int main(void)
{
    const char* test_literals[] = {
        "a",        // char
        "Z",        // char
        "0",        // char/int
        "42",       // int
        "-42",      // int
        "2147483647", // int max
        "-2147483648", // int min
        "4.2f",     // float
        "-4.2f",    // float
        "nanf",     // float special
        "+inff",    // float special
        "-inff",    // float special
        "4.2",      // double
        "-4.2",     // double
        "nan",      // double special
        "+inf",     // double special
        "-inf",     // double special
        "abc",      // invalid
        "42abc",    // invalid
        "1.2.3",    // invalid
        "",         // invalid
        " ",        // invalid
        "127",      // int (char max)
        "128",      // int (overflow char)
        "256",      // int (overflow char)
        "!",         // char
        "3.4e+35f", // float max
        "1e400", // double max
        "-0.0",      //negative zero
    };

    for (size_t i = 0; i < sizeof(test_literals)/sizeof(test_literals[0]); ++i) {
        std::cout << "==== Test: \"" << test_literals[i] << "\" ====" << std::endl;
        ScalarConverter::convert(test_literals[i]);
        std::cout << std::endl;
    }
    return 0;
}
