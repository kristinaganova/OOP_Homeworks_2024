#include <iostream>
#include "MultiSet.h"
#include<fstream>

int main() 
{
    try
    {
        MultiSet set(9, 3);

        for (int i = 0; i < 10; i++)
        {
            set.add(i);
            if (i != 9) 
            {
                set.add(i + 1);
            }
            if (i != 0)
                set.add(i - 1);
        }
        set.print();
        set.printMemoryRepresentation();

        std::cout << std::endl;

        MultiSet set2(9, 3);

        for (int i = 0; i < 10; i++)
        {
            set2.add(i);

            if (i != 0)
                set2.add(i - 1);
        }
        set2.print();
        set2.printMemoryRepresentation();

        std::cout << std::endl;
        std::cout << set2.getCount(3) << std::endl;
        std::cout << std::endl;

        MultiSet set3 = set2 & set;
        set3.print();


        set3.serialize("file.dat");

        MultiSet set4 (9,3);
        std::ifstream is("file.dat", std::ios::binary | std::ios::in);
        if (!is.is_open())
            return 0;
        is >> set4;
        set4.print();
    }
    catch (const std::exception& e)
    {
        std::cout << e.what();
    }

    return 0;
}