#pragma once

#include "parameter.h"
#include <vector>

class MainFunction {
public:
    static bool eq(const parameter& x, const parameter& y);

    static bool le(const parameter& x, const parameter& y);

    static bool nand(const parameter& x, const parameter& y);

    static size_t length(const parameter& x);

    static parameter head(parameter& x);

    static std::list<parameter> tail(parameter& x);

    static parameter list(double start, double x = 1);
    static parameter list(double start, double x, int n);

    static std::list<parameter> concat(std::list<parameter> l1, const std::list<parameter>& l2);

    static parameter If(const std::string &expr, const std::string &then, const std::string &otherwise, const std::vector<parameter>& params);

    static double read();

    static int write(const parameter& x);

    static int Int(const parameter& x);

};