#pragma once
#include "Row.h"

class Table
{
	Row rows[MAX_ROWS_COUNT_IN_TABLE];
	unsigned rowsCount = 0;

    unsigned getMaxColumns() const;
    void calculateMaxColumnWidths(size_t* maxColumnWidths) const;
    void printRow(const Cell* cells, unsigned cellsCount, const size_t* maxColumnWidths) const; // because i dont want rows to be printed outside the table
public:
    void addRow(const Row& rowToAdd);
    void addRow(const Row& rowToAdd, unsigned rowIndex);
    void removeRow(unsigned rowNumber);
    void editCell(unsigned rowNumber, unsigned colNumber, const char* newValue);
    void print() const;
    const Row& getRowAtIndex(unsigned index) const;
    const Row* getRows() const;
    const unsigned getRowsCount() const;
    void setRowsCount(unsigned count);
};