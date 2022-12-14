#include <iostream>
#include "functionExecute.h"

int parameter::MAXELEMENTS = 100;

void read(const std::string& line, const std::vector<parameter>& emptyVector){
    std::size_t SIZE = line.size();
    std::string name;
    size_t i = 0;
    while(i + 1 < SIZE && !(line[i] == '-' && line[i+1] == '>')) {
        name += line[i++];
    }
    if(i + 1 >= SIZE) {
        if(line[i] == '>' && line[i-1] == '-') {
            std::cout<<"> Empty declaration of function \n";
        }
        else {
            try{
                parameter::reset();
                std::cout<<"> ";
                functionExecute::getInstance().execute(line,emptyVector).print();
                std::cout<<"\n";
            } catch (std::exception& e) {
                std::cout<<e.what()<<"\n";
            }
        }
    } else {
        i+=2;
        int paramsCount = 0;
        int smallBracketsCount = 0, bigBracketsCount = 0;
        std::string exprToExecute;
        while(i < SIZE) {
            if(line[i] == '(') smallBracketsCount++;
            if(line[i] == ')') smallBracketsCount--;
            if(line[i] == '[') bigBracketsCount++;
            if(line[i] == ']') bigBracketsCount--;
            if(line[i -1] == '#') {
                int x = 0;
                while('0' <= line[i] && line[i] <= '9') {
                    x = x * 10 + (line[i] - '0');
                    i++;
                }
                if(line[i-1] == '#') {
                    std::cout<<"Invalid declaration of function \n";
                    break;
                }
                if(x + 1 - paramsCount > 2) {
                    std::cout<<"Invalid declaration of parameters \n";
                    break;
                }
                paramsCount = std::max(paramsCount,x + 1);
                i--;
            }
            exprToExecute += line[i];
            i++;
        }
        if(!smallBracketsCount && !bigBracketsCount)  {
            functionExecute::getInstance().addCustomFunction(new customFunction(name,paramsCount,exprToExecute));
        }
    }
}

int main(int argc, const char* argv[]) {

    std::string line;
    std::vector<parameter> emptyVector;
    for(int i = 1; i < argc; i++){
        std::fstream fin(argv[i]);
        while(!fin.eof()){
            std::getline(fin,line);
            read(line,emptyVector);
        }
    }

    while(line != "exit"){
        std::getline(std::cin,line);
        std::cout<<"Curr line is: "<<line<<"\n";
        read(line,emptyVector);
    }


    return 0;
}
/*

and -> not(nand(#0, #1))
divisors -> concat([2],list(3, 2,add(1, int(sqrt(#0)))))
containsDevisors -> if(length(#0),if(eq(#1, head(#0)), containsDevisors(tail(#0), #1), if(mod(#1,head(#0)), containsDevisors(tail(#0), #1), 1)),0)
isPrime -> not(containsDevisors(divisors(#0), #0))
filterPrimes -> if(length(#0), if(isPrime(head(#0)),concat([head(#0)], filterPrimes(tail(#0))),filterPrimes(tail(#0))), [])
primes10 -> filterPrimes(concat([2], list(3, 1, 7)))

allPrimes -> filterPrimes(concat([2], list(3)))

not -> nand(#0, 1)
or -> nand(not(#0), not(#1))
p -> if(length(#0), or(write(head(#0)), p(tail(#0))), 1)

containsDevisors([2 3], 5)
 */