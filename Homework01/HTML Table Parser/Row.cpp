#include "Row.h"
#include <iostream>

void Row::addCell(const Cell& cell)
{
	if (cellsCount >= MAX_CELLS_COUNT_IN_ROW) 
	{
		std::cerr << "Error: Row can contain up to 30 cells." << std::endl;
		return;
	}
	cells[cellsCount++] = cell;
}

void Row::editCell(unsigned cellIndex, const char* newValue)
{
	if (cellIndex > cellsCount)
	{
		std::cerr << "Error: Index not in range." << std::endl;
		return;
	}
	cells[cellIndex].setCellVal(newValue);
}

const Cell* Row::getCells() const
{
	return cells;
}

unsigned Row::getCellsCount() const
{
	return this->cellsCount;
}

void Row::setCellsCount(unsigned count)
{
	if (count > MAX_CELLS_COUNT_IN_ROW)
	{
		std::cout << "Error: Cells count not in range." << std::endl;
		return;
	}
	cellsCount = count;
}