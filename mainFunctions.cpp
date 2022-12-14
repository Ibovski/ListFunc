#include <iostream>
#include "mainFunctions.h"
#include "functionExecute.h"

bool MainFunction::eq(const parameter& x, const parameter& y) {
    return  x == y;
}

bool MainFunction::le(const parameter& x, const parameter& y) {
    return x < y;
}

bool MainFunction::nand(const parameter &x, const parameter &y) {
    return !x || !y;
}

size_t MainFunction::length(const parameter& x) {
    return x.length();
}

parameter MainFunction::head(parameter& x) {
    return x.getHead();
}

std::list<parameter> MainFunction::tail(parameter& x) {
    return x.getTail();
}



std::list<parameter> MainFunction::concat(std::list<parameter> l1, const std::list<parameter> &l2) {
    for (const parameter& curr : l2) {
        l1.push_back(curr);
    }
    return l1;
}

parameter MainFunction::If(const std::string &expr, const std::string &then, const std::string &otherwise, const std::vector<parameter>& params) {
    if(!(functionExecute::getInstance().execute(expr,params))) return functionExecute::getInstance().execute(otherwise,params);
    return functionExecute::getInstance().execute(then,params);
}

double MainFunction::read() {
    double x;
    std::cout<<"read(): ";
    std::cin>>x;
    std::string empty;
    std::getline(std::cin,empty);
    return x;
}

int MainFunction::write(const parameter& x) {
    x.print();
    std::cout<<"\n";
    return 0;
}

int MainFunction::Int(const parameter& x) {
    if(x.getType() == REAL_NUMBER) return int(x.getX());
    return 0;
}

parameter MainFunction::list(double start, double x, int n) {
    std::list<double> newList;
    newList.push_back(start);
    for (int i = 1; i < n ; i++) {
        start += x;
        newList.push_back(start);
    }

    return parameter(newList);
}

parameter MainFunction::list(double start, double x) {
    std::list<double> newList;
    newList.push_back(start);
    for (int i = 1; i <= 10 ; i++) {
        start += x;
        newList.push_back(start);
    }
    return {newList,x};
}




