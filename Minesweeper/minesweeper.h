#pragma once

int isInsideMatrix(int rows, int cols, int x, int y);

void print(int h, int w, char** t);

char** init_state(int h, int w);

void discover(int i, int j, int h, int w, char** t, char** s);

char** board_matrix(int h, int w, int nr_bombs);

bool gameOver(char mark, int x, int y, int h, int w, char** t, char** s);

bool equalMatrix(int h, int w, char** t, char** s);

void markCell(int i, int j, char** t);

void randomVectors(int h, int w, int* row, int* col, int nr_bombs);
