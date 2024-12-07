// first coding project: connect four xxxx

// connect four game board: 6 rows by 7 columns

/*         A B C D E F G
        1  - - - - - - -
        2  - - - - - - -
        3  - - - - - - -
        4  - - - - - - -
        5  - - - - - - -
        6  - - - - - - -    
        
        rules of the game:
        1. 2 players
        2. players have to get 4-in-a-row of their own color (using red/yellow)
            - can get 4-in-a-row either diagonally, vertically, or horizontally
        3. players take turns dropping in pieces
        4. first player to get 4-in-a-row wins
        5. if all pieces are used and no win is detected, then there is a tie  */

/*  think about coding:

    data structures: 2d array (6 rows by 7 columns)
    user input for 2 players
    storing player moves in 2d array (ex. 0 = empty space, 1 = p1 piece, 2 = p2 piece)

    ** FOR LATER, do i want to use graphics? yes, but how do i implement them? **

*/

#include <iostream>
#include <vector>

using namespace std;

const int ROWS = 6;
const int COLS = 7;

char gameBoard[6][7] = {}; // initialize everything on game board to 0 (AKA empty)

void initializeBoard() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            gameBoard[i][j] = ' ';
        }
    }
}

void displayBoard() {
    cout << "\n";

    cout << "   "; // resolve space gap
    for (int col = 0; col < COLS; col++) {
        cout << col << " ";
    }

    cout << "\n";

    for (int i = 0; i < ROWS; i++) {
        cout << i << " ";
        for (int j = 0; j < COLS; j++) {
           cout <<  "|" << gameBoard[i][j];
        }
        cout << "|\n";
    }

    cout << "\n";
}

int playerInput(int player) {
    int colValue;
    cout << "Player " << player << ", choose a column 0 through 6: ";
    cin >> colValue;
    cout << "\n";

    bool recheck = false;

    while (recheck == false) {
        // if player selects column that is out of bounds or input fails
        if (colValue < 0 || colValue > 6 || cin.fail()) {
            cin.clear(); // clear input
            cin.ignore(100, '\n'); // ignore a max of 100 characters and up until '\n' 
            cout << "You chose an invalid column :( Choose a column 0 through 6: ";
            cin >> colValue;
            // need to address case if player still inputs an invalid value
        } else if (gameBoard[0][colValue] != ' ') { // if column is full
            cout << "Column "<< colValue << " is full :( Try another: ";
            cin >> colValue;
        } else {
            return colValue;
            break;
        }
    }

    return -1; // didn't work
    
}

int dropToken(int colValue, int player) {
    char p1Token = 'X';
    char p2Token = 'O';
    
    for (int i = ROWS - 1; i >= 0; i--) {
        if (gameBoard[i][colValue] == ' ') { // check if position on board is empty
            // if empty insert token according to player
            if (player == 1) {
                gameBoard[i][colValue] = p1Token;
            } else if (player == 2) {
                gameBoard[i][colValue] = p2Token;
            }
            return i;
        }
       
    }
    return -1;
}

// helper functions to check for a win
bool verticalWin(int row, int col, char pToken) {
    int count = 1; // include token that was just placed

    // check above
    int aboveRow = row - 1;
    while (aboveRow < ROWS && gameBoard[aboveRow][col] == pToken) {
        aboveRow--;
        count++;
    }

    // check below
    int belowRow = row + 1;
    while (belowRow >= 0 && gameBoard[belowRow][col] == pToken) {
        belowRow++;
        count++;
    }

    return count >= 4;
}

bool horizontalWin(int row, int col, char pToken) {
    int count = 1; // include token that was just placed
    // check left
    int leftCol = col - 1;
    while (leftCol >= 0 && gameBoard[row][leftCol] == pToken) {
        leftCol--;
        count++;
    }

    // check right
    int rightCol = col + 1;
    while (rightCol < COLS && gameBoard[row][rightCol] == pToken) {
        rightCol++;
        count++;
    }

    return count >= 4;
}

bool leftDiagonalWin(int row, int col, char pToken) { // / (top right to bottom left)
    int count = 1;

    // checking below left diagonal
    int belowRow = row + 1;
    int leftCol = col - 1;

    while (belowRow < ROWS && leftCol < COLS && gameBoard[belowRow][leftCol] == pToken) {
        belowRow++;
        leftCol--;
        count++;
    }

    // checking above left diagonal
    int aboveRow = row - 1;
    int rightCol = col + 1;

    while (aboveRow >= 0 && rightCol >= 0 && gameBoard[aboveRow][rightCol] == pToken) {
        aboveRow--;
        rightCol++;
        count++;
    }

    return count >= 4;
}

bool rightDiagonalWin(int row, int col, char pToken) { // \ (top left to bottom right)
    int count = 1;

    // checking below right diagonal
    int belowRow = row + 1;
    int rightCol = col + 1;

    while (belowRow < ROWS && rightCol < COLS && gameBoard[belowRow][rightCol] == pToken) {
        belowRow++;
        rightCol++;
        count++;
    }

    // checking above right diagonal
    int aboveRow = row - 1;
    int leftCol = col - 1;

    while (aboveRow >= 0 && leftCol >= 0 && gameBoard[aboveRow][leftCol] == pToken) {
        aboveRow--;
        leftCol--;
        count++;
    }

    return count >= 4;
}

// function to check if board is full
bool boardFull() {
    for (int i = 0; i < COLS; i++) {
        if (gameBoard[0][i] == ' ') {
            return false;
        }
    }
    return true;
}

int main() {
    // game setup
    initializeBoard();

    bool gameWon = false;

    int currentPlayer = 1;
    char tokens[] = {'X', 'O'};

    displayBoard(); // display before gameplay

    char replay = 'Y';

    while (replay == 'Y' || replay == 'y') {

        while (gameWon == false) {

            // current position and player
            int selectedCol = playerInput(currentPlayer);
            int currentRow = dropToken(selectedCol, currentPlayer);
            // cout << "Player " << currentPlayer << " (row: " << currentRow << " column: " << selectedCol << ")\n";
            char pToken = tokens[currentPlayer - 1];

            displayBoard(); // display during gameplay

            // check to see if the game is won or board is full
            if (verticalWin(currentRow, selectedCol, pToken) || horizontalWin(currentRow, selectedCol, pToken) || rightDiagonalWin(currentRow, selectedCol, pToken) || leftDiagonalWin(currentRow, selectedCol, pToken)) {
                gameWon = true;
                cout << "Player " << currentPlayer << " wins!\n\n";
                // cout << "\n";
            } 

            if (boardFull()) {
                cout << "It's a draw!\n\n";
                // cout << "\n";
                break;
            }

            // switching players
            if (currentPlayer == 1) {
                currentPlayer = 2;
            } else {
                currentPlayer = 1;
            }

        }

        cout << "Do you want to play again? Enter Y or N: ";
        cin >> replay;
        cout << "\n";

        // replay loop from chatGPT
        while (replay != 'Y' && replay != 'y' && replay != 'N' && replay != 'n') {
            cout << "Invalid input. Please enter Y or N: ";
            cin >> replay;
            cout << "\n";
        }

        if (replay == 'Y' || replay == 'y') {
            gameWon = false;
            initializeBoard();
            cout << "Get ready, now it's Player " << currentPlayer << "'s turn!\n\n";
        }
    }

    cout << "Thanks for playing Connect Four :)\n";

    return 0;
}