#include "include/TicTacToeLocal.hpp"

TicTacToeLocal::TicTacToeLocal(uint16_t boardSize, uint16_t sequence, uint8_t playerCount) : TicTacToe(boardSize, sequence, playerCount) {}

TicTacToeLocal::TicTacToeLocal() {        
    // Ask for input from the user
    std::cout << "Enter the size of the TicTacToe board: ";
    std::cin >> boardSize;

    std::cout << "Enter the requierd sequence to win: ";
    std::cin >> sequence;

    std::cout << "Enter the amount of players playing TicTacToe: ";
    std::cin >> playerCount;

    t = new TicTacToe(boardSize, sequence, playerCount);

    std::cout << (int)gameLoop() << std::endl;
}

uint8_t TicTacToeLocal::gameLoop() {
    uint8_t running = 255;
    while (running) {
       running = t->calculate();
       
       break;
    }
    return running;
}

void TicTacToeLocal::printToConsole() {
    uint8_t* board = t->getBoard();
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {

        }
        
    }
}