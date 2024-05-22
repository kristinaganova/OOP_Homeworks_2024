#include "Table.h"
#include <iostream>

void Table::addRow(const Row& rowToAdd)
{
    if (rowsCount < MAX_ROWS_COUNT_IN_TABLE) 
        rows[rowsCount++] = rowToAdd;
    else
        std::cerr << "Error: Maximum rows count exceeded." << std::endl;
}

void Table::addRow(const Row& rowToAdd, unsigned rowIndex)
{
    if (rowIndex > rowsCount)
    {
        std::cerr << "Error: rowIndex exceeds maximum rows count in table." << std::endl;
        return;
    }

    if (rowsCount > MAX_ROWS_COUNT_IN_TABLE)
    {
         std::cerr << "Error: Maximum rows count exceeded." << std::endl; 
         return;
    }
      
    for (unsigned i = rowsCount; i > rowIndex; i--)
            rows[i] = rows[i - 1];
    rows[rowIndex] = rowToAdd;
    rowsCount++;
}

void Table::removeRow(unsigned rowNumber)
{
    if (rowNumber < rowsCount) 
    {
        for (unsigned i = rowNumber; i < rowsCount - 1; ++i)
            rows[i] = rows[i + 1];
        --rowsCount;
    }
    else
        std::cerr << "Error: Row number out of bounds." << std::endl;
}

void Table::editCell(unsigned rowNumber, unsigned colNumber, const char* newValue)
{
    if (rowNumber < rowsCount)
    {
        if (colNumber < rows[rowNumber].getCellsCount())
            rows[rowNumber].editCell(colNumber, newValue);
        else
            std::cerr << "Error: Column number out of bounds." << std::endl;
    }
    else
        std::cerr << "Error: Row number out of bounds." << std::endl;
}

unsigned Table::getMaxColumns() const 
{
    unsigned maxCols = 0;
    for (unsigned i = 0; i < rowsCount; ++i)
        maxCols = std::max(maxCols, rows[i].getCellsCount());

    return maxCols;
}

void Table::calculateMaxColumnWidths(size_t* maxColumnWidths) const 
{
    for (unsigned i = 0; i < rowsCount; ++i)
    {
        for (unsigned j = 0; j < rows[i].getCellsCount(); ++j)
        {
            size_t cellWidth = std::strlen(rows[i].getCells()[j].getCellVal());
            if (rows[i].getCells()[j].getIsHeader())
                cellWidth += 2; // Adding 2 for the *
            maxColumnWidths[j] = std::max(maxColumnWidths[j], cellWidth);
        }
    }
}

void Table::printRow(const Cell* cells, unsigned cellsCount, const size_t* maxColumnWidths) const 
{
    std::cout << "|";
    for (unsigned j = 0; j < getMaxColumns(); ++j)
    {
        if (j < cellsCount) 
        {
            const Cell& cell = cells[j];
            size_t cellWidth = std::strlen(cell.getCellVal());
            size_t padding = maxColumnWidths[j] - cellWidth;

            if (cell.getIsHeader()) 
            {
                std::cout << "*" << cell.getCellVal() << "*";
                padding -= 2; // Adjust padding for the *
            }
            else 
                std::cout << cell.getCellVal();

            for (unsigned k = 0; k < padding; ++k)
                std::cout << " ";
        }
        else 
        {
            for (unsigned k = 0; k < maxColumnWidths[j]; ++k)
                std::cout << " ";
        }
        std::cout << "|";
    }
    std::cout << std::endl;
}

void Table::print() const 
{
    unsigned maxCols = getMaxColumns();
    size_t* maxColumnWidths = new size_t[maxCols]();

    calculateMaxColumnWidths(maxColumnWidths);

    for (unsigned i = 0; i < rowsCount; ++i) 
        printRow(rows[i].getCells(), rows[i].getCellsCount(), maxColumnWidths);

    delete[] maxColumnWidths;
}

const Row& Table::getRowAtIndex(unsigned index) const
{
    return rows[index];
}

const Row* Table::getRows() const
{
    return rows;
}

const unsigned Table::getRowsCount() const
{
    return rowsCount;
}

void Table::setRowsCount(unsigned count)
{
    if (count > MAX_ROWS_COUNT_IN_TABLE)
    {
        std::cerr << "Error: Rows count not in range." << std::endl;
        return;
    }
    this->rowsCount = count;
}