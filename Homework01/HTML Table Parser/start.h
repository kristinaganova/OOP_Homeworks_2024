#pragma once
#include <cstring>
#include "HTMLParser.h"
#include <sstream>
#include <fstream>

void handleAdd(const char* args, HTMLParser& parser)
{
    unsigned rowIndex;
    std::stringstream ss(args);
    ss >> rowIndex;
    ss.ignore();

    Row newRow;
    char cellValue[MAX_CELL_SIZE];
    while (ss.getline(cellValue, MAX_CELL_SIZE, ','))
    {
        Cell newCell(cellValue);
        newRow.addCell(newCell);
    }

    parser.getTable().addRow(newRow, rowIndex - 1);
}

void handleRemove(const char* args, HTMLParser& parser)
{
    unsigned rowIndex;
    std::stringstream ss(args);
    ss >> rowIndex;
    parser.getTable().removeRow(rowIndex - 1);
}

void handleEdit(const char* args, HTMLParser& parser)
{
    unsigned rowIndex, colIndex;
    char newValue[MAX_CELL_SIZE];
    std::stringstream ss(args);
    ss >> rowIndex >> colIndex >> newValue;
    parser.getTable().editCell(rowIndex - 1, colIndex - 1, newValue);
}

void handlePrint(HTMLParser& parser)
{
    parser.getTable().print();
}

void handleCommand(const char* command, HTMLParser& parser)
{
    std::stringstream ss(command);
    char operation[10];
    ss >> operation;

    if (strcmp(operation, ADD_COMMAND) == 0)
    {
        handleAdd(command + strlen(ADD_COMMAND), parser);
    }
    else if (strcmp(operation, REMOVE_COMMAND) == 0)
    {
        handleRemove(command + strlen(REMOVE_COMMAND), parser);
    }
    else if (strcmp(operation, EDIT_COMMAND) == 0)
    {
        handleEdit(command + strlen(EDIT_COMMAND), parser);
    }
    else if (strcmp(operation, PRINT_COMMAND) == 0)
    {
        handlePrint(parser);
    }
    else
    {
        std::cerr << "Error: Invalid command." << std::endl;
    }
}

void printMenu()
{
    std::cout << "Command options:" << std::endl;
    std::cout << "1. add <row number>, <value1>, <value2>,... " << std::endl;
    std::cout << "2. edit <row number> <col number> <value> " << std::endl;
    std::cout << "3. print" << std::endl;
    std::cout << "4. remove <row number>" << std::endl;
}

void run()
{
    char filename[BUFFER_SIZE];
    std::cout << "Enter filename: ";
    std::cin >> filename;
    HTMLParser parser(filename);
    std::cin.ignore();

    const int MAX_COMMAND_LENGTH = 100;
    char command[MAX_COMMAND_LENGTH];

    while (true)
    {
        printMenu();
        std::cout << std::endl;

        std::cout << "Enter command: ";
        std::cin.getline(command, MAX_COMMAND_LENGTH);
        if (std::strcmp(command, QUIT_COMMAND) == 0)
            break;
        handleCommand(command, parser);
        std::cout << std::endl;
    }
}