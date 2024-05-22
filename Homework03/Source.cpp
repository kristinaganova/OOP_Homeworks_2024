#include <iostream>
#include <fstream>
#include "PartialFunctionCreator.h"

namespace 
{
    int convertCharToDigit(char ch)
    {
        if (ch >= '0' && ch <= '9')
            return ch - '0';
        return -1;
    }

    unsigned convertStrToUnsigned(const char* str)
    {
        if (!str)
            return 0;

        unsigned result = 0;
        while (*str)
        {
            int digit = convertCharToDigit(*str);
            if (digit == -1)
                return 0;
            (result *= 10) += digit;
            str++;
        }
        return result;
    }

    int convertStrToSigned(const char* str)
    {
        if (!str)
            return 0;

        if (*str == '-')
            return -1 * convertStrToUnsigned(str + 1);
        else
            return convertStrToUnsigned(str);
    }

    void createFunFile(const char* filename)
    {
        std::ofstream out(filename, std::ios::binary);
        int16_t mode = 3;
        int16_t count = 3;

        out.write((const char*)&mode, sizeof(int16_t));
        out.write((const char*)&count, sizeof(int16_t));

        char file1[] = "first.dat";
        out.write((const char*)file1, sizeof(file1));

        char file2[] = "second.dat";
        out.write((const char*)file2, sizeof(file2));

        char file3[] = "third.dat";
        out.write((const char*)file3, sizeof(file3));
    }

    void createT0(const char* name)
    {
        std::ofstream out(name, std::ios::binary);
        int16_t mode = 0;
        int16_t count = 7;
        out.write((char*)&mode, sizeof(int16_t));
        out.write((char*)&count, sizeof(int16_t));

        int32_t arr[] = { 0, 1, 2, 3, 5, 6, 7 };
        out.write((char*)arr, count * sizeof(int32_t));

        int32_t arr2[] = { 0, 3, 3, 3, 4, 4, 0 };
        out.write((char*)arr2, count * sizeof(int32_t));
    }

    void createT1(const char* name)
    {
        std::ofstream out(name, std::ios::binary);
        int16_t mode = 1;
        int16_t count = 2;
        out.write((char*)&mode, sizeof(int16_t));
        out.write((char*)&count, sizeof(int16_t));

        int32_t arr[] = { 3, 5 };
        out.write((char*)arr, count * sizeof(int32_t));
    }

    void createT2(const char* name)
    {
        std::ofstream out(name, std::ios::binary);
        int16_t mode = 2;
        int16_t count = 4;
        out.write((char*)&mode, sizeof(int16_t));
        out.write((char*)&count, sizeof(int16_t));

        int32_t arr[] = { 0,5,6,7 };
        out.write((char*)arr, count * sizeof(int32_t));
    }
}

void processInterval(PartialFunction* f, int a, int b)
{
    for (int i = a; i <= b; ++i) 
    {
        if (f->isDefinedAt(i))
            std::cout << "f(" << i << ")=" << f->calculate(i) << " ";
    }
    std::cout << std::endl;
}

void interactiveMode(PartialFunction* f) 
{
    char input[256];
    int x;

    while (true)
    {
        std::cout << "Enter a number (or 'exit' to quit): ";
        std::cin >> input;

        if (strcmp(input, "exit") == 0) break;

        bool isValidNumber = true;
        for (int i = 0; input[i] != '\0'; ++i)
        {
            if (!isdigit(input[i]) && (i != 0 || input[i] != '-'))
            {
                isValidNumber = false;
                break;
            }
        }

        if (isValidNumber) 
        {
            x = convertStrToSigned(input);

            if (f->isDefinedAt(x))
                std::cout << "f(" << x << ")=" << f->calculate(x) << std::endl;
            else
                std::cout << "Not defined at " << x << std::endl;
        }
        else 
        {
            std::cout << "Invalid input, please enter a valid number or 'exit' to quit." << std::endl;
        }
    }
}
 
void run()
{
    PartialFunctionCreator creator;

    char filename[1024];
    std::cout << "Enter file name:";
    std::cin >> filename;

    PartialFunction* func = creator.partialFunctionFactory(filename);

    int mode;
    std::cout << "Select mode (1: Interval, 2: Interactive): ";
    std::cin >> mode;

    if (mode == 1)
    {
        int a, b;
        std::cout << "Enter interval [a, b]: ";
        std::cin >> a >> b;

        std::cout << "Results:";
        processInterval(func, a, b);
    }
    else if (mode == 2)
    {
        std::cout << "Interactive mode:" << std::endl;
        interactiveMode(func);
    }
    else
    {
        std::cout << "Invalid mode selected." << std::endl;
    }

    delete func;
}

int main() 
{
    try 
    {
       /* const char f[] = "func.dat";
        const char t0[] = "first.dat";
        const char t1[] = "second.dat";
        const char t2[] = "third.dat";*/

       /* createFunFile(f);
        createT0(t0);
        createT1(t1);
        createT2(t2);*/

        run();
    }
    catch (std::exception& e)
    {
        std::cout << e.what();
    }
}