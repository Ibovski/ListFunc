#include <iostream>
#include <utility>
#include "parameter.h"

parameter::parameter(const std::list<double> &list)  {
    for (double k : list) {
        this->list.emplace_back(k);
    }
    this->type = LIST_LITERAL;
}
parameter::parameter(std::list<parameter>  list, double step): list(std::move(list)), step(step), type(UNLIMITED_LIST) {}

parameter::parameter(std::list<double> &list, double step) {
    for (double k : list) {
        this->list.emplace_back(k);
    }
    this->step = step;
    this->type = UNLIMITED_LIST;
}

bool parameter::operator==(const parameter &other) const  {
    if(this->type == UNLIMITED_LIST && other.type == UNLIMITED_LIST){
        return this->step == other.step && this->list.front() == other.list.front();
    }
    if(this->type == UNLIMITED_LIST && other.type != UNLIMITED_LIST) return false;
    if(this->type == REAL_NUMBER && other.type == REAL_NUMBER) {
        return this->x == other.x;
    }
    if(this->type == REAL_NUMBER && other.type == LIST_LITERAL) {
        return other.list.size() == 1 && other.list.front().type == REAL_NUMBER && other.list.front().x == x;
    }
    if(this->type == LIST_LITERAL && other.type == LIST_LITERAL) {
        if(this->list.size() != other.list.size())
            return false;

        auto iterThis = list.begin();
        auto iterOther = other.list.begin();
        while(iterThis != list.end()){
            if(*iterThis != *iterOther) return false;
            iterThis++;
            iterOther++;
        }
        return true;
    }
    return other == *this;
}



bool parameter::operator<(const parameter &other) const {
    if(this->type == UNLIMITED_LIST || other.type == UNLIMITED_LIST) throw std::invalid_argument("You can't compare unlimited lists");
    if(this->type == REAL_NUMBER && other.type == REAL_NUMBER) {
        return this->x < other.x;
    }
    if(this->type == REAL_NUMBER && other.type == LIST_LITERAL) {
        return other.list.size() == 1 && other.list.front().type == REAL_NUMBER && other.list.front().x < x;
    }
    if(this->type == LIST_LITERAL && other.type == LIST_LITERAL) {
        if(this->list.size() != other.list.size())
            return this->list.size() < other.list.size();

        auto iterThis = list.begin();
        auto iterOther = other.list.begin();
        while(iterThis != list.end()){
            if(*iterThis != *iterOther) return *iterThis < *iterOther;
            iterThis++;
            iterOther++;
        }
        return true;
    }
    return !(other < *this);
}

bool parameter::operator!() const {
    if(this->type == REAL_NUMBER) return this->x == 0;
    return this->list.empty();
}

size_t parameter::length() const {
    if(this->type == REAL_NUMBER) return -1;
    if(this->type == UNLIMITED_LIST) return MAXELEMENTS;
    return this->list.size();
}

parameter parameter::getHead(){
    if(this->type == UNLIMITED_LIST && list.empty()){
        list.emplace_back((list.front().x + step));
        MAXELEMENTS--;
    }
    return this->list.front();
}

std::list<parameter> parameter::getTail() {
    std::list<parameter> newList = this->list;
    if(this->type == UNLIMITED_LIST && list.size() == 9 && MAXELEMENTS > 0){
        newList.emplace_back((list.back().x + step));
        MAXELEMENTS--;
    }
    newList.pop_front();
    return newList;
}

void parameter::print() const{
    if(this->type == REAL_NUMBER) std::cout<<this->x;
    else if(this->type == LIST_LITERAL){
        std::cout<<"[";
        auto it = this->list.begin();
        it->print();
        it++;
        while(it != this->list.end()){
            std::cout<<" ";
            it->print();
            it++;
        }
        std::cout<<"]";
    } else if(this->type == UNLIMITED_LIST) {
        std::cout<<"[";
        auto it = this->list.begin();
        it->print();
        it++;
        for(int i = 1; i <=10; i++) {
            std::cout<<" ";
            it->print();
            it++;
        }
        std::cout<<"...";
    }
}

void parameter::reset() {
    MAXELEMENTS = 100;
}


parameter::parameter() = default;

