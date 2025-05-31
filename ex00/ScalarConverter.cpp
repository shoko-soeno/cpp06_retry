#include "ScalarConverter.h"

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter &src)
{
    (void)src;
}
/*
This class should not be instantiated or copied
*/

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &src)
{
    (void)src;
    return *this;
}

ScalarConverter::~ScalarConverter() {}

void ScalarConverter::convert(const std::string &literal)
{
    if (literal.empty())
    {
        std::cout << "Error: Empty input" << std::endl;
        return;
    }
    LiteralType type = detectType(literal);
    switch (type){
        case TYPE_CHAR:
            convertChar(literal);
            break;
        case TYPE_INT:
            convertInt(literal);
            break;
        case TYPE_FLOAT:
            convertFloat(literal);
            break;
        case TYPE_DOUBLE:
            convertDouble(literal);
            break;
        default:
            std::cout << "Error: Invalid input" << std::endl;
    }
}
/*
detect char/int/float/double and convert it to all types
*/
void ScalarConverter::convertChar(const std::string &literal)
{
    ScalarValues result;
    result.isCharConvertible = false;
    result.isIntConvertible = false;
    result.isFloatConvertible = false;
    result.isDoubleConvertible = false;

    char c = literal[0];
    if (literal.length() != 1 || !std::isprint(c))
    {
        result.isCharConvertible = false;
    } else {
        result.isCharConvertible = true;
    }
    result.c = c;
    result.isCharConvertible = true;
    result.i = static_cast<int>(c);
    result.isIntConvertible = true;
    result.f = static_cast<float>(c);
    result.isFloatConvertible = true;
    result.d = static_cast<double>(c);
    result.isDoubleConvertible = true;
    printScalarValues(result);
}

void ScalarConverter::convertInt(const std::string &literal)
{
    ScalarValues result;
    result.isCharConvertible = false;
    result.isIntConvertible = false;
    result.isFloatConvertible = false;
    result.isDoubleConvertible = false;
    long l = strtol(literal.c_str(), NULL, 10);

    if (l > std::numeric_limits<int>::max() || l < std::numeric_limits<int>::min())
    {
        result.isCharConvertible = false;
        result.isIntConvertible = false;
    } else {
        result.isCharConvertible = true;
        result.isIntConvertible = true;
        result.i = static_cast<int>(l);
    }
    result.f = static_cast<float>(l);
    result.isFloatConvertible = true;
    result.d = static_cast<double>(l);
    result.isDoubleConvertible = true;
}

void ScalarConverter::convertFloat(const std::string &literal)
{
    ScalarValues result;
    result.isCharConvertible = false;
    result.isIntConvertible = false;
    result.isFloatConvertible = false;
    result.isDoubleConvertible = false;

    float f = 0.0f;
    if (literal == "nanf" || literal == "+inff" || literal == "-inff")
    {
        if (literal == "nanf")
            f = std::numeric_limits<float>::quiet_NaN();
        else if (literal == "+inff")
            f = std::numeric_limits<float>::infinity();
        else if (literal == "-inff")
            f = -std::numeric_limits<float>::infinity();
    }
    errno = 0; // Reset errno before conversion
    f = strtof(literal.c_str(), NULL);
    if (errno == ERANGE || !std::isfinite(f))
    {
        std::cout << "char: impossible\n";
        std::cout << "int: impossible\n";
        std::cout << "float: impossible\n";
        std::cout << "double: impossible\n";
        return;
    }
    result.f = f;
    result.isFloatConvertible = true;
    result.d = static_cast<double>(f);
    result.isDoubleConvertible = true;
    if (f >= std::numeric_limits<int>::min() && f <= std::numeric_limits<int>::max()) {
        result.i = static_cast<int>(f);
        result.isIntConvertible = true;
    }
    if (result.isIntConvertible &&
        result.i >= std::numeric_limits<char>::min() &&
        result.i <= std::numeric_limits<char>::max())
    {
        result.c = static_cast<char>(f);
        result.isCharConvertible = true;
    }
    printScalarValues(result);
}

void ScalarConverter::convertDouble(const std::string &literal)
{
    ScalarValues result;
    result.isCharConvertible = false;
    result.isIntConvertible = false;
    result.isFloatConvertible = false;
    result.isDoubleConvertible = false;

    errno = 0; // Reset errno before conversion
    char* end = NULL;
    double d = strtod(literal.c_str(), &end);
    if (errno == ERANGE || !std::isfinite(d))
    {
        std::cout << "char: impossible\n";
        std::cout << "int: impossible\n";
        std::cout << "float: impossible\n";
        std::cout << "double: impossible\n";
        return;
    }
    result.d = d;
    result.isDoubleConvertible = true;
    float f = static_cast<float>(d);
    if (std::isfinite(f)) {
        result.f = f;
        result.isFloatConvertible = true;
    }
    if (d >= std::numeric_limits<int>::min() && d <= std::numeric_limits<int>::max()) {
        result.i = static_cast<int>(d);
        result.isIntConvertible = true;
    }
    if (result.isIntConvertible &&
        result.i >= std::numeric_limits<char>::min() &&
        result.i <= std::numeric_limits<char>::max() &&
        std::isprint(static_cast<char>(d)))
    {
        result.c = static_cast<char>(d);
        result.isCharConvertible = true;
    }
    printScalarValues(result);
}

