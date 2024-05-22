#pragma once

constexpr unsigned MAX_CELL_SIZE = 50;
constexpr unsigned MAX_CELLS_COUNT_IN_ROW = 15;
constexpr unsigned BUFFER_SIZE = MAX_CELLS_COUNT_IN_ROW * MAX_CELL_SIZE;
constexpr unsigned MAX_ROWS_COUNT_IN_TABLE = 100;

constexpr char START_ROW_HTML[] = "<tr>";
constexpr char END_ROW_HTML[] = "</tr>";
constexpr char START_TABLE_HTML[] = "<table>";
constexpr char END_TABLE_HTML[] = "</table>";
constexpr char START_HEADER_HTML[] = "<th>";
constexpr char END_HEADER_HTML[] = "</th>";
constexpr char START_CELL_HTML[] = "<td>";
constexpr char END_CELL_HTML[] = "/td";

constexpr char ADD_COMMAND[] = "add";
constexpr char REMOVE_COMMAND[] = "remove";
constexpr char EDIT_COMMAND[] = "edit";
constexpr char PRINT_COMMAND[] = "print";
constexpr char QUIT_COMMAND[] = "quit";