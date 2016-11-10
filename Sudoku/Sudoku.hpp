#ifndef Sudoku_hpp
#define Sudoku_hpp

#include <iostream>
#include <string>
#include <fstream>

#define UNKNOWN_VALUE 0
#define TABLE_SIZE 9

class Sudoku {
private:
	int m_table[TABLE_SIZE][TABLE_SIZE];
	bool m_fixedCells[TABLE_SIZE][TABLE_SIZE];
public:
	Sudoku();
	int getCell(int row, int column);
	void enterNumber(int row, int column, int number);
	void readTableFromFile(std::string file);
	bool isRowValid(int row);
	bool isColumnValid(int column);
	bool isSquareValid(int square);
	bool isTableValid();
	bool isCellNeighbourhoodValid(int row, int column);
	bool isRowComplete(int row);
	bool isColumnComplete(int column);
	bool isSquareComplete(int square);
	bool isTableComplete();
	bool isCellFixed(int row, int column);
	void solveTable();
	
	friend std::ostream& operator<<(std::ostream& os, const Sudoku& table);
};

#endif /* Sudoku_hpp */
