#include "User.h"
#include "UserManager.h"
#include "game_logic.h"
#include "game_ui.h"
#include "ai_logic.h"
#include "leaderboard.h"
#include "game_constants.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <limits>

using namespace std;

int main() {
#ifdef _WIN32
    system("chcp 65001");
    system("color 0D");
#endif

    srand(time(NULL));

    string username, password;
    int authChoice;

    cout << "1. Register\n2. Login\nChoose option: ";
    cin >> authChoice;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    bool loggedIn = false;

    if (authChoice == 1) {
        if (UserManager::registerUser(User(username, password))) {
            cout << "Registered successfully!\n";
            loggedIn = true;
        } else {
            cout << "Username already exists.\n";
        }
    } else if (authChoice == 2) {
        if (UserManager::loginUser(username, password)) {
            cout << "Login successful!\n";
            loggedIn = true;
        } else {
            cout << "Invalid credentials.\n";
        }
    } else {
        cout << "Invalid option.\n";
        return 0;
    }

    if (!loggedIn) return 0;

    char x, o;
    int choice;
    string u1 = username, u2;
    int menuChoice;
    vector<char> board(9);
    char playAgain;
    int aiLevel = 0;

    while (true) {
        GameUI::showRules();
        GameUI::showMainMenu();

        while (!(cin >> menuChoice) || menuChoice < 1 || menuChoice > 4) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << RED << " " << warning << " Invalid input! Enter 1-4: " << RESET;
        }

        if (menuChoice == 4) {
            cout << "\n " << sparkle << " Thanks for playing! " << sparkle << "\n";
            break;
        }
        if (menuChoice == 3) {
            Leaderboard::showLeaderboard();
            continue;
        }

        GameLogic::clearScreen();

        if (menuChoice == 1) {
            cout << " " << person << " Enter name of player 2: ";
            cin >> u2;
        } else {
            u2 = "Computer";
            cout << "\n " << robot << " Select AI difficulty:\n";
            cout << " " << dice << " 1. Easy\n";
            cout << " " << brain << " 2. Medium\n";
            cout << " " << genius << " 3. Hard\n";
            cout << " " << check << " Enter choice (1-3): ";
            while (!(cin >> aiLevel) || aiLevel < 1 || aiLevel > 3) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << RED << " " << warning << " Invalid input! Enter 1-3: " << RESET;
            }
        }

        GameUI::selectSymbol(x, o, u1);

        do {
            board = {'1','2','3','4','5','6','7','8','9'};
            vector<int> usedMoves;
            int currentPlayer = 1;
            int score = -1;

            ofstream history("history.txt", ios::app);
            history << "\nMatch: " << u1 << " vs " << u2 << "\n";

            while (score == -1) {
                GameLogic::displayColorfulBoard(x, o, u1, u2, board);

                if (currentPlayer == 1 || menuChoice == 1) {
                    cout << " " << (currentPlayer == 1 ? u1 : u2) << ", enter position (1-9): ";
                    while (!(cin >> choice) || choice < 1 || choice > 9 ||
                           !AILogic::isMoveValid(usedMoves, choice) || board[choice-1] == 'X' || board[choice-1] == 'O') {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << RED << " " << warning << " Invalid move! Try again: " << RESET;
                    }
                } else {
                    switch (aiLevel) {
                        case 1: AILogic::easyAI(board, usedMoves, choice); break;
                        case 2: AILogic::mediumAI(board, usedMoves, choice, o, x); break;
                        case 3: AILogic::hardAI(board, usedMoves, choice, o); break;
                    }
                    cout << " " << robot << " Computer chooses position " << choice << "\n";
                    GameLogic::wait(500);
                }

                usedMoves.push_back(choice);
                board[choice-1] = (currentPlayer == 1) ? x : o;

                history << (currentPlayer == 1 ? u1 : u2) << " played " << choice << "\n";

                score = GameLogic::checkWin(board);
                currentPlayer = (currentPlayer % 2) + 1;
            }

            GameLogic::displayColorfulBoard(x, o, u1, u2, board);

            string winner;
            if (score == 1) {
                winner = (currentPlayer == 1) ? u2 : u1;
                cout << GREEN << "\n " << trophy << " " << winner << " wins! " << trophy << "\n" << RESET;
            } else {
                winner = "DRAW";
                cout << YELLOW << "\n " << handshake << " It's a draw! " << handshake << "\n" << RESET;
            }

            Leaderboard::updateLeaderboard(u1, u2, winner);
            history << "Result: " << winner << "\n";
            history << "-----------------------------\n";
            history.close();

            cout << "\n " << star << " Play again with same players? (y/n): ";
            cin >> playAgain;
        } while (tolower(playAgain) == 'y');
    }

    return 0;
}
