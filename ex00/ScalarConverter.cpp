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
    ScalarValues result = {};

    char c = literal[0];
    if (literal.length() != 1)
    {
        result.isCharConvertible = false;
    } else {
        result.c = c;
        result.isCharConvertible = true;
    }
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
    ScalarValues result = {};
    long l = strtol(literal.c_str(), NULL, 10);

    if (l > std::numeric_limits<int>::max() || l < std::numeric_limits<int>::min())
    {
        result.isCharConvertible = false;
        result.isIntConvertible = false;
    } else {
        int i = static_cast<int>(l);
        result.i = i;
        result.isIntConvertible = true;
        if (i >= std::numeric_limits<char>::min() &&
            i <= std::numeric_limits<char>::max())
        {
            result.c = static_cast<char>(i);
            result.isCharConvertible = true;
        } else {
            result.isCharConvertible = false;
        }
    }
    result.f = static_cast<float>(l);
    result.isFloatConvertible = true;
    result.d = static_cast<double>(l);
    result.isDoubleConvertible = true;
    printScalarValues(result);
}

void ScalarConverter::convertFloat(const std::string &literal)
{
    ScalarValues result = {};

    float f = 0.0f;
    if (isSpecialLiteral(literal, result))
        return printScalarValues(result);
    errno = 0;
    char* end = NULL;
    f = strtof(literal.c_str(), &end);
    if (errno == ERANGE || *end != 'f' || *(end + 1) != '\0')
    {   
        errno = 0;
        std::string doubleLiteral = literal.substr(0, literal.length() - 1); // Remove 'f' for double conversion
        char* end2 = NULL;
        double d = strtod(doubleLiteral.c_str(), &end2);
        if (errno == ERANGE || *end2 != '\0')
        {
            result.isDoubleConvertible = false;
        } else {
            result.d = d;
            result.isDoubleConvertible = true;
        }
        return printScalarValues(result);
    }
    result.f = f;
    result.isFloatConvertible = true;

    errno = 0; // Reset errno before double conversion
    std::string doubleLiteral = literal.substr(0, literal.length() - 1); // Remove 'f' for double conversion
    char* end3 = NULL;
    double d = strtod(doubleLiteral.c_str(), &end3);
    if (errno == ERANGE || *end3 != '\0')
    {
        result.isDoubleConvertible = false;
    } else {
        result.d = d;
        result.isDoubleConvertible = true;
    }

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
    ScalarValues result = {};

    if (isSpecialLiteral(literal, result))
        return printScalarValues(result);
    errno = 0; // Reset errno before conversion
    char* end = NULL;
    double d = strtod(literal.c_str(), &end);
    if (errno == ERANGE || *end != '\0')
    {
        result.isCharConvertible = false;
        result.isIntConvertible = false;
        result.isFloatConvertible = false;
        result.isDoubleConvertible = false;
        return printScalarValues(result);
    }
    result.d = d;
    result.isDoubleConvertible = true;
    float f = static_cast<float>(d);
    if (std::isfinite(f)) {
        result.f = f;
        result.isFloatConvertible = true;
    } else {
        result.isFloatConvertible = false;
    }

    if (d >= std::numeric_limits<int>::min() && d <= std::numeric_limits<int>::max()) {
        result.i = static_cast<int>(d);
        result.isIntConvertible = true;
    } else {
        result.isIntConvertible = false;
    }

    if (result.isIntConvertible &&
        result.i >= std::numeric_limits<char>::min() &&
        result.i <= std::numeric_limits<char>::max() &&
        std::isprint(static_cast<char>(d)))
    {
        result.c = static_cast<char>(d);
        result.isCharConvertible = true;
    } else {
        result.isCharConvertible = false;
    }
    printScalarValues(result);
}

bool ScalarConverter::isSpecialLiteral(const std::string &literal, ScalarValues &result)
{
    if (literal == "nanf" || literal == "+inff" || literal == "-inff")
    {
        result.isCharConvertible = false;
        result.isIntConvertible = false;
        result.isFloatConvertible = true;
        result.isDoubleConvertible = true;
        if (literal == "nanf")
            result.f = std::numeric_limits<float>::quiet_NaN();
        else if (literal == "+inff")
            result.f = std::numeric_limits<float>::infinity();
        else if (literal == "-inff")
            result.f = -std::numeric_limits<float>::infinity();
        result.d = static_cast<double>(result.f);
        return true;
    }
    if (literal == "nan" || literal == "+inf" || literal == "-inf")
    {
        result.isCharConvertible = false;
        result.isIntConvertible = false;
        result.isFloatConvertible = true;
        result.isDoubleConvertible = true;
        if (literal == "nan")
            result.d = std::numeric_limits<double>::quiet_NaN();
        else if (literal == "+inf")
            result.d = std::numeric_limits<double>::infinity();
        else if (literal == "-inf")
            result.d = -std::numeric_limits<double>::infinity();
        result.f = static_cast<float>(result.d);
        return true;
    }
    return false;
}
