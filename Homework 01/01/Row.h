#pragma once
#include "Cell.h"

class Row
{
    Cell cells[MAX_CELLS_COUNT_IN_ROW];
    unsigned cellsCount = 0;
public:
    Row() = default;
    const Cell* getCells() const;
    unsigned getCellsCount() const;
    void addCell(const Cell& cell);
    void editCell(unsigned cellIndex, const char* newValue);
    void setCellsCount(unsigned count);
};