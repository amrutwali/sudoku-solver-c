#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef N
#define N 9
#endif
#ifndef EMPTY
#define EMPTY 0
#endif

typedef struct
{
    int *data;
    int size;
    int capacity;
} IntPairList;

void InitIntPairList(IntPairList *list);
void AddPair(IntPairList *list, int first, int second);
IntPairList CreateE(void);
void PrintBoard(int board[N][N]);
bool isValid(int board[N][N], int row, int col, int num);
bool FindEmptyCell(int board[N][N], int *row, int *col);
bool SolveSudoku(int board[N][N]);

int main(int argc, char *argv[])
{
    int board[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0}, {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0}, {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1}, {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0}, {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9},
    };

    printf("Initial Sudoku puzzle:\n");
    PrintBoard(board);

    IntPairList E = CreateE();
    printf("\nSet E created with %d pairs.\n", E.size);

    if (SolveSudoku(board))
    {
        printf("\nSovled Sudoku puzzle:\n");
        PrintBoard(board);
    }
    else
        printf("\nNo solution exists.\n");

    free(E.data);
    return 0;
}

void InitIntPairList(IntPairList *list)
{
    list->size = 0;
    list->capacity = 10;
    list->data = malloc(list->capacity * 2 * sizeof(int));
}

void AddPair(IntPairList *list, int first, int second)
{
    if (list->size >= list->capacity)
    {
        list->capacity *= 2;
        list->data = realloc(list->data, list->capacity * 2 * sizeof(int));
    }
    list->data[list->size * 2] = first;
    list->data[list->size * 2 + 1] = second;
    list->size++;
}

IntPairList CreateE(void)
{
    IntPairList E;
    InitIntPairList(&E);
    int i, j, k, l, a, b;

    for (j = 1; j <= 9; j++)
    {
        for (k = 1; k <= 9; k++)
        {
            i = (j - 1) * 9 + k;
            a = j % 3;
            if (a == 0)
                a = 3;
            b = k % 3;
            if (b == 0)
                b = 3;
            // Same row
            for (l = k + 1; l <= 9; l++)
                AddPair(&E, i, i + l - k);
            // Same column
            for (l = j + 1; l <= 9; l++)
                AddPair(&E, i, (l - 1) * 9 + k);
            // Same 3x3 block
            if (a != 3)
            {
                if (b != 3)
                    AddPair(&E, i, j * 9 + k + 1);
                if (b != 2 && b != 3)
                    AddPair(&E, i, j * 9 + k + 2);
            }
            if (a == 1 || a == 2)
            {
                if (b == 1)
                {
                    AddPair(&E, i, (j + 1) * 9 + k);
                    AddPair(&E, i, (j + 1) * 9 + k + 1);
                    AddPair(&E, i, (j + 1) * 9 + k + 2);
                }
                else if (b == 2)
                {
                    AddPair(&E, i, (j + 1) * 9 + k - 1);
                    AddPair(&E, i, (j + 1) * 9 + k);
                    AddPair(&E, i, (j + 1) * 9 + k + 1);
                }
                else
                {
                    AddPair(&E, i, (j + 1) * 9 + k - 2);
                    AddPair(&E, i, (j + 1) * 9 + k - 1);
                    AddPair(&E, i, (j + 1) * 9 + k);
                }
            }
            if (a == 1)
            {

                if (b == 1)
                {
                    AddPair(&E, i, (j + 2) * 9 + k);
                    AddPair(&E, i, (j + 2) * 9 + k + 1);
                    AddPair(&E, i, (j + 2) * 9 + k + 2);
                }
                else if (b == 2)
                {
                    AddPair(&E, i, (j + 2) * 9 + k - 1);
                    AddPair(&E, i, (j + 2) * 9 + k);
                    AddPair(&E, i, (j + 2) * 9 + k + 1);
                }
                else
                {
                    AddPair(&E, i, (j + 2) * 9 + k - 2);
                    AddPair(&E, i, (j + 2) * 9 + k - 1);
                    AddPair(&E, i, (j + 2) * 9 + k);
                }
            }
        }
    }
    return E;
}

void PrintBoard(int board[N][N]) 
{
    printf("---------------------\n");
    for (int i = 0; i < N; i++)
    {
        printf("| ");
        for (int j = 0; j < N; j++)
        {
            if (board[i][j] == EMPTY)
            {
                printf(". ");
            }
            else
            {
                printf("%d ", board[i][j]);
            }
            if ((j + 1) % 3 == 0)
            {
                printf("---------------------\n");
            }
        }
    }
}

bool isValid(int board[N][N], int row, int col, int num)
{
    for (int x = 0; x < N; x++)
        if (board[row][x] == num)
            return false;

    for (int x = 0; x < N; x++)
        if (board[x][col] == num)
            return false;

    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i + startRow][j + startCol] == num)
                return false;

    return true;
}

bool FindEmptyCell(int board[N][N], int *row, int *col)
{
    for (*row = 0; *row < N; (*row)++)
        for (*col = 0; *col < N; (*col)++)
            if (board[*row][*col] == EMPTY)
                return true;

    return false;
}

bool SolveSudoku(int board[N][N]) 
{
    int row, col;

    if (!FindEmptyCell(board, &row, &col))
        return true;

    for (int num = 1; num <= 9; num++)
    {
        if (isValid(board,  row,  col,  num))
        {
            board[row][col] = num;

            if(SolveSudoku(board))
                return true;

            board[row][col] = EMPTY;
        }
    }
    return false; /* Trigger backtracking */
}














