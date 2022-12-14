#include "functionExecute.h"
#include <stack>
#include <iostream>

functionExecute::functionExecute() {

    allFunctions.emplace("eq",new customFunction("eq",2,""));
    allFunctions.emplace("le",new customFunction("le",2,""));
    allFunctions.emplace("nand",new customFunction("nand",2,""));
    allFunctions.emplace("length",new customFunction("length",1,""));
    allFunctions.emplace("head", new customFunction("head",1,""));
    allFunctions.emplace("tail", new customFunction("tail",1,""));
    allFunctions.emplace("list", new customFunction("list",-1,""));
    allFunctions.emplace("concat", new customFunction("concat",2,""));
    allFunctions.emplace("if", new customFunction("if",3,""));
    allFunctions.emplace("read",new customFunction("read",0,""));
    allFunctions.emplace("write",new customFunction("write",1,""));
    allFunctions.emplace("int",new customFunction("int",1,""));

    allFunctions.emplace("add", new customFunction("add", 2, ""));
    allFunctions.emplace("sub", new customFunction("sub", 2, ""));
    allFunctions.emplace("mul", new customFunction("mul", 2, ""));
    allFunctions.emplace("div", new customFunction("div", 2, ""));
    allFunctions.emplace("mod", new customFunction("mod",2,""));
    allFunctions.emplace("sqrt", new customFunction("sqrt",1, ""));

}

parameter functionExecute::getResultFromIf(const std::string &str, int& ind, const std::vector<parameter> &params) {
    std::string fst,snd,thr;
    int smallBracketsCount = 0, bigBracketsCount = 0;
    while(!(str[ind] == ',' && !smallBracketsCount && !bigBracketsCount)) {
        if(str[ind] == '(') smallBracketsCount++;
        if(str[ind] == ')') smallBracketsCount--;
        if(str[ind] == '[') bigBracketsCount++;
        if(str[ind] == ']') bigBracketsCount--;
        fst+=str[ind++];
    }
    ind++;
    smallBracketsCount = 0, bigBracketsCount = 0;
    while(!(str[ind] == ',' && !smallBracketsCount && !bigBracketsCount)) {
        if(str[ind] == '(') smallBracketsCount++;
        if(str[ind] == ')') smallBracketsCount--;
        if(str[ind] == '[') bigBracketsCount++;
        if(str[ind] == ']') bigBracketsCount--;
        snd+=str[ind++];
    }
    ind++;
    smallBracketsCount = 0, bigBracketsCount = 0;
    while(!(str[ind] == ')' && !smallBracketsCount && !bigBracketsCount)) {
        if(str[ind] == '(') smallBracketsCount++;
        if(str[ind] == ')') smallBracketsCount--;
        if(str[ind] == '[') bigBracketsCount++;
        if(str[ind] == ']') bigBracketsCount--;
        thr+=str[ind++];
    }

    return MainFunction::If(fst,snd,thr,params);
}

parameter functionExecute::execute(const std::string& expression, const std::vector<parameter> &params) {

    std::string str;
    std::stack<customFunction*> functionNames;
    int bracketsCount = 0;
    bool unlimited = false;
    parameter ans;
    for (int ind = 0; ind < expression.size(); ind++) {
        char i = expression[ind];
        if(str == "if"){
            ind++;
            ans = getResultFromIf(expression,ind,params);
            if(!functionNames.empty()) functionNames.top()->params.push_back(ans);
            str = "";

        }
        else if(i == '(' && !bracketsCount) {
            if(allFunctions.find(str) == allFunctions.end()) throw std::invalid_argument("There is no function with name= " + str);
            functionNames.emplace(new customFunction(*allFunctions.at(str)));
            str = "";

        }else if(i == ',' && !bracketsCount) {
            if(!str.empty()) functionNames.top()->params.emplace_back(convertToParam(str,params));
            str = "";
        }else if(i == ')' && !bracketsCount) {
            customFunction* cF = functionNames.top();
            functionNames.pop();
            if(!str.empty()) cF->params.emplace_back(convertToParam(str,params));
            ans = (cF->calc());
            if(ans.getType() == UNLIMITED_LIST) unlimited = true;
            if(!functionNames.empty()) functionNames.top()->params.push_back(ans);
            cF->params.clear();
            str = "";
            delete cF;
        }else if(i == '['){
            bracketsCount++;
            str += i;
        }else if(i == ']'){
            bracketsCount--;
            str+=i;
        } else if(bracketsCount > 0 || (bracketsCount == 0 && i != ' ' && i != '\n' && i != '\t')) {
            str += i;
        }
    }

    if(!str.empty()) ans = convertToParam(str,params);
    if(unlimited && ans.getType() == LIST_LITERAL) ans.setType(UNLIMITED_LIST);
    return ans;
}

parameter functionExecute::convertToParam(std::string &str, const std::vector<parameter> &params) {
    if(('0'<= str[0] && str[0] <= '9') || str[0] == '-') {
        return  parameter(std::stod(str));
    } else if(str[0] == '[') {
        double x = 0;
        std::list<parameter> l;
        std::string number;
        for(size_t i = 1; i < str.size(); i++) {
            if(str[i] == '-' || ('0'<= str[i] && str[i] <= '9')) {
                number += str[i];
            }else if(str[i] == ' '){
                x = std::stod(number);
                number = "";
                l.emplace_back(x);
            }
            else if(str[i] == '['){
                int bigBracketsCount = 1;
                std::string expr = "[";
                i++;
                while(bigBracketsCount != 0) {
                    if(str[i] == '[') bigBracketsCount++;
                    if(str[i] == ']') bigBracketsCount--;
                    expr+=str[i++];
                }
                l.emplace_back(convertToParam(expr,params));
            } else if(str[i] != ']'){
                int smallBracketsCount = 0, bigBracketsCount = 0;
                std::string expr;
                while(!(str[i] == ' ' && !smallBracketsCount && !bigBracketsCount) && i + 1 < str.size()) {
                    if(str[i] == '(') smallBracketsCount++;
                    if(str[i] == ')') smallBracketsCount--;
                    if(str[i] == '[') bigBracketsCount++;
                    if(str[i] == ']') bigBracketsCount--;
                    expr+=str[i++];
                }
                l.emplace_back(functionExecute::getInstance().execute(expr,params));
            }

        }
        if(!number.empty()){
            x = std::stod(number);
            number = "";
            l.emplace_back(x);
        }
        return  l;
    } else {
        int index = 0;
        int i = 1;
        while('0' <= str[i] && str[i] <= '9')
            index = index * 10 + (str[i++] - '0');
        return params[index];
    }
}

functionExecute &functionExecute::getInstance() {
    static functionExecute instance;
    return instance;
}

void functionExecute::addCustomFunction(customFunction* function) {
    if(allFunctions.find(function->getName()) != allFunctions.end()){
        std::cout<<"> 1 \n";
        customFunction* curr = allFunctions.at(function->getName());
        allFunctions.erase(function->getName());
        delete curr;
    } else {
        std::cout<<"> 0 \n";
    }
    allFunctions.emplace(function->getName(),function);
}




