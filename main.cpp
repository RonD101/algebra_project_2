#include <iostream>
#include <vector>
using std::vector;

bool inColumn(int col, int num, int N);
bool inRow(int row, int num, int N);

int main() {
    vector<vector<int>> matrix;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}

bool inColumn(vector<vector<int>>& matrix, int col, int num, int N) {
    for (int row = 0; row < N; row++)
        if (matrix[row][col] == num)
            return true;
    return false;
}

bool inRow(vector<vector<int>>& matrix, int row, int num, int N) {
    for (int col = 0; col < N; col++)
        if (matrix[row][col] == num)
            return true;
    return false;
}