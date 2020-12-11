#include <iostream>

using namespace std;

void boards_counter(int N, int &counter, int **board);

bool isSafe(int i, int j, int **board, int N, int num);

void delete_num(int i, int j, int **board);

bool allBoardFilled(int **board, int N, int &i, int &j);

void printBoard(int **board,int N);


bool boardIsValid(int **board, int N);

int main() {
    const int N = 4;
    int rows = N, cols = N;
    int **board = new int *[rows];
    board[0] = new int[rows * cols];
    for (int i = 1; i < rows; ++i)
        board[i] = board[0] + i * cols;
    for (int j = 0; j < N; ++j) {
        for (int i = 0; i < N; ++i) {
            if (i == 0) {
                board[i][j] = j+1;
            } else if (j == 0) {
                board[i][j] = i+1;
            } else {
                board[i][j] = 0;
            }
        }
    }
    int counter = 0;
    boards_counter(N, counter, board);
    cout << counter;

    return 0;
}

void boards_counter(int N, int &counter, int **board) {
    int i, j;
    if (allBoardFilled(board, N, i, j)) {
        if (boardIsValid(board,N)) {
            printBoard(board, N);
            counter++;
            return;
        }
        else return;
    }

    for (int num = 1; num <= N; num++) {

        // Check if looks promising
        if (isSafe(i, j, board, N, num)) {

            // Make tentative assignment
            board[i][j] = num;

            // Return, if success
            boards_counter(N, counter, board);

            // Failure, unmake & try again
            delete_num(i, j, board);
        }
    }

    // This triggers backtracking
}

bool boardIsValid(int **board, int N) {
    for (int i = 0; i < N ; ++i) {
        for (int j = 0; j < i ; ++j) {
            if (board[i][j] != board[j][i]){
                return false;
            }
        }
    }
    return true;

}

bool isSafe(int i, int j, int **board, int N, int num) {
    bool is_row = false, is_column = false;
    for (int k = 0; k < N; ++k) {
        if (board[i][k] == num) {
            is_column = true;
            break;
        }
    }
    for (int l = 0; l < N; ++l) {
        if (board[l][j] == num) {
            is_row = true;
            break;
        }
    }
    return !(is_column || is_row);
}

void delete_num(int i, int j, int **board) {
    board[i][j] = 0;
}

bool allBoardFilled(int **board, int N, int &i, int &j) {
    for ( i = 1; i < N; ++i) {
        for ( j = 1; j < N; ++j) {
            if (board[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

void printBoard(int **board,int N){
    for (int i = 0; i < N ; ++i) {
        for (int j = 0; j < N ; ++j) {
            cout << board[i][j];
            if (j == N-1)
            cout << endl;
        }
    }
    cout << "_______"<< endl;
}
