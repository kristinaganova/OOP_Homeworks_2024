#pragma once
#include "Table.h"
#include <iostream>
#include <fstream>
#pragma warning (disable:4996)

class HTMLParser
{
private:
    char filename[MAX_CELL_SIZE];
    Table table;
public: 
    ~HTMLParser();
    explicit HTMLParser(const char* filename);
    void setFileName(const char* filename);
    const Table& getTable() const;
    Table& getTable();
    void parseHTMLTable(std::ifstream& file);
    void saveTableToFile() const;
    
private:
    Row parseRow(std::ifstream& file);
    Cell parseCell(const char* line);

    void saveCellToFile(std::ofstream& file, const Cell& cell) const;
    void saveRowToFile(std::ofstream& file, const Row& row) const;
};