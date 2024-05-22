#include "Cell.h"
#include <iostream>
#pragma warning (disable:4996)

Cell::Cell() = default;

Cell::Cell(const char* val, bool header)
{
    setIsHeader(header);
    decodeCharacterEntityReference((char*)val);
    setCellVal(val);
}

void Cell::decodeCharacterEntityReference(char* value)
{
    char* reference = myStrstr(value, "&#");
    while (reference)
    {
        unsigned num = myAtoi(reference + 2);
        unsigned numlen = getNumLen(num);
        *reference = (char)num;
        char* src = reference + 2 + numlen; // +2 for the &# and
        char* dest = reference + 1;
        while (*src)
        {
            *dest = *src;
            src++;
            dest++;
        }
        *dest = '\0';
        reference = myStrstr(reference + 1, "&#");
    }
}

const char* Cell::getCellVal() const
{
    return this->cellVal;
}

bool Cell::getIsHeader() const
{
    return isHeader;
}

void Cell::setCellVal(const char* val)
{
    if (!val)
        return;
    strcpy(this->cellVal, val);
    size_t len = strlen(this->cellVal);
    this->cellVal[len] = '\0';
}

void Cell::setIsHeader(bool header)
{
    this->isHeader = header;
}