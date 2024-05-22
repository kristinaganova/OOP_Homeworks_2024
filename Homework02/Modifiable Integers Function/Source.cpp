#include <iostream>
#include "ModifiableIntegersFunc.h"
#include <functional>


int16_t sampleFunc(int16_t x)
{
    return x + 1;
}
int16_t sampleFunc2(int16_t x)
{
    return x * x;
}

int main()
{
    try
    {
        ModifiableIntegersFunc func(sampleFunc2);
        std::cout << func.isInjective() << std::endl;
        std::cout << func.operator^(Pair(2, 3)) << std::endl;

        std::cout << "Plotting function:" << std::endl;
        func.plot(-10, 10);

        func.setCustomResults(0, 5);
        func.excludePoint(1);

        std::cout << "\nPlotting function after custom results and exclusions:" << std::endl;
        func.plot(-10, 10);

        std::cout << "\nFunction evaluation:" << std::endl;
        for (int16_t x = -5; x <= 5; ++x) {
            std::cout << "f(" << x << ") = " << func(x) << std::endl;
        }

        std::cout << "\nFunction composition:" << std::endl;
        ModifiableIntegersFunc composedFunc(sampleFunc);
        composedFunc.excludePoint(0);
        int16_t result = func(func, 2);
        std::cout << "f(g(2)) = " << result << std::endl;
    }
    catch (std::exception& ex)
    {
        std::cout << ex.what();
    }
    catch (...)
    {

    }
    return 0;
}
