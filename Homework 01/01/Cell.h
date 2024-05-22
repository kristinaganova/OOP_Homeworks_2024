#pragma once
#include "GlobalConstants.h"
#include "helperFunctions.h"

class Cell
{
	char cellVal[MAX_CELL_SIZE + 1] = "";
	bool isHeader = false;
	void decodeCharacterEntityReference(char* value);
public:

	Cell();
	explicit Cell(const char* val, bool header = false);
	const char* getCellVal() const;
	bool getIsHeader() const;
	void setCellVal(const char* val);
	void setIsHeader(bool header);
};