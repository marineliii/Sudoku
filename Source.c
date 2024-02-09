#define _CRT_SECURE_NO_WARNINGS



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define N 9 // size of the grid
#define EMPTY 0 // empty cell
#define TRUE 1 // boolean true
#define FALSE 0 // boolean false

// function prototypes
void print_grid(int grid[N][N]); // prints the grid
int is_valid(int grid[N][N], int row, int col, int num); // checks if a number is valid for a cell
int solve_grid(int grid[N][N]); // solves the grid using backtracking
void generate_grid(int grid[N][N], int level); // generates a grid with a given level of difficulty
void input_grid(int grid[9][9]);
bool insert_value(int grid[9][9], int row, int col, int value);
void test_input_grid();

// main function
int main()
{
    int grid[N][N]; // the sudoku grid
    int level; // the level of difficulty
    int choice; // the user's choice

    srand(time(NULL)); // initialize random seed

    printf("Welcome to the sudoku game!\n");
    printf("Please choose a level of difficulty (1-5):\n");
    printf("1. Easy\n");
    printf("2. Medium\n");
    printf("3. Hard\n");
    printf("4. Very hard\n");
    printf("5. Extreme\n");
    printf("6 . Input custum grid\n");
    scanf("%d", &level); // get the user's input

    if (level >= 1 && level <= 5) {
        generate_grid(grid, level); // generate a grid with the chosen level
        print_grid(grid); // print the grid
    }
    else {
        test_input_grid(grid);  // input coustom grid to test it on
    }

    
    

    printf("Do you want to see the solution? (1-Yes, 0-No)\n");
    scanf("%d", &choice); // get the user's input

    if (choice == 1) // if the user wants to see the solution
    {
        if (solve_grid(grid) == TRUE) // if the grid is solvable
        {
            printf("The solution is:\n");
            print_grid(grid); // print the solution
        }
        else // if the grid is not solvable
        {
            printf("The grid is not solvable.\n");
        }
    }

    printf("Thank you for playing!\n");
    return 0;
}

// function to print the grid
void print_grid(int grid[N][N])
{
    int i, j;
    for (i = 0; i < N; i++) // for each row
    {
        for (j = 0; j < N; j++) // for each column
        {
            printf("%d ", grid[i][j]); // print the cell value
        }
        printf("\n"); // print a new line
    }
}

// function to check if a number is valid for a cell
int is_valid(int grid[N][N], int row, int col, int num)
{
    int i, j;
    int row_start = (row / 3) * 3; // the starting row of the 3x3 subgrid
    int col_start = (col / 3) * 3; // the starting column of the 3x3 subgrid

    for (i = 0; i < N; i++) // for each row
    {
        if (grid[i][col] == num) // if the number is already in the column
        {
            return FALSE; // return false
        }
    }

    for (j = 0; j < N; j++) // for each column
    {
        if (grid[row][j] == num) // if the number is already in the row
        {
            return FALSE; // return false
        }
    }

    for (i = row_start; i < row_start + 3; i++) // for each row in the subgrid
    {
        for (j = col_start; j < col_start + 3; j++) // for each column in the subgrid
        {
            if (grid[i][j] == num) // if the number is already in the subgrid
            {
                return FALSE; // return false
            }
        }
    }

    return TRUE; // return true
}

// function to solve the grid using backtracking
int solve_grid(int grid[N][N])
{
    int i, j, num;
    int row = -1; // the row of the empty cell
    int col = -1; // the column of the empty cell
    int found = FALSE; // flag to indicate if an empty cell is found

    for (i = 0; i < N; i++) // for each row
    {
        for (j = 0; j < N; j++) // for each column
        {
            if (grid[i][j] == EMPTY) // if the cell is empty
            {
                row = i; // set the row
                col = j; // set the column
                found = TRUE; // set the flag
                break; // break the inner loop
            }
        }
        if (found == TRUE) // if an empty cell is found
        {
            break; // break the outer loop
        }
    }

    if (found == FALSE) // if no empty cell is found
    {
        return TRUE; // return true (the grid is solved)
    }

    for (num = 1; num <= N; num++) // for each number from 1 to 9
    {
        if (is_valid(grid, row, col, num) == TRUE) // if the number is valid for the cell
        {
            grid[row][col] = num; // place the number in the cell
            if (solve_grid(grid) == TRUE) // if the grid can be solved with this number
            {
                return TRUE; // return true
            }
            grid[row][col] = EMPTY; // backtrack and remove the number from the cell
        }
    }

    return FALSE; // return false (the grid cannot be solved)
}

// function to generate a grid with a given level of difficulty
void generate_grid(int grid[N][N], int level)
{
    int i, j, k, num;
    int count = 0; // the number of cells to be filled
    int max_count = 0; // the maximum number of cells to be filled
    int row, col; // the row and column of the cell to be filled

    // initialize the grid with empty cells
    for (i = 0; i < N; i++) // for each row
    {
        for (j = 0; j < N; j++) // for each column
        {
            grid[i][j] = EMPTY; // set the cell to empty
        }
    }

    // determine the maximum number of cells to be filled based on the level of difficulty
    switch (level)
    {
    case 1: // easy
        max_count = 40;
        break;
    case 2: // medium
        max_count = 30;
        break;
    case 3: // hard
        max_count = 25;
        break;
    case 4: // very hard
        max_count = 20;
        break;
    case 5: // extreme
        max_count = 15;
        break;
    default: // invalid level
        printf("Invalid level of difficulty.\n");
        return;
    }

    // fill the grid with random numbers until the maximum count is reached
    while (count < max_count)
    {
        row = rand() % N; // generate a random row
        col = rand() % N; // generate a random column
        num = rand() % N + 1; // generate a random number from 1 to 9

        if (grid[row][col] == EMPTY && is_valid(grid, row, col, num) == TRUE) // if the cell is empty and the number is valid
        {
            grid[row][col] = num; // place the number in the cell
            count++; // increment the count
        }
    }

    // solve the grid using backtracking
    if (solve_grid(grid) == FALSE) // if the grid cannot be solved
    {
        printf("The grid cannot be solved.\n");
        return;
    }

    // remove some numbers from the grid to create the puzzle
    for (k = 0; k < max_count; k++) // for each cell to be removed
    {
        row = rand() % N; // generate a random row
        col = rand() % N; // generate a random column

        if (grid[row][col] != EMPTY) // if the cell is not empty
        {
            grid[row][col] = EMPTY; // remove the number from the cell
        }

    }
    // A function to input a custom grid from the standard input stream
    
}
void input_grid(int grid[9][9]) {
    // Declare a variable to store the input value
    int value;
    // Loop through the grid positions
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            // Read the input value using scanf
            scanf("%d", &value);
            // Insert the value into the grid using the insert_value function
            insert_value(grid, i, j, value);
        }
    }
}

        
// A function to create an empty sudoku grid of size 9x9
void create_grid(int grid[9][9]) {
    // Initialize all the elements to zero
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            grid[i][j] = 0;
        }
    }
}


// A function to insert a value into the sudoku grid at a given position
// Returns true if the insertion is successful, false otherwise
bool insert_value(int grid[9][9], int row, int col, int value) {
    // Check if the position is valid
    if (row < 0 || row > 8 || col < 0 || col > 8) {
        return false;
    }
    // Check if the value is valid
    if (value < 1 || value > 9) {
        return false;
    }
    // Check if the position is already filled
    if (grid[row][col] != 0) {
        return false;
    }
    // Check if the value is already present in the same row, column or 3x3 box
    for (int i = 0; i < 9; i++) {
        if (grid[row][i] == value || grid[i][col] == value) {
            return false;
        }
    }
    int box_row = (row / 3) * 3;
    int box_col = (col / 3) * 3;
    for (int i = box_row; i < box_row + 3; i++) {
        for (int j = box_col; j < box_col + 3; j++) {
            if (grid[i][j] == value) {
                return false;
            }
        }
    }
    // If all the checks are passed, insert the value and return true
    grid[row][col] = value;
    return true;
}

void test_input_grid(int grid [9][9])
{
    
    create_grid(grid);
    printf("Grid before input\n");
    print_grid(grid);
    printf("Input custum grid\n");
    input_grid(grid);
    printf("Grid after input\n");
    print_grid(grid);
}
