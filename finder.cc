// Omar Lopez
// omarl4574@csu.fullerton.edu
// @omarl4574

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// the files that grab the board and words
const string BOARD_FILE = "board.txt";
const string WORDS_FILE = "words.txt";

// Structure for storing the x and y cords of the words
struct Coords {
  int x;
  int y;
};

// checks horizontal direction
bool SearchHorizontal(const vector<vector<char>>& board, const string& word,
                      int row, int col, bool forward, vector<Coords>& coords) {
  // if forwards is true direction is 1 and if false the direction is -1
  int direction{forward ? 1 : -1};

  // checks if the word could be in the bounds of the board
  if (col + direction * (word.length() - 1) < 0 ||
      col + direction * (word.length() - 1) >= board[row].size())
    return false;

  // checks to see if the character in the board equal to the characters in the
  // word
  for (int i = 0; i < word.length(); ++i) {
    if (board[row][col + (direction * i)] != word[i]) return false;
    Coords coordinates;
    coordinates.x = row;
    coordinates.y = col + (direction * i);
    coords.push_back(coordinates);
  }

  return true;
}

// checks the vertical direction
bool SearchVertical(const vector<vector<char>>& board, const string& word,
                    int row, int col, bool forward, vector<Coords>& coords) {
  // if forwards is true direction is 1 and if false the direction is -1
  int direction{forward ? 1 : -1};

  // checks if the word could be in the bounds of the board
  if (row + direction * (word.length() - 1) < 0 ||
      row + direction * (word.length() - 1) >= board.size())
    return false;

  // checks to see if the character in the board equal to the characters in the
  // word
  for (int i = 0; i < word.length(); ++i) {
    if (board[row + (direction * i)][col] != word[i]) return false;
    Coords coordinates;
    coordinates.x = row + (direction * i);
    coordinates.y = col;
    coords.push_back(coordinates);
  }

  return true;
}

bool TopLeftToBottomRight(const vector<vector<char>>& board, const string& word,
                          int row, int col, bool forward,
                          vector<Coords>& coords) {
  // if forwards is true direction is 1 and if false the direction is -1
  int direction{forward ? 1 : -1};

  // checks if the word could be in the bounds of the board
  if (row + direction * (word.length() - 1) < 0 ||
      row + direction * (word.length() - 1) >= board.size() ||
      col + direction * (word.length() - 1) < 0 ||
      col + direction * (word.length() - 1) >= board[row].size())
    return false;

  // checks to see if the character in the board equal to the characters in the
  // word
  for (int i = 0; i < word.length(); i++) {
    if (board[row + (direction * i)][col + (direction * i)] != word[i])
      return false;
    Coords coordinates;
    coordinates.x = row + (direction * i);
    coordinates.y = col + (direction * i);
    coords.push_back(coordinates);
  }

  return true;
}

// checks from the top right to the bottom left in the diagonal directions
bool TopRightToBottomLeft(const vector<vector<char>>& board, const string& word,
                          int row, int col, bool forward,
                          vector<Coords>& coords) {
  // if forwards is true direction is 1 and if false the direction is -1
  int direction{forward ? 1 : -1};

  // checks if the word could be in the bounds of the board
  if (row + direction * (word.length() - 1) < 0 ||
      row + direction * (word.length() - 1) >= board.size() ||
      row - direction * (word.length() - 1) < 0 ||
      row - direction * (word.length() - 1) <= board.size())
    return false;

  // checks to see if the character in the board equal to the characters in the
  // word
  for (int i = 0; i < word.length(); ++i) {
    if (board[row + (direction * i)][col - (direction * i)] != word[i])
      return false;
    Coords coordinates;
    coordinates.x = row - (direction * i);
    coordinates.y = col + (direction * i);
    coords.push_back(coordinates);
  }

  return true;
}

// function that hold both of the diagonal functions together
bool SearchDiagonal(const vector<vector<char>>& board, const string& word,
                    int row, int col, bool forward, vector<Coords>& coords) {
  return TopRightToBottomLeft(board, word, row, col, forward, coords) ||
         TopLeftToBottomRight(board, word, row, col, forward, coords);
}

// checks rather the horizonatal direction or vertical direction
bool SearchBoard(const vector<vector<char>>& board, const string& word, int x,
                 int y, bool forward, bool isDiagonal, vector<Coords>& coords) {
  if (isDiagonal) {
    return SearchDiagonal(board, word, x, y, forward, coords);
  } else {
    return SearchHorizontal(board, word, x, y, forward, coords) ||
           SearchVertical(board, word, x, y, forward, coords);
  }
}

// finds all the words in the board
void SolveBoard(const vector<vector<char>>& board,
                const vector<string>& words) {
  for (const string& word : words) {
    bool found = false;
    vector<Coords> coords;

    for (int x = 0; x < board.size(); x++) {
      for (int y = 0; y < board[x].size(); y++) {
        // checks for all varitations of how to find words in the board
        // if any are true its print the x and y cords to the console
        if (SearchBoard(board, word, x, y, true, false, coords) ||
            SearchBoard(board, word, x, y, false, false, coords) ||
            SearchBoard(board, word, x, y, true, true, coords) ||
            SearchBoard(board, word, x, y, false, true, coords)) {
          cout << word << " Coordinates are: \n";
          for (const Coords& coord : coords) {
            cout << "(" << coord.x + 1 << ", " << coord.y + 1 << ")" << endl;
          }
          cout << "================================" << endl;
          found = true;
          break;
        }
      }
      // if found early it breaks out of the for loop to start searching for the
      // next word
      if (found) break;
    }

    // if not found then prints '{word} not found'
    if (!found) cout << word << " not found" << endl;
  }
}

int main() {
  // checks if the 'words.txt' file exists
  ifstream wordsFile(WORDS_FILE);
  if (!wordsFile.is_open()) {
    cerr << "Error opening words.txt" << endl;
    return 1;
  }

  // puts the words from the 'words.txt' file in the words vector
  vector<string> words;
  string word;

  while (wordsFile >> word) {
    transform(word.begin(), word.end(), word.begin(), ::toupper);
    words.push_back(word);
  }
  wordsFile.close();

  // checks if the 'board.txt' file exists
  ifstream boardFile(BOARD_FILE);
  if (!boardFile.is_open()) {
    cerr << "Error opening board.txt" << endl;
    return 1;
  }

  // puts the board from the 'board.txt' in the board vector
  vector<vector<char>> board;
  string line;
  while (getline(boardFile, line)) {
    vector<char> row(line.begin(), line.end());
    board.push_back(row);
  }
  boardFile.close();

  // runs the algorithm to solve the word puzzle
  SolveBoard(board, words);

  return 0;
}
