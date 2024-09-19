#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

const int rows = 3;
const int cols = 3;

unordered_map<char, int> SYMBOL_ROWS = {
    {'A', 2},
    {'B', 4},
    {'C', 6},
    {'D', 8}
};

unordered_map<char, int> SYMBOL_VALUES = {
    {'A', 1},
    {'B', 3},
    {'C', 5},
    {'D', 7}
};

double deposit() {
    double amount;
    while (true) {
        cout << "Enter a deposit amount: ";
        cin >> amount;

        if (cin.fail() || amount <= 0) {
            cin.clear(); // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Invalid deposit amount, try again." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            return amount;
        }
    }
}

int getLines() {
    int numberofLines;
    while (true) {
        cout << "Enter a lines amount to bet on (1-3): ";
        cin >> numberofLines;

        if (cin.fail() || numberofLines <= 0 || numberofLines > 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid number of lines, try again." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return numberofLines;
        }
    }
}

double getBet(double balance, int amtLines) {
    double amtOfBet;
    while (true) {
        cout << "Enter the bet per line: ";
        cin >> amtOfBet;
        double total = balance / amtLines;

        if (amtOfBet > total) {
            cout << "Amount of bet is greater than balance available, try again." << endl;
        } else if (amtOfBet <= 0) {
            cout << "Invalid bet amount, try again." << endl;
        } else {
            return amtOfBet;
        }
    }
}

vector<vector<char>> spin() {
    vector<char> symbols;
    for (const auto& pair : SYMBOL_ROWS) {
        for (int i = 0; i < pair.second; i++) {
            symbols.push_back(pair.first);
        }
    }

    vector<vector<char>> roll(cols, vector<char>());

    for (int i = 0; i < cols; i++) {
        vector<char> rollSymbols = symbols;
        for (int j = 0; j < rows; j++) {
            int random = rand() % rollSymbols.size();
            roll[i].push_back(rollSymbols[random]);
            rollSymbols.erase(rollSymbols.begin() + random);
        }
    }
    return roll;
}

vector<vector<char>> transpose(const vector<vector<char>>& rolled) {
    vector<vector<char>> ROWS(rows, vector<char>());
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            ROWS[i].push_back(rolled[j][i]);
        }
    }
    return ROWS;
}

void printRow(const vector<vector<char>>& rolled) {
    for (const auto& row : rolled) {
        if (!row.empty()) {
            string rowString;
            for (size_t i = 0; i < row.size(); i++) {
                rowString += row[i];
                if (i != row.size() - 1) {
                    rowString += " | ";
                }
            }
            cout << rowString << endl;
        }
    }
}

double getWinning(const vector<vector<char>>& transposed, double bet, int lines) {
    double winnings = 0;

    for (int i = 0; i < lines; i++) {
        const auto& symbols = transposed[i];
        bool allsame = true;
        for (const auto& symbol : symbols) {
            if (symbol != symbols[0]) {
                allsame = false;
                break;
            }
        }
        if (allsame) {
            winnings += bet * SYMBOL_VALUES[symbols[0]];
        }
    }

    return winnings;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    double balance = deposit();
    bool exit = false;
    while (!exit) {
        cout << "Your balance is: $" << balance << endl;
        int amtLines = getLines();
        double bet = getBet(balance, amtLines);
        balance -= bet * amtLines;
        auto rolled = spin();
        auto transposed = transpose(rolled);
        printRow(rolled);
        double win = getWinning(transposed, bet, amtLines);
        balance += win;
        cout << "You won: $" << win << endl;

        string playAgain;
        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;
        if (playAgain != "y") {
            exit = true;
        }
    }
    return 0;
}

