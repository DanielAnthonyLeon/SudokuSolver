#include "Sudoku.hpp"

Sudoku::Sudoku() {
	for (int row = 1; row <= TABLE_SIZE; row++) {
		for (int column = 1; column <= TABLE_SIZE; column++) {
			m_table[row-1][column-1] = UNKNOWN_VALUE;
			m_fixedCells[row-1][column-1] = false;
		}
	}
}

int Sudoku::getCell(int row, int column) {
	return m_table[row-1][column-1];
}

void Sudoku::enterNumber(int row, int column, int number) {
	m_table[row-1][column-1] = number;
}

void Sudoku::readTableFromFile(std::string file) {
	std::ifstream table;
	table.open(file);
	int number;
	for (int row = 1; row <= TABLE_SIZE; row++) {
		for (int column = 1; column <= TABLE_SIZE; column++) {
			table >> number;
			enterNumber(row, column, number);
			if (number != 0) {
				m_fixedCells[row-1][column-1] = true;
			}
		}
	}
	table.close();
}

bool Sudoku::isRowValid(int row) {
	int seenBefore[TABLE_SIZE];
	for (int n = 1; n <= TABLE_SIZE; n++) {
		seenBefore[n-1] = false;
	}
	for (int column = 1; column <= TABLE_SIZE; column++) {
		int number = getCell(row, column);
		if (number == UNKNOWN_VALUE) {
			continue;
		}
		else if (number < 0 || number > TABLE_SIZE) {
			return false;
		}
		else if (seenBefore[number-1]) {
			return false;
		}
		else {
			seenBefore[number-1] = true;
		}
	}
	return true;
}

bool Sudoku::isColumnValid(int column) {
	int seenBefore[TABLE_SIZE];
	for (int n = 1; n <= TABLE_SIZE; n++) {
		seenBefore[n-1] = false;
	}
	for (int row = 1; row <= TABLE_SIZE; row++) {
		int number = getCell(row, column);
		if (number == UNKNOWN_VALUE) {
			continue;
		}
		else if (number < 0 || number > TABLE_SIZE) {
			return false;
		}
		else if (seenBefore[number-1]) {
			return false;
		}
		else {
			seenBefore[number-1] = true;
		}
	}
	return true;
}

bool Sudoku::isSquareValid(int square) {
	int seenBefore[TABLE_SIZE];
	for (int n = 1; n <= TABLE_SIZE; n++) {
		seenBefore[n-1] = false;
	}
	int topRow = ((square-1)/3) * 3 + 1;
	int leftColumn = ((square-1) % 3) * 3 + 1;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			int number = getCell(topRow+i, leftColumn+j);
			if (number == UNKNOWN_VALUE) {
				continue;
			}
			else if (number < 0 || number > TABLE_SIZE) {
				return false;
			}
			else if (seenBefore[number-1]) {
				return false;
			}
			else {
				seenBefore[number-1] = true;
			}
		}
	}
	return true;
}

bool Sudoku::isTableValid() {
	for (int index = 1; index <= TABLE_SIZE; index++) {
		if (!isRowValid(index)) {
			return false;
		}
		else if (!isColumnValid(index)) {
			return false;
		}
		else if (!isSquareValid(index)) {
			return false;
		}
	}
	return true;
}

bool Sudoku::isCellNeighbourhoodValid(int row, int column) {
	int square = (((row-1)/3 + 1) * 3 - 2) + (column-1)/3;
	int number = getCell(row, column);
	return number != UNKNOWN_VALUE &&
	isRowValid(row) && isColumnValid(column) && isSquareValid(square);
}

bool Sudoku::isRowComplete(int row) {
	if (isRowValid(row)) {
		for (int column = 1; column <= TABLE_SIZE; column++) {
			if (getCell(row, column) == UNKNOWN_VALUE) {
				return false;
			}
		}
		return true;
	}
	return false;
}

bool Sudoku::isColumnComplete(int column) {
	if (isColumnValid(column)) {
		for (int row = 1; row <= TABLE_SIZE; row++) {
			if (getCell(row, column) == UNKNOWN_VALUE) {
				return false;
			}
		}
		return true;
	}
	return false;
}

bool Sudoku::isSquareComplete(int square) {
	int topRow = ((square-1)/3) * 3 + 1;
	int leftColumn = ((square-1) % 3) * 3 + 1;
	if (isSquareValid(square)) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (getCell(topRow+i, leftColumn+j) == UNKNOWN_VALUE) {
					return false;
				}
			}
		}
		return true;
	}
	return false;
}

bool Sudoku::isTableComplete() {
	for (int index = 1; index <= TABLE_SIZE; index++) {
		if (!isRowComplete(index)) {
			return false;
		}
		else if (!isColumnComplete(index)) {
			return false;
		}
		else if (!isSquareComplete(index)) {
			return false;
		}
	}
	return true;
}

bool Sudoku::isCellFixed(int row, int column) {
	return m_fixedCells[row-1][column-1];
}

void Sudoku::solveTable() {
		// array of initially blank cells
	int variableCells[TABLE_SIZE*TABLE_SIZE][2];
	int index = 0;
		// fill in the array
	for (int row = 1; row <= TABLE_SIZE; row++) {
		for (int column = 1; column <= TABLE_SIZE; column++) {
			if (!isCellFixed(row, column)) {
				variableCells[index][0] = row;
				variableCells[index][1] = column;
				index++;
			}
		}
	}
		// Fill in the rest of the array with 0's so I know when I hit the end
	for (int i = index; i < TABLE_SIZE*TABLE_SIZE; i++) {
		variableCells[i][0] = variableCells[i][1] = 0;
	}
	
	int pointer = 0; // Points to current variable cell
	
	while (true) {
		if (pointer < 0) {
			std::cout << "No solution has been found\n";
			break;
		}
		else if (pointer >= TABLE_SIZE*TABLE_SIZE ||
						 variableCells[pointer][0] == 0) {
			std::cout << "A solution has been found!\n";
			std::cout << *this << std::endl;
			break;
		}
		int row = variableCells[pointer][0];
		int column = variableCells[pointer][1];
		int number = getCell(row, column);
		enterNumber(row, column, number+1);
		if (number > TABLE_SIZE) {
			enterNumber(row, column, UNKNOWN_VALUE);
			pointer--;
		}
		else if (isCellNeighbourhoodValid(row, column)) {
			pointer++;
			std::cout << *this << std::endl;
		}
	}
}

std::ostream& operator<<(std::ostream& os, const Sudoku& table) {
	os << "|-----------------------|\n";
	for (int row = 1; row <= TABLE_SIZE; row++) {
		os << "| ";
		for (int column = 1; column <= TABLE_SIZE; column++) {
			std::cout << table.m_table[row-1][column-1];
			if (column < TABLE_SIZE) {
				std::cout << " ";
			}
			if (column % 3 == 0 && column < TABLE_SIZE) {
				os << "| ";
			}
		}
		os << " |";
		os << std::endl;
		if (row % 3 == 0 && row < TABLE_SIZE) {
			os << "|-----------------------|\n";
		}
	}
	os << "|-----------------------|";
	return os;
}
