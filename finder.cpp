// Omar Lopez
// omarl4574@csu.fullerton.edu
// @omarl4574

#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

/* The function that set up the board as a 2D array to then sort through later
and find all the words */
vector<vector<string>> SetUpBoard(int amount_rows, int amount_cols,
                                  string letters) {
  vector<vector<string>> board(amount_rows, vector<string>(amount_cols));

  int letter_index = 0;
  for (int rows = 0; rows < amount_rows; rows++) {
    for (int cols = 0; cols < amount_cols; cols++) {
      board[rows][cols] = letters[letter_index];
      letter_index++;
    }
  }
  return board;
}

// Prints the cross word puzzle board
void PrintBoard(vector<vector<string>> board) {
  for (int rows = 0; rows < board.size(); rows++) {
    for (int cols = 0; cols < board[rows].size(); cols++) {
      cout << board[rows][cols] << " ";
    }
    cout << "\n";
  }
}

/* asks the user for all the words they need to find in the cross word puzzle
they entered and stores every word they entered in a vector called words */

vector<string> GetAllWords() {
  vector<string> words;

  while (true) {
    cout << "Enter words (type 'quit' exit): ";
    string word;
    cin >> word;

    if (word == "quit") {
      break;
    }

    words.push_back(word);
  }

  return words;
}

// prints all the words the user has entered from the words vector
void PrintWords(vector<string> words) {
  for (int i = 0; i < words.size(); i++) {
    cout << words[i] << ", ";
  }
  cout << "\n";
}

pair<vector<vector<int>>, int> CheckRight(vector<vector<string>> board,
                                          vector<string> words, int curr_word) {
  string temp_word;
  vector<vector<int>> indexs;
  vector<int> index_pairs;
  pair<vector<vector<int>>, int> res;

  for (int rows = 0; rows < board.size(); rows++) {
    for (int cols = 0; cols < board[rows].size(); cols++) {
      if (begin(board[rows][cols]) != begin(words[curr_word])) {
        temp_word = "";
        index_pairs.clear();
      }
    }
  }
  res.first = indexs;
  res.second = curr_word;
  return res;
}
/*the function which will take in the board and the list of words and find all
the words and return a list of indexs where the words have been found*/
void FindWords(vector<vector<string>> board, vector<string> words) {
  vector<vector<vector<int>>> indexs;
  int current_word{0};

  pair right_res{CheckRight(board, words, current_word)};
  current_word = right_res.second;
}

int main() {
  int num_rows{0};
  int num_cols{0};

  cout << "Enter the amount of rows your board has: ";
  cin >> num_rows;

  cout << "Enter the amount of columns your board has: ";
  cin >> num_cols;

  string letters{"qwerty"};
  cout << "Enter the board all horizontally: ";
  cin >> letters;

  vector<vector<string>> board{SetUpBoard(num_rows, num_cols, letters)};
  vector<string> words{GetAllWords()};

  return 0;
}