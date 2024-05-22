#include "HTMLParser.h"

HTMLParser::~HTMLParser()
{
    saveTableToFile();
}

HTMLParser::HTMLParser(const char* filename)
{
    setFileName(filename);

    std::ifstream in(filename);

    if (!in.is_open())
    {
        throw "Error: Failed to open file";
    }

    parseHTMLTable(in);
    std::cout << "Table parsed successfully" << std::endl;
    std::cout << std::endl;

    in.close();
}

void HTMLParser::setFileName(const char* filename)
{
    if (!filename)
        return;

    std::strcpy(this->filename, filename);
    size_t len = strlen(filename);
    this->filename[len] = '\0';
}

const Table& HTMLParser::getTable() const
{
    return table;
}

Table& HTMLParser::getTable()
{
    return table;
}

void HTMLParser::parseHTMLTable(std::ifstream& file)
{
    char buff[BUFFER_SIZE];
    while (file.getline(buff, BUFFER_SIZE))
    {
        if (isStartRow(buff))
        {
            Row rowToAdd = parseRow(file);
            table.addRow(rowToAdd);
        }
    }
}

Row HTMLParser::parseRow(std::ifstream& file)
{
    Row rowToAdd;
    char buff[BUFFER_SIZE];

    while (!file.eof())
    {
        file.getline(buff, BUFFER_SIZE);
        if (isEndRow(buff))
            break;

        Cell cellToAdd = parseCell(buff);
        rowToAdd.addCell(cellToAdd);
    }

    return rowToAdd;
}

Cell HTMLParser::parseCell(const char* line)
{
    char cellVal[MAX_CELL_SIZE];
    extractValue(line, cellVal);

    Cell cellToAdd(cellVal);
    if (isStartHeader(line))
        cellToAdd.setIsHeader(true);

    return cellToAdd;
}

void HTMLParser::saveTableToFile() const
{
    std::ofstream file(filename, std::ios::out);

    if (!file.is_open())
    {
        std::cerr << "Error: Failed to open file " << filename << std::endl;
        return;
    }

    file << START_TABLE_HTML << '\n';

    for (unsigned int i = 0; i < table.getRowsCount(); i++)
    {
        file << '\t' << START_ROW_HTML << '\n';
        saveRowToFile(file, table.getRows()[i]);
        file << '\t' << END_ROW_HTML << '\n';
    }

    file << END_TABLE_HTML << std::endl; //to flush the buffer

    file.close();
}

void HTMLParser::saveCellToFile(std::ofstream& file, const Cell& cell) const
{
    const char* cellTag = (cell.getIsHeader() ? "th" : "td");
    file << "\t\t<" << cellTag << ">" << cell.getCellVal() << "</" << cellTag << ">" << '\n';
}

void HTMLParser::saveRowToFile(std::ofstream& file, const Row& row) const
{
    for (unsigned int j = 0; j < row.getCellsCount(); j++)
    {
        saveCellToFile(file, row.getCells()[j]);
    }
}