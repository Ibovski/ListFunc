#include "mathFunctions.h"
#include <iostream>

double MathFunctions::add(double x, double y) {
    return x + y;
}

double MathFunctions::sub(double x, double y) {
    return x - y;
}

double MathFunctions::mul(double x, double y) {
    return x * y;
}

double MathFunctions::div(double x, double y) {
    if(y == 0) throw std::invalid_argument("Can not divide by 0");
    return x / y;
}

int MathFunctions::mod(double x, double y) {
    if(x != (int) x || y != (int) y)  throw std::invalid_argument("The argument in mod function");
    return (int)x % (int)y;
}

double MathFunctions::SQRT(double x) {
    return sqrt(x);
}
