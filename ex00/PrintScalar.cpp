#include "ScalarConverter.h"

void ScalarConverter::printScalarValues(const ScalarValues& values)
{
    if (values.isCharConvertible)
    {
        if (std::isprint(values.c))
            std::cout << "char: '" << values.c << "'" << std::endl;
        else
            std::cout << "char: Non displayable" << std::endl;
    } else {
        std::cout << "char: impossible" << std::endl;
    }

    if (values.isIntConvertible)
        std::cout << "int: " << values.i << std::endl;
    else
        std::cout << "int: impossible" << std::endl;
    
    if (values.isFloatConvertible) {
        std::cout << "float: " << values.f;
        if (values.f == static_cast<int>(values.f))
            std::cout << values.f << ".0f" << std::endl;
        else
            std::cout << values.f << "f" << std::endl;
    } else {
        std::cout << "float: impossible" << std::endl;
    }

    if (values.isDoubleConvertible) {
        std::cout << "double: " << values.d;
        if (values.d == static_cast<int>(values.d))
            std::cout << values.d << ".0" << std::endl;
        else
            std::cout << values.d << std::endl;
    } else {
        std::cout << " impossible" << std::endl;
    }
}
/*
if the value has no decimal part,
    print it as a float/double with .0
*/
