#pragma once

#include "parameter.h"
#include "customFunction.h"
#include <vector>
#include <map>

class functionExecute {
private:
    std::map<std::string,customFunction*> allFunctions;
    functionExecute();
    functionExecute(const functionExecute& other) = default;
    parameter getResultFromIf(const std::string& str, int &ind, const std::vector<parameter>& params);
public:

    static functionExecute& getInstance();
    static parameter convertToParam(std::string& str, const std::vector<parameter> &params);

    void addCustomFunction(customFunction* function);
    parameter execute(const std::string& expression, const std::vector<parameter> &params);
};