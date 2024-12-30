#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

int StepDown(int index, int height);
int StepRight(int index, int width);
int MaxPathValue(int index, int pathStart, int boardSize, int** board);
int maximumPath(int** board, int size);
void printOptimalPath(int** board, int* movementPath, int size, int maximumIndex);
void DP(int** board, int size);

// constant variable
const int MIN = -2147483648;  // Most negative 32-bit integer

// function to get the index of the cell below
int StepDown(int index, int height) {
    int row = index / height + 1;
    int column = index % height;

    if (row >= height) {
        return -1;
    }
    
    return row * height + column;
}

// function to get the index of the cell in the right 
int StepRight(int index, int width) {
    int row = index / width;
    int column = index % width + 1;
    
    if (column >= width) {
        return -1;
    }
    
    return row * width + column;
}

// function to find the maximum path value
int MaxPathValue(int index, int pathStart, int boardSize, int** board) {
    
    // outside
    if (index == -1) {
        return 0;
    }

    // location of cell index 
    int row = index / boardSize;
    int column = index % boardSize;

    if (pathStart == 1) {
        int indexDown = StepDown(index, boardSize);
        int indexRight = StepRight(index, boardSize);
        
        int down = board[column][row] + MaxPathValue(indexDown, 1, boardSize, board);
        int right = board[column][row] + MaxPathValue(indexRight, 1, boardSize, board);
        
        return std::max(right, down);
    } 
    
    else {
        int indexDown = StepDown(index, boardSize);
        int indexRight = StepRight(index, boardSize);
        
        int down_withCurrent = board[column][row] + MaxPathValue(indexDown, 1, boardSize, board);
        int down_withoutCurrent = MaxPathValue(indexDown, 0, boardSize, board);
        
        int right_withCurrent = board[column][row] + MaxPathValue(indexRight, 1, boardSize, board);
        int right_withoutCurrent = MaxPathValue(indexRight, 0, boardSize, board);

        
        return std::max(down_withCurrent, std::max(right_withCurrent, std::max(down_withoutCurrent, right_withoutCurrent)));
    }
}

// function to find the maximum value from the two starts
int maximumPath(int** board, int size) {
    int value_startA = MaxPathValue(0, 0, size, board);
    int value_startB = MaxPathValue(0, 1, size, board);
    
    return std::max(value_startA, value_startB);
}

// print solution 
void printOptimalPath(int** board, int* movementPath, int size, int maximumIndex) {
    int index = maximumIndex;
    int pathDirection = movementPath[maximumIndex];

    while (pathDirection != 0) {
        pathDirection = movementPath[index];

        int Y_index = index / size;
        int X_index = index % size;

        std::cout << board[X_index][Y_index] << std::endl;

        int down = StepDown(index, size);
        int right = StepRight(index, size);

        if (pathDirection == 1) {
            index = right;
        } 
        else if (pathDirection == 2) {
            index = down;
        }
    }
}

// dynamic programming 
void DP(int** board, int size) {
    int boardSize = size * size; // # of cells in the grid
    int endingIndex = boardSize - 1; // index of the last cell in grid 
    int* movementPath = new int[boardSize]; // memo to store the path movement of each cell
    int** values = new int*[boardSize]; // memo to store values of each cell

    for (int i = 0; i < boardSize; ++i) {
        values[i] = new int[2];
    }

    // last cell location
    int lastVertical = endingIndex / size;
    int lastHorizontal = endingIndex % size;

    values[endingIndex][0] = MIN;
    values[endingIndex][1] = board[lastHorizontal][lastVertical];

    for (int index = endingIndex - 1; index >= 0; --index) {
        
        int Y_index = index / size;
        int X_index = index % size;

        values[index][0] = MIN;
        values[index][1] = board[X_index][Y_index];

        int down = StepDown(index, size);
        int right = StepRight(index, size);
        

        if (down != -1 &&  right != -1) {
            
            bool RightLarger0 = values[down][0] < values[right][0];
            bool RightLarger1 = values[down][1] < values[right][1];

            int value0 = std::max(values[down][0], values[right][0]);
            int value1 = std::max(values[down][1], values[right][1]);
            
            values[index][1] += std::max(0, value1);
            
            if (value1 > 0) {
               if (RightLarger1) {
                   movementPath[index] = 1;
                   
               } 
               else {
                   movementPath[index] = 2;
                   
               }
            }
            
            values[index][0] += std::max(0, std::max(value0, value1));
        }
        
        else if (right == -1) {
            
            values[index][1] += std::max(0, values[down][1]);
            
            if (values[down][1] > 0) {
                movementPath[index] = 2;
            }
            
            values[index][0] += std::max(0, std::max(values[down][1], values[down][0]));
        } 
        
        else {
            if (values[right][1] > 0) {
                movementPath[index] = 1;
            }
            
            values[index][0] += std::max(0, std::max(values[right][1], values[right][0]));
            values[index][1] += std::max(0, values[right][1]);
        }
    }

    // to find the maximum total value of all paths

    int maximumIndex = -1;
    int maximum = MIN;
    
    for (int j = 0; j < boardSize; ++j) {
        for (int k = 0; k < 2; ++k) {
            if (values[j][k] >= maximum) {
                maximum = values[j][k];
                maximumIndex = j;
            }
        }
    }

    printOptimalPath(board, movementPath, size, maximumIndex);

    for (int index = 0; index < boardSize; ++index) {
        delete[] values[index];
    }
    
    delete[] movementPath;
    delete[] values;
}

//main
int main() {
    // input size (board = N*N)
    int N;
    std::cin >> N;

    int** board = new int*[N];
    
    for (int index = 0; index < N; ++index) {
        board[index] = new int[N];
    }

    // Read the matrix elements in the specified format
    char comma;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cin >> board[i][j]; // values
            if (j < N - 1) {
                std::cin >> comma; // comma
                if (comma != ',') {
                    return 1; 
                }
            }
        }
    }

    DP(board, N);


    for (int i = 0; i < N; ++i) {
        delete[] board[i];
    }
    
    delete[] board;

    return 0;
}
