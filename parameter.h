#pragma once
#include <fstream>
#include <string>
#include <list>
#include <utility>

enum Type {
    REAL_NUMBER = 0,
    LIST_LITERAL = 1,
    UNLIMITED_LIST = 2,
    UNKNOWN = 3,
};

class parameter{
private:
    double x = 0;
    double step = 0;
    std::list<parameter> list;
    Type type = UNKNOWN;
    static int MAXELEMENTS;
public:

    parameter();
    explicit parameter(double x) : x(x), type(REAL_NUMBER) {}
    parameter(std::list<parameter> list, double step);
    parameter(std::list<double>& list, double step);
    parameter(std::list<parameter> list): list(std::move(list)), type(LIST_LITERAL) {}
    explicit parameter(const std::list<double>& list);
    explicit parameter(std::list<parameter>&& list): list(std::move(list)), type(LIST_LITERAL) {}
    bool operator==(const parameter& other) const;
    bool operator<(const parameter& other) const;
    bool operator!() const;
    bool operator!=(const parameter& other) const { return !(*this == other); }

    void print() const;

    size_t length() const;

    parameter getHead();

    std::list<parameter> getTail();

    static int getMAXELEMENTS() { return MAXELEMENTS; }
    double getX() const { return x; }
    double getStep() const { return step; }
    void setX(double _x) { x = _x; }
    void setType(Type type1) { type = type1; }
    std::list<parameter> getList() const { return list; }
    Type getType() const {return type; }
    void add(const parameter& el) { list.push_back(el); }
    static void reset();
};