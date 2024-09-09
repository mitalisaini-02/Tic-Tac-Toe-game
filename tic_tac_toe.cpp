#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()

using namespace std;

// To draw the Tic-Tac-Toe board
void draw_a_board(const vector<vector<char>>& board) {
    cout << "  0 1 2\n";
    for (int i = 0; i < 3; ++i) {
        cout << i << ' ';
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j] << ' ';
        }
        cout << '\n';
    }
}

// To check for a win
bool check_the_win_condition(const vector<vector<char>>& board, char player) {
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
    return false;
}

// To check for a draw
bool checkDraw(const vector<vector<char>>& board) {
    for (const auto& row : board) {
        for (char cell : row) {
            if (cell == ' ') return false;
        }
    }
    return true;
}

// To get available moves
vector<pair<int, int>> getAvailableMoves(const vector<vector<char>>& board) {
    vector<pair<int, int>> moves;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') {
                moves.push_back({i, j});
            }
        }
    }
    return moves;
}

// Function to make the best move for the computer
void computerMove(vector<vector<char>>& board, char computerPlayer, char humanPlayer) {
    vector<pair<int, int>> bestMoves;
    int bestScore = -1000; // Computer's best score

    // Check all available moves
    vector<pair<int, int>> moves = getAvailableMoves(board);
    for (const auto& move : moves) {
        int row = move.first;
        int col = move.second;
        board[row][col] = computerPlayer;
        
        int score = 0;
        if (check_the_win_condition(board, computerPlayer)) {
            score = 10;
        } else if (check_the_win_condition(board, humanPlayer)) {
            score = -10;
        } else {
            score = 0; // Simple AI, we only handle immediate win/loss here
        }
        
        board[row][col] = ' '; // Undo the move
        
        // Update the best move
        if (score > bestScore) {
            bestScore = score;
            bestMoves.clear();
            bestMoves.push_back(move);
        } else if (score == bestScore) {
            bestMoves.push_back(move);
        }
    }

    // Make a move among the best moves
    if (!bestMoves.empty()) {
        srand(static_cast<unsigned>(time(0))); // Seed the random number generator
        int index = rand() % bestMoves.size();
        int row = bestMoves[index].first;
        int col = bestMoves[index].second;
        board[row][col] = computerPlayer;
        cout << "Computer (" << computerPlayer << ") plays at " << row << ' ' << col << '\n';
    }
}

// Function to handle player move
bool makeMove(vector<vector<char>>& board, char player) {
    int row, col;
    while (true) {
        cout << "Player " << player << ", enter row (0-2) and column (0-2),( by using space between them):";
        cin >> row >> col;

        if (cin.fail() || row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ') {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid move. Please try again.\n";
        } else {
            board[row][col] = player;
            return true;
        }
    }
}

// Function to play a game of Tic-Tac-Toe
void playGame(bool vsComputer) {
    vector<vector<char>> board(3, vector<char>(3, ' '));
    char player = 'X';
    char computerPlayer = 'O';
    
    cout << "Welcome to Tic-Tac-Toe!\n";
    if (vsComputer) {
        cout << "You are playing against the computer.\n";
    } else {
        cout << "You are playing against another player.\n";
    }

    for (int turn = 0; turn < 9; ++turn) {
        draw_a_board(board);

        if (player == 'X' || !vsComputer) {
            if (makeMove(board, player)) {
                if (check_the_win_condition(board, player)) {
                    draw_a_board(board);
                    cout << "Player " << player << " wins!\n";
                    return;
                }
                if (checkDraw(board)) {
                    draw_a_board(board);
                    cout << "It's a draw!\n";
                    return;
                }
                player = (player == 'X') ? 'O' : 'X'; // Switch player
            }
        } else {
            computerMove(board, computerPlayer, player);
            if (check_the_win_condition(board, computerPlayer)) {
                draw_a_board(board);
                cout << "Computer (" << computerPlayer << ") wins!\n";
                return;
            }
            if (checkDraw(board)) {
                draw_a_board(board);
                cout << "It's a draw!\n";
                return;
            }
            player = 'X'; // Switch to the human player
        }
    }
}

// Main function with replay option
int main() {
    char playAgain;
    char gameMode;

    do {
        cout << "Do you want to play against another player or the computer? (p/c): ";
        cin >> gameMode;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
        
        if (gameMode == 'p') {
            playGame(false); // Player vs Player
        } else if (gameMode == 'c') {
            playGame(true); // Player vs Computer
        } else {
            cout << "Invalid choice. Please select 'p' for player vs player or 'c' for player vs computer.\n";
        }

        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    } while (playAgain == 'y' || playAgain == 'Y');
    
    cout << "Thank you for playing!\n";
    return 0;
}
