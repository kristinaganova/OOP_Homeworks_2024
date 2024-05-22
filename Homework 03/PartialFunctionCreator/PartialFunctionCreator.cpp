#include "PartialFunctionCreator.h"

PartialFunctionByCriteria<CriteriaAlwaysDefined>* PartialFunctionCreator::createAlwaysDefinedCriteria(std::ifstream& ifs, int16_t N)
{
    if (N <= 0)
        throw std::invalid_argument("Invalid N");

    Vector<int32_t> args(N);
    args.readFromBinary(ifs, N);

    return new PartialFunctionByCriteria<CriteriaAlwaysDefined>(CriteriaAlwaysDefined(args));
}

PartialFunctionByCriteria<CriteriaNotDefinedInArgs>* PartialFunctionCreator::createNotDefinedInArgsCriteria(std::ifstream& ifs, int16_t N) 
{
    if (N <= 0)
        throw std::invalid_argument("Invalid N");

    Vector<int32_t> args(N);
    args.readFromBinary(ifs, N);

    return new PartialFunctionByCriteria<CriteriaNotDefinedInArgs>(CriteriaNotDefinedInArgs(args));
}

PartialFunctionByCriteria<CriteriaDefinedInArgs>* PartialFunctionCreator::createDefinedInArgsCriteria(std::ifstream& ifs, int16_t N) 
{
    if (N <= 0)
        throw std::invalid_argument("Invalid N");

    Vector<int32_t> args(N);
    args.readFromBinary(ifs, N);
    Vector<int32_t> res(N);
    res.readFromBinary(ifs, N);

    return new PartialFunctionByCriteria<CriteriaDefinedInArgs>(CriteriaDefinedInArgs(args, res));
}

PartialFunction** PartialFunctionCreator::readPartialFunctions(std::ifstream& in, int16_t& count) 
{
    if (count <= 0)
        throw std::invalid_argument("Invalid count of files");

    PartialFunction** functions = new PartialFunction * [count];

    char buffer[1024];
    for (size_t i = 0; i < count; i++) 
    {
        in.getline(buffer, 1024, '\0');
        functions[i] = partialFunctionFactory(buffer);
    }

    return functions;
}

MaxOfPartialFunctions* PartialFunctionCreator::createMaxOfPartialFunctions(std::ifstream& ifs, int16_t count) 
{
    if (count <= 0)
        throw std::invalid_argument("Invalid count of files");

    PartialFunction** functions = readPartialFunctions(ifs, count);
    return new MaxOfPartialFunctions(std::move(functions), count);
}

MinOfPartialFunctions* PartialFunctionCreator::createMinOfPartialFunctions(std::ifstream& ifs, int16_t count) 
{
    if (count <= 0)
        throw std::invalid_argument("Invalid count of files");

    PartialFunction** functions = readPartialFunctions(ifs, count);
    return new MinOfPartialFunctions(std::move(functions), count);
}

PartialFunction* PartialFunctionCreator::partialFunctionFactory(const char* fileName) 
{
    std::ifstream in(fileName, std::ios::binary);

    if (!in.is_open())
        throw std::runtime_error("Could not open file");

    int16_t T;
    in.read((char*)&T, sizeof(int16_t));

    int16_t N;
    in.read((char*)&N, sizeof(int16_t));

    switch (T) 
    {
    case 0: return createDefinedInArgsCriteria(in, N); break;
    case 1: return createNotDefinedInArgsCriteria(in, N); break;
    case 2: return createAlwaysDefinedCriteria(in, N); break;
    case 3: return createMaxOfPartialFunctions(in, N); break;
    case 4: return createMinOfPartialFunctions(in, N); break;
    default: throw std::runtime_error("Invalid mode"); break;
    }
}