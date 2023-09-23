// Omar Lopez
// omarl4574@csu.fullerton.edu
// @omarl4574

#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<vector<char>> SetUpBoard(int amount_rows, int amount_cols, string letters){
    vector<vector<char>> board(amount_rows, vector<char>(amount_cols));

    int letter_index = 0;
    for(int rows = 0; rows < amount_rows; rows++){
        for(int cols = 0; cols < amount_cols; cols++){
            board[rows][cols] = letters[letter_index];
            letter_index++;
        }
    }
    return board;
}

void PrintBoard(vector<vector<char>> board, int amount_rows, int amount_cols){
    for(int rows = 0; rows < amount_rows; rows++){
        for(int cols = 0; cols < amount_cols; cols++){
            cout << board[rows][cols] << " ";
        }
        cout << "\n";
    }
}

int main(){
    int num_rows{0};
    int num_cols{0};

    cout << "Enter the amount of rows your board has: ";
    cin >> num_rows;

    cout << "Enter the amount of columns your board has: ";
    cin >> num_cols;

    string letters{"qwerty"};
    cout << "Enter the board all horizontally: ";
    cin >> letters;

    vector<vector<char>> board = SetUpBoard(num_rows, num_cols, letters);
    PrintBoard(board, num_rows, num_cols);

    return 0;
}
