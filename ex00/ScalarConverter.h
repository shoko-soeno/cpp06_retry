#ifndef SCALARCONVERTER_H
# define SCALARCONVERTER_H
# include <iostream>
# include <string>
# include <cstdlib>
# include <limits>
# include <cmath>
# include <cerrno>

// LiteralType detectType(const std::string& literal);

struct ScalarValues {
    bool    isCharConvertible;
    bool    isIntConvertible;
    bool    isFloatConvertible;
    bool    isDoubleConvertible;
    char    c;
    int     i;
    float   f;
    double  d;
};

enum LiteralType {
    TYPE_CHAR,
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_INVALID
};
// ScalarValues castToAllTypes(const std::string& literal, LiteralType type);
// void printScalarValues(const ScalarValues& values);

class ScalarConverter
{
private:
    ScalarConverter();
    ScalarConverter(const ScalarConverter &src);
    ScalarConverter &operator=(const ScalarConverter &other);
    static void printScalarValues(const ScalarValues& values);
    static void convertChar(const std::string &literal);
    static void convertInt(const std::string &literal);
    static void convertFloat(const std::string &literal);
    static void convertDouble(const std::string &literal);
    static LiteralType detectType(const std::string& literal);

public:
    ~ScalarConverter();
    static void convert(const std::string &literal);
};
/*
only static menbers
no instance of this class should be created
*/

#endif
