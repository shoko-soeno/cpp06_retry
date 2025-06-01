#include "ScalarConverter.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <literal>" << std::endl;
        return 1;
    }
    ScalarConverter::convert(argv[1]);
    return 0;
}

// int main(void)
// {
//     const char* test_literals[] = {
//         "0",
//         "nan",     // double special
//         "42.0f",    // float special
//         "abc",      // invalid
//         "42abc",    // invalid
//         "1.2.3",    // invalid
//         "",         // invalid
//         " ",        // space
//         "127",      // int, char nondisplayable
//         "-2147483648", // int min
//         "999999999999", // int overflow but lower than double/float max
//         "-4.2f",    // float
//         "nanf",     // float special
//         "+inff",    // float special
//         "-inff",    // float special
//         "-4.2",     // double
//         "nan",      // double special
//         "+inf",     // double special
//         "-inf",     // double special
//         "3.4e+38f", // float max
//         "3.4e+40f",  // float overflow but lower than double max
//         "1e400", // double max
//         "-0.0",      //negative zero
//     };

//     for (size_t i = 0; i < sizeof(test_literals)/sizeof(test_literals[0]); ++i) {
//         std::cout << "==== Test: \"" << test_literals[i] << "\" ====" << std::endl;
//         ScalarConverter::convert(test_literals[i]);
//         std::cout << std::endl;
//     }
//     return 0;
// }
