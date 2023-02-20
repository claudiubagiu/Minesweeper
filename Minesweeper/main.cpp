#include <iostream>
#include <ctime>
#include <cstdlib>
#include "minesweeper.h"

using namespace std;

int main()
{
	srand(time(0));
	int h, w, nr_bombs, row;
	char col;
	int x, y;
	char mark;
	cout << "Numarul de linii(0 < n < 100): ";
	cin >> h;
	cout << "Numarul de coloane(0 < m <= 52): ";
	cin >> w;
	cout << "Numarul de bombe: ";
	cin >> nr_bombs;
	char** hidden_matrix = init_state(h, w);
	char** random_matrix = board_matrix(h,w,nr_bombs);
	do 
	{
		print(h, w, hidden_matrix);
		cout << endl << "Doriti sa marcati o celula ? (y / n)" << endl;
		cin >> mark;
		cout << "Pozitia bombei(exemplu: A2): ";
		cin >> col >> row;
		x = row - 1;
		if (col <= 'Z')
			y = (int)col - 65;
		else
			y = (int)col - 71;
		if (mark == 'y')
			markCell(x, y, hidden_matrix);
		else
			discover(x, y, h, w, random_matrix, hidden_matrix);
	} while (!gameOver(mark, x, y, h, w, hidden_matrix, random_matrix));
	if (equalMatrix(h, w, hidden_matrix, random_matrix))
	{
		print(h, w, random_matrix);
		cout << endl << "Ai castigat!";
	}
	else
	{
		print(h, w, random_matrix);
		cout << endl << "Ai pierdut!";
	}

	for (int i = 0; i < h; i++) {
		delete[] hidden_matrix[i];
	}
	delete[] hidden_matrix;

	for (int i = 0; i < h; i++) {
		delete[] random_matrix[i];
	}
	delete[] random_matrix;

	return 0;
}