#include "Sudoku.hpp"
using namespace std;

int main() {
	/*Sudoku table2;
	table2.readTableFromFile("table2.txt");
		cout << table2 << endl;
		table2.solveTable();
	
	Sudoku table3;
	table3.readTableFromFile("table3.txt");
	cout << table3.isTableComplete() << endl;*/
	
	Sudoku table4;
	table4.readTableFromFile("table4.txt");
	cout << table4 << endl;
	table4.solveTable();
    return 0;
}
