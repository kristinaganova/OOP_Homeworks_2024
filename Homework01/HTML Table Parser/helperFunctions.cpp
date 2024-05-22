#include "helperFunctions.h"

void extractValue(const char* start, char* result)
{
    int valueIndex = 0;
    bool inTag = false;

    while (*start)
    {
        if (*start == '>')
            inTag = true;
        else if (inTag && *start != '<')
            result[valueIndex++] = *start;
        else if (inTag && *start == '<')
            break;

        start++;
    }
    result[valueIndex] = '\0';
}

bool isPrefix(const char* pattern, const char* text)
{
    while (*text != '\0' && *pattern != '\0')
    {
        if (*text != *pattern)
            return false;
        text++;
        pattern++;
    }
    return *pattern == '\0';
}

bool searchInText(const char* text, const char* pattern)
{
    size_t textLen = strlen(text);
    size_t patternLen = strlen(pattern);
    while (patternLen <= textLen)
    {
        if (isPrefix(pattern, text))
            return true;
        text++;
        textLen--;
    }
    return false;
}

unsigned getNumLen(unsigned num)
{
    int len = 0;
    while (num > 0)
    {
        num /= 10;
        len++;
    }
    return len;
}

bool isStartRow(const char* line)
{
    return searchInText(line, START_ROW_HTML);
}

bool isEndRow(const char* line)
{
    return searchInText(line, END_ROW_HTML);
}

bool isStartHeader(const char* line)
{
    return searchInText(line, START_HEADER_HTML);
}

char* myStrstr(char* str1, const char* str2)
{
    if (*str2 == '\0') return str1;
    if (*str1 == '\0') return nullptr;

    char* p1 = str1;

    while (*p1)
    {
        char* p1_start = p1;
        const char* p2 = str2;

        while (*p1 && *p2 && *p1 == *p2)
        {
            p1++;
            p2++;
        }

        if (*p2 == '\0') return p1_start;
        if (*p1_start == '\0') return nullptr;

        p1 = p1_start + 1;
    }

    return nullptr;
}

bool isDigit(char ch)
{
    return ch >= '0' && ch <= '9';
}

int myAtoi(const char* str)
{
    int result = 0;
    int sign = 1;
    int i = 0;

    while (str[i] == ' ')
        i++;

    if (str[i] == '-' || str[i] == '+')
    {
        sign = (str[i] == '-') ? -1 : 1;
        i++;
    }

    while (isDigit(str[i]))
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return result * sign;
}