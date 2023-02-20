#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "minesweeper.h"

using namespace std;

void print(int h, int w, char** t) {
    system("cls");
    cout << "   ";
    for (int i = 65; i < 65 + w; i++)
        if (i < 91)
            cout << (char)i;
        else
            cout << (char)(i + 6);
    cout << endl;
    for (int i = 0; i < h; i++) {
        cout << left << setw(3) << i + 1;
        for (int j = 0; j < w; j++) {
            cout << t[i][j];
        }
        cout << right << setw(3) << i + 1 << endl;
    }
    cout << "   ";
    for (int i = 65; i < 65 + w; i++)
        if (i < 91)
            cout << (char)i;
        else
            cout << (char)(i + 6);
}

int isInsideMatrix(int rows, int cols, int x, int y) {
    return (x >= 0 && x < rows&& y >= 0 && y < cols);
}

char** init_state(int h, int w) {
    char** s = new char* [h];
    for (int i = 0; i < h; i++)
        s[i] = new char[w];
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            s[i][j] = '?';
    return s;
}

void discover(int i, int j, int h, int w, char** t, char** s) {
    if (!isInsideMatrix(h, w, i, j))
        return;
    if (t[i][j] == 'X')
        return;
    if (s[i][j] == '.')
        return;
    if (t[i][j] >= '1' && t[i][j] <= '8') {
        s[i][j] = t[i][j];
        return;
    }
    if (t[i][j] == '.') {
        s[i][j] = '.';
        for (int x = i - 1; x <= i + 1; x++)
            for (int y = j - 1; y <= j + 1; y++) {
                if (x == i && y == j)
                    continue;
                discover(x, y, h, w, t, s);
            }
        return;
    }
    return;
}

void randomVectors(int h, int w, int* row, int* col, int nr_bombs)
{
    int count = 0;
    while (count < nr_bombs)
    {
        int numberCol = rand() % w;
        int numberRow = rand() % h;
        bool exist = false;
        for (int i = 0; i < count; i++)
        {
            if (numberCol == col[i] && numberRow == row[i])
            {
                exist = true;
                break;
            }
        }
        if (exist == false)
        {
            col[count] = numberCol;
            row[count] = numberRow;
            count++;
        }
    }

}

char** board_matrix(int h, int w, int nr_bombs)
{
    int* col = new int[nr_bombs];
    int* row = new int[nr_bombs];
    randomVectors(h, w, row, col, nr_bombs);
    char** s = new char* [h];
    for (int i = 0; i < h; i++)
        s[i] = new char[w];
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            s[i][j] = '0';
    for (int i = 0; i < nr_bombs; i++)
    {
        int r = row[i];
        int c = col[i];
        s[r][c] = 'X';
    }
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (s[i][j] == 'X') {
                for (int x = i - 1; x <= i + 1; x++)
                    for (int y = j - 1; y <= j + 1; y++) {
                        if (x == i && y == j)
                            continue;
                        if (isInsideMatrix(h, w, x, y) == 1 && s[x][y] != 'X')
                            s[x][y]++;
                    }
            }
        }
    }
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            if (s[i][j] == '0')
                s[i][j] = '.';
    delete[] col;
    delete[] row;
    return s;
}

bool gameOver(char mark, int x, int y, int h, int w, char **t, char **s)
{
    if (s[x][y] == 'X' && mark != 'y')
        return true;
    bool equal_matrix = true;
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
        {
            if (t[i][j] != s[i][j] && s[i][j] != 'X')
                equal_matrix = false;
        }
    if (equal_matrix == true)
        return true;
    return false;
}

bool equalMatrix(int h, int w, char** t, char** s)
{
    bool equal = true;
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
        {
            if (t[i][j] != s[i][j] && s[i][j] != 'X')
                equal = false;
        }
    if (equal == false)
        return false;
    return true;
}

void markCell(int i, int j, char** t)
{
    if (t[i][j] == '?')
        t[i][j] = '!';
}
