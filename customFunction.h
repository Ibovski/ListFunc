#pragma once

#include "parameter.h"
#include "mainFunctions.h"
#include "mathFunctions.h"
#include <string>
#include <vector>

class customFunction{
private:
    std::string name;
    int paramsCount = 0;
    std::string exprToExecute;
    std::string& removeIntervals(std::string& str);
public:
    std::vector<parameter> params;
    customFunction(const customFunction& other);
    explicit customFunction(std::string _name, int _paramsCount, std::string _expr): name(removeIntervals(_name)), paramsCount(_paramsCount), exprToExecute(
            removeIntervals(_expr)) {};

    std::string getName() const { return name; }
    int getParameterCount() const { return paramsCount; }
    std::string getExpressionToExecute() const { return exprToExecute; }

    parameter calc();

};