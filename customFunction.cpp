#include "customFunction.h"
#include "functionExecute.h"

parameter customFunction::calc() {
    if(params.size() != paramsCount && name != "list") throw std::invalid_argument("Not enough parameters for " + name);
    if(exprToExecute.empty()) {
        if(name == "eq") {
            return parameter(MainFunction::eq(params[0],params[1]));
        }
        if(name == "le") {
            return parameter(MainFunction::le(params[0],params[1]));
        }
        if(name == "nand") {
            return parameter(MainFunction::nand(params[0],params[1]));
        }
        if(name == "length") {
            return parameter(MainFunction::length(params[0]));
        }
        if(name == "head") {
            return parameter(MainFunction::head(params[0]));
        }
        if(name == "tail") {
            std::list<parameter> l = MainFunction::tail(params[0]);
            if(params[0].getType() == UNLIMITED_LIST) return {l,params[0].getStep()};
            return {l};
        }
        if(name == "list") {
            if(params.size() == 1){
                if(params[0].getType() != REAL_NUMBER) throw std::invalid_argument("Invalid arguments for list(#0) function, #0 must be a REAL_NUMBER");
                return MainFunction::list(params[0].getX());
            }
            if(params.size() == 2){
                if(params[0].getType() != REAL_NUMBER || params[1].getType() != REAL_NUMBER) throw std::invalid_argument("Invalid arguments for list(#0,#1) function");
                return MainFunction::list(params[0].getX(),params[1].getX());
            }
            if(params.size() == 3){
                if(params[0].getType() != REAL_NUMBER || params[1].getType() != REAL_NUMBER || params[2].getType() != REAL_NUMBER) throw std::invalid_argument("Invalid arguments for list(#0,#1,#2) function");
                return MainFunction::list(params[0].getX(),params[1].getX(),params[2].getX());
            }
            throw std::invalid_argument("Not enough parameters for " + name);
        }
        if(name == "concat") {
            if(params[0].getType() != LIST_LITERAL || params[1].getType() == REAL_NUMBER) throw std::invalid_argument("Invalid arguments for concat function");
            std::list<parameter> conc =  MainFunction::concat(params[0].getList(),params[1].getList());
            if(params[1].getType() == UNLIMITED_LIST) return {conc,params[1].getStep()};
            return conc;
        }
        if(name == "read") {
            return parameter(MainFunction::read());
        }
        if(name == "write"){
            return parameter(MainFunction::write(params[0]));
        }
        if(name == "read") {
            return parameter(MainFunction::write(params[0]));
        }
        if(name == "int") {
            return parameter(MainFunction::Int(params[0]));
        }
        if(name == "add") {
            if(params[0].getType() != REAL_NUMBER && params[1].getType() != REAL_NUMBER) throw std::invalid_argument("Invalid argument: must be real number in add function");
            return parameter(MathFunctions::add(params[0].getX(),params[1].getX()));
        }
        if(name == "sub") {
            if(params[0].getType() != REAL_NUMBER && params[1].getType() != REAL_NUMBER) throw std::invalid_argument("Invalid argument: must be real number in sub function");
            return parameter(MathFunctions::sub(params[0].getX(),params[1].getX()));
        }
        if(name == "mul") {
            if(params[0].getType() != REAL_NUMBER && params[1].getType() != REAL_NUMBER) throw std::invalid_argument("Invalid argument: must be real number in mul function");
            return parameter(MathFunctions::mul(params[0].getX(),params[1].getX()));
        }
        if(name == "div") {
            if(params[0].getType() != REAL_NUMBER && params[1].getType() != REAL_NUMBER) throw std::invalid_argument("Invalid argument: must be real number in div function");
            return parameter(MathFunctions::div(params[0].getX(),params[1].getX()));
        }
        if(name == "mod") {
            if(params[0].getType() != REAL_NUMBER && params[1].getType() != REAL_NUMBER) throw std::invalid_argument("Invalid argument: must be real number in mod function");
            return parameter(MathFunctions::mod(params[0].getX(),params[1].getX()));
        }
        if(name == "sqrt") {
            if(params[0].getType() != REAL_NUMBER) throw std::invalid_argument("Invalid argument: must be real number in sqrt function");
            return parameter(MathFunctions::SQRT(params[0].getX()));
        }
    }
    return functionExecute::getInstance().execute(exprToExecute,params);
}

std::string& customFunction::removeIntervals(std::string &str) {
    while(str[0] == ' ' || str[0] == '\n' || str[0] == '\t') str.erase(0,1);
    while(str[str.size() - 1] == ' ' || str[str.size() - 1] == '\n' || str[str.size() - 1] == '\t') str.pop_back();

    return str;
}

customFunction::customFunction(const customFunction &other) = default;

