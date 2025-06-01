#include "ScalarConverter.h"

LiteralType ScalarConverter::detectType(const std::string& literal) {
    if (literal.size() == 1 && std::isprint(literal[0]) && !std::isdigit(literal[0]))
        return TYPE_CHAR;
    else if (isInt(literal)) 
        return TYPE_INT;
    else if (isFloat(literal))
        return TYPE_FLOAT;
    if (isDouble(literal))
        return TYPE_DOUBLE;
    return TYPE_INVALID;
}

bool ScalarConverter::isInt(const std::string &literal)
{
    char *ptr;

    strtol(literal.c_str(), &ptr, 10);
    return (*ptr == '\0' && literal.find('.') == std::string::npos);
}

bool ScalarConverter::isFloat(const std::string &literal)
{
    char *ptr;

    if (literal == "nanf" || literal == "+inff" || literal == "-inff")
        return true;

    strtof(literal.c_str(), &ptr);
    return (*ptr == 'f' && *(ptr + 1) == '\0');
}

bool ScalarConverter::isDouble(const std::string &literal)
{
    char *ptr;

    if (literal == "nan" || literal == "+inf" || literal == "-inf")
        return true;

    strtod(literal.c_str(), &ptr);
    return (*ptr == '\0');
}
