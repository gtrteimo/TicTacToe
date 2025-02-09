#include <format>

#include "include/TicTacToeLocal.hpp"

TicTacToeLocal::TicTacToeLocal(uint16_t boardSize, uint16_t sequence, uint8_t playerCount) : TicTacToe(boardSize, sequence, playerCount) {}

TicTacToeLocal::TicTacToeLocal() {        

    boardSize = 0;
    sequence = boardSize;
    playerCount = 0;

    int tempInput;

    std::cout << "\nTicTacToe Setup:\n"
              << "1) Board Size\n"
              << "2) Win Sequence\n"
              << "3) Number of Players\n"
              << std::endl;

    std::cout << "Enter the size of the TicTacToe board: ";
    while (true) {
        if (!(std::cin >> tempInput) || tempInput < 3) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! The board size must be at least 3: ";
        } else {
            boardSize = static_cast<uint16_t>(tempInput);
            break;
        }
    }

    std::cout << "Enter the required sequence to win: ";
    while (true) {
        if (!(std::cin >> tempInput) || tempInput < 1 || tempInput > static_cast<int>(boardSize)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! The sequence must be between 1 and " << boardSize << ": ";
        } else {
            sequence = static_cast<uint16_t>(tempInput);
            break;
        }
    }

    std::cout << "Enter the number of players playing TicTacToe: ";
    while (true) {
        if (!(std::cin >> tempInput) || tempInput < 2 || tempInput > 200) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! The number of players must be between 2 and 200: ";
        } else {
            playerCount = static_cast<uint8_t>(tempInput);
            break;
        }
    }

    std::cout << std::endl;

    t = new TicTacToe(boardSize, sequence, playerCount);

    std::cout << (int)gameLoop() << std::endl;
}

uint8_t TicTacToeLocal::gameLoop() {
    uint8_t width = 0;
    uint32_t num = (uint32_t)boardSize*boardSize-1;
    while (num > 0) {
        num /= 10;
        width++;
    }
    uint8_t running = 255;
    while (running) {
       running = t->calculate();
       printToConsole(width);
       readFromConsole();
       break;
       if (running <= 200) {
        break;
       }

    }
    return running;
}

void TicTacToeLocal::printToConsole(uint8_t width) {
    uint8_t* board = t->getBoard();
    for (int i = 0; i < boardSize; i++) {
        if (i) {
            for (int j = 0; j < boardSize; j++) {
                if (j) {
                    std::cout << "-";
                }
                for (int k = 0; k < width; k++) {
                    std::cout << "-";
                }
            }
            std::cout << "\n";
        }
        for (int j = 0; j < boardSize; j++) {
            if (j) {
                std::cout << "|";
            }
            uint8_t n1 = 0;
            uint8_t n2 = board[i*boardSize+j];
            if (n2) {
                if (n2 > 90) {
                    n1 = 65;
                    n2 -= 26;
                    while (n2 > 90) {
                        n2 -= 26;
                        n1++;
                    }
                }
                if (n1) {
                    std::cout << std::format("{:^{}s}", std::string(1, (char)n1) + std::string(1, (char)n2), width);
                } else {
                    std::cout << std::format("{:^{}d}", n2, width);
                }
            } else {
                std::cout << std::format("{:^{}d}", i*boardSize + j, width);
            }
        }
        std::cout << "\n";
    }
}

uint32_t TicTacToeLocal::readFromConsole() {
    return 0;
}