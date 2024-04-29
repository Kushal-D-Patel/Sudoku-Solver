/**
 * Exercise 11 - Sudoku
 *
 * Please read the comments below carefully, they describe your task in detail.
 *
 * Any clarifications and corrections will be posted to Piazza so please keep an
 * eye on the forum!
 *
 * Unauthorized distribution or posting is strictly prohibited. You must seek
 * approval from course staff before uploading and sharing with others.
 *
 * Starter code:  (Updated by) Charles Xu, 2024
 *             (Originally by) Mustafa Quraish, 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ===========================================================================
// DO NOT CHANGE ANY 'ifndef' AND 'endif' MACROS.
// These macros help ensure your parts of your code does not conflict with the
// automarker. Changing them will result in your code not compiling and you
// receiving a 0 for the entire assignment.
// ===========================================================================
#ifndef __testing__

/**
 * Given a 9x9 Sudoku grid, this function prints out the grid in a format
 * that is easy to view, aiding in debugging or visualization.
 *
 * @param sudoku The 9x9 Sudoku grid to be printed.
 */
void print_sudoku(int sudoku[9][9]) {
    printf("The Sudoku contains:\n");
    printf("+-------+-------+-------+\n");
    for (int j = 0; j < 9; j++) {
        printf("| ");
        for (int i = 0; i < 9; i++) {
            printf("%d ", sudoku[j][i]);
            if (i % 3 == 2) printf("| ");
        }
        printf("\n");
        if (j % 3 == 2) printf("+-------+-------+-------+\n");
    }
}

#endif

/**
 * This function checks if the current Sudoku grid (not necessarily complete)
 * is valid. A Sudoku grid is considered valid if, ignoring the 0s, each row,
 * column, and 3x3 subgrid does not repeat any digits from 1 to 9.
 *
 * @note An incomplete Sudoku grid may be valid if the criteria above is met.
 *
 * @param sudoku The 9x9 Sudoku grid to be checked.
 * @return 1 if the Sudoku is valid, 0 if it's not.
 */
int is_valid_sudoku(int sudoku[9][9]) {
    int row[9][10] = {0}; // Array to track numbers in each row
    int col[9][10] = {0}; // Array to track numbers in each column
    int subgrid[3][3][10] = {0}; // Array to track numbers in each 3x3 subgrid

    // Check rows, columns, and 3x3 subgrids for repeated numbers
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int num = sudoku[i][j];
            if (num == 0) continue; // Skip if it's an empty cell

            // Check row
            if (row[i][num]) return 0;
            row[i][num] = 1;

            // Check column
            if (col[j][num]) return 0;
            col[j][num] = 1;

            // Check subgrid
            int subgrid_row = i / 3;
            int subgrid_col = j / 3;
            if (subgrid[subgrid_row][subgrid_col][num]) return 0;
            subgrid[subgrid_row][subgrid_col][num] = 1;
        }
    }

    // If no repeated numbers found, Sudoku is valid
    return 1;
}

int find_empty_cell(int sudoku[9][9], int *row, int *col) {
    for (*row = 0; *row < 9; (*row)++) {
        for (*col = 0; *col < 9; (*col)++) {
            if (sudoku[*row][*col] == 0)
                return 1; // Found an empty cell
        }
    }
    return 0; // No empty cell found
}

int used_in_row(int sudoku[9][9], int row, int num) {
    for (int col = 0; col < 9; col++) {
        if (sudoku[row][col] == num)
            return 1; // Number is already used in this row
    }
    return 0; // Number is not used in this row
}

int used_in_col(int sudoku[9][9], int col, int num) {
    for (int row = 0; row < 9; row++) {
        if (sudoku[row][col] == num)
            return 1; // Number is already used in this column
    }
    return 0; // Number is not used in this column
}

int used_in_subgrid(int sudoku[9][9], int startRow, int startCol, int num) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (sudoku[row + startRow][col + startCol] == num)
                return 1; // Number is already used in this subgrid
        }
    }
    return 0; // Number is not used in this subgrid
}

int is_safe(int sudoku[9][9], int row, int col, int num) {
    // Check if 'num' is not already used in current row, column, and subgrid
    return !used_in_row(sudoku, row, num) &&
           !used_in_col(sudoku, col, num) &&
           !used_in_subgrid(sudoku, row - row % 3, col - col % 3, num);
}

/**
 * Given a (possibly partially) completed Sudoku grid, this function attempts
 * to solve the Sudoku. The `sudoku` array is changed to contain the solution
 * if one exists. None of the digits in the input grid should be changed.
 *
 * @note: Empty spots in the grid are denoted with 0s.
 *
 * @param sudoku The 9x9 Sudoku grid to be solved.
 * @return 1 if the Sudoku was solved successfully and the `sudoku` array is
 * updated, 0 if it's not possible to solve the Sudoku, and the input `sudoku`
 * array remains unchanged in this case.
 */
int solve_sudoku(int sudoku[9][9]) {
    // Find empty cell
    int row, col;
    if (!find_empty_cell(sudoku, &row, &col))
        return 1; // Sudoku solved successfully

    // Try filling the empty cell with a number
    for (int num = 1; num <= 9; num++) {
        if (is_safe(sudoku, row, col, num)) {
            // If it's safe to place the number, try placing it
            sudoku[row][col] = num;

            // Recursively solve the Sudoku
            if (solve_sudoku(sudoku))
                return 1; // If the Sudoku is solved successfully, return

            // If not solved, backtrack and try a different number
            sudoku[row][col] = 0;
        }
    }

    // If no number works, backtrack
    return 0;
}

// ===========================================================================
// DO NOT CHANGE ANY 'ifndef' AND 'endif' MACROS.
// These macros help ensure your parts of your code does not conflict with the
// automarker. Changing them will result in your code not compiling and you
// receiving a 0 for the entire assignment.
// ===========================================================================
#ifndef __testing__

int main() {
    int sudoku_grid[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    print_sudoku(sudoku_grid);

    int solved = solve_sudoku(sudoku_grid);

    printf("\nsolve_sudoku() return value: %d\n\n", solved);

    /* Look at the handout to see the solution for this! */
    print_sudoku(sudoku_grid);

    return 0;
}

#endif