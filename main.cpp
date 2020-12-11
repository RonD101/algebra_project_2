#include <iostream>
#include <string.h>
#include <memory>
#include <vector>

#define MAX_CHARS 256
using namespace std;
using std::vector;
using std::string;

void boards_counter(vector<string> &matrices, int N, int &counter, int **board);
bool allBoardFilled(int **board, int N, int &i, int &j);
bool isSafe(int i, int j, int **board, int N, int num);
bool checkPermute(const string& board_a, const string& board_b);
bool areIsomorphic(string str1, string str2);
void delete_num(int i, int j, int **board);
bool boardIsValid(int **board, int N);
void printBoard(int **board,int N);

int main() {

    // This code produces all the groups including the isomorphism ones.
    // i.e for N=4 we get 4 groups, but 3 of them are basically the same.
    // We need to check for permutations for each pair of matrices we get.
    // Than "delete" all of them except for 1.
    const int N = 4;
    vector<string> matrices;
    int rows = N, cols = N;
    int **board = new int *[rows];
    board[0] = new int[rows * cols];

    for (int i = 1; i < rows; ++i)
        board[i] = board[0] + i * cols;
    for (int j = 0; j < N; ++j) {
        for (int i = 0; i < N; ++i) {
            if (i == 0)
                board[i][j] = j+1;
            else if (j == 0)
                board[i][j] = i+1;
            else
                board[i][j] = 0;
        }
    }

    int counter = 0;
    boards_counter(matrices, N, counter, board);
    for (int i = 0; i < matrices.size(); ++i) {
        for (int j = i; j < matrices.size(); ++j) {
            if(i != j) {
                if (checkPermute(matrices[i], matrices[j]))
                    counter--;
            }
        }
    }
    cout << counter << endl;
    for (int k = 0; k < N; ++k)
        delete [] board[k];

    delete [] board;
    return 0;
}

void boards_counter(vector<string> &matrices, int N, int &counter, int **board) {

    int i, j;
    if (allBoardFilled(board, N, i, j)) {
        if (boardIsValid(board,N)) {
            printBoard(board, N);
            counter++;
            string temp;
            for (int k = 1; k < N; ++k) {
                for (int l = 1; l < N; ++l)
                temp = temp + std::to_string(board[k][l]);
            }
            matrices.push_back(temp);
            return;
        }
        else return;
    }

    for (int num = 1; num <= N; num++) {
        if (isSafe(i, j, board, N, num)) {
            board[i][j] = num;
            boards_counter(matrices, N, counter, board);
            delete_num(i, j, board);
        }
    }
}

bool boardIsValid(int **board, int N) {

    for (int c = 0; c < N; ++c) {
        for (int s = 0; s < N; ++s) {
            for (int t = 0; t < N; ++t) {
                int k = board[c][board[s][t]-1];
                int j = board[board[c][s]-1][t];
                if(k != j)
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

    for (i = 1; i < N; ++i) {
        for (j = 1; j < N; ++j) {
            if (board[i][j] == 0)
                return false;
        }
    }
    return true;
}

bool checkPermute(const string& board_a, const string& board_b) {

    if(board_a == board_b)
        return false;
    bool k = areIsomorphic(board_a, board_b);
    return k;
}

bool areIsomorphic(string str1, string str2) {

    int m = str1.length(), n = str2.length();
    if (m != n)
        return false;

    bool marked[MAX_CHARS] = {false};
    int map[MAX_CHARS];
    memset(map, -1, sizeof(map));

    // Process all characters one by on
    for (int i = 0; i < n; i++) {
        if (map[str1[i]] == -1) {
            if (marked[str2[i]] == true)
                return false;

            marked[str2[i]] = true;
            map[str1[i]] = str2[i];
        }

        else if (map[str1[i]] != str2[i])
            return false;
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