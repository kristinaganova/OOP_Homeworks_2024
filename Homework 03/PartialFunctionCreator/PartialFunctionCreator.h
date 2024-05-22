#pragma once
#include <iostream>
#include <fstream>
#include "PartialFunctionByCriteria.hpp"
#include "CriteriaAlwaysDefined.h"
#include "CriteriaDefinedInArgs.h"
#include "CriteriaNotDefinedInArgs.h"
#include "MaxOfPartialFunctions.h"
#include "MinOfPartialFunctions.h"
#include "Vector.hpp"

class PartialFunctionCreator 
{
public:
    PartialFunctionByCriteria<CriteriaAlwaysDefined>* createAlwaysDefinedCriteria(std::ifstream& ifs, int16_t N);
    PartialFunctionByCriteria<CriteriaNotDefinedInArgs>* createNotDefinedInArgsCriteria(std::ifstream& ifs, int16_t N);
    PartialFunctionByCriteria<CriteriaDefinedInArgs>* createDefinedInArgsCriteria(std::ifstream& ifs, int16_t N);
    MaxOfPartialFunctions* createMaxOfPartialFunctions(std::ifstream& ifs, int16_t count);
    MinOfPartialFunctions* createMinOfPartialFunctions(std::ifstream& ifs, int16_t count);

    PartialFunction* partialFunctionFactory(const char* fileName);

private:
    PartialFunction** readPartialFunctions(std::ifstream& in, int16_t& count);
};
