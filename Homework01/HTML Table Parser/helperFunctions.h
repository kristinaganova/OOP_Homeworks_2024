#pragma once
#include <iostream>
#include "GlobalConstants.h"

void extractValue(const char* start, char* result);

bool isPrefix(const char* pattern, const char* text);

bool searchInText(const char* text, const char* pattern);

unsigned getNumLen(unsigned num);

bool isStartRow(const char* line);

bool isEndRow(const char* line);

bool isStartHeader(const char* line);

char* myStrstr(char* str1, const char* str2);

bool isDigit(char ch);

int myAtoi(const char* str);