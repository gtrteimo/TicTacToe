#include <format>

#include "include/TicTacToeUser.hpp"

TicTacToeUser::TicTacToeUser(uint16_t boardSize, uint16_t sequence, uint8_t playerCount) : TicTacToe(boardSize, sequence, playerCount) {}

TicTacToeUser::TicTacToeUser() {        

    boardSize = 3;
    sequence = boardSize;
    playerCount = 2;
    gui = false;

    bool rep = true;
    int tempInput;

    while (rep) {

        std::cout << "TicTacToe:\n"
                << "1) Play Local\n"
                << "2) Play Online\n"
                << "3) Settings\n"
                << "4) Exit\n";

        std::cout << std::endl;

        uint8_t var = 0;

        while (true) {
            if (!(std::cin >> tempInput) || tempInput < 1 || tempInput > 4) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input! Choose between 1 to 4: ";
            } else {
                var = static_cast<uint8_t>(tempInput);
                break;
            }
        }

        std::cout << std::endl;

        switch (var) {
        case 1: {
            t = new TicTacToe(boardSize, sequence, playerCount);
            uint8_t result = gameLoop();  // Now safely scoped within case 1
            if (result == 255) { 
                uint8_t n1 = 0; 
                uint8_t n2 = playerTurn;
                if (n2 > 90) {
                    n1 = 65;
                    n2 -= 26;
                    while (n2 > 90) {
                        n2 -= 26;
                        n1++;
                    }
                }
                if (n1) {
                    std::cout << "\nGame was aborted by player "<<n1<<n2<<"!";
                } else {
                    std::cout << "\nGame was aborted by player "<<n2<<"!";
                }
            } else if (result) {
                uint8_t n1 = 0; 
                uint8_t n2 = result;
                if (n2 > 90) {
                    n1 = 65;
                    n2 -= 26;
                    while (n2 > 90) {
                        n2 -= 26;
                        n1++;
                    }
                }
                if (n1) {
                    std::cout << "\nPlayer "<<n1<<n2<<" won the game!";
                } else {
                    std::cout << "\nPlayer "<<n2<<" won the game!";
                }
            } else {
                std::cout << "Draw! Winning is impossible in this situation!";
            }
            delete t;
            break;
        } case 2:
            std::cout << "Not Implemented" << std::endl;
            break;
        case 3: {
            bool repeat = true;  // Move this declaration outside the switch
            while (repeat) {
                std::cout << "TicTacToe Setup:\n"
                << "1) Board Size\n"
                << "2) Win Sequence\n"
                << "3) Number of Players\n"
                << "4) Enable GUI\n"
                << "5) Return\n"
                << std::endl;

                while (true) {
                    if (!(std::cin >> tempInput) || tempInput < 1 || tempInput > 5) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid input! Choose between 1 to 5: ";
                    } else {
                        var = static_cast<uint8_t>(tempInput);
                        break;
                    }
                }
                switch (var) {
                case 1:
                    std::cout << "Enter the size of the TicTacToe board, currctly " << boardSize << ": ";
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
                    break;
                case 2:
                    std::cout << "Enter the required sequence to win, currctly " << sequence << ": ";
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
                    break;
                case 3:
                    std::cout << "Enter the number of players playing TicTacToe, currctly " << playerCount << ": ";
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
                    break;
                case 4:
                    std::cout << "Enable GUI (y/n), currctly " << gui << ": ";
                    char input;
                    while (true) {
                        if (!(std::cin >> input) || (tolower(input) != 'y' && tolower(input) != 'n')) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "Invalid input! Enter 'y' for yes or 'n' for no: ";
                        } else {
                            gui = (tolower(input) == 'y');
                            break;
                        }
                    }
                    break;
                case 5:
                    repeat = false;
                    break;
                }
            }
            break;
        }
        case 4:
            rep = false;
            break;
        }
        std::cout << std::endl;
    }
}


uint8_t TicTacToeUser::gameLoop() {
    uint8_t width = 0;
    uint32_t num = (uint32_t)boardSize*boardSize-1;
    while (num > 0) {
        num /= 10;
        width++;
    }
    uint8_t running = 255;
    printToConsole(width);
    while (running) {
       uint32_t in = readFromConsole();
       if (in == 4294967295) {
        running = 255;
        break;
       }
       t->setMove(playerTurn+1, in);
       printToConsole(width);
       running = t->calculate();
       playerTurn++;
       if (playerTurn >= playerCount) {
        playerTurn = 0;
       }
       if (running <= 200) {
        break;
       }

    }
    return running;
}

void TicTacToeUser::printToConsole(uint8_t width) {
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
            // std::cout << (int)n2 << std::endl;
            if (n2) {
                n2 += 64;
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
                    std::cout << std::format("{:^{}c}", n2, width);
                }
            } else {
                std::cout << std::format("{:^{}d}", i*boardSize + j, width);
            }
        }
        std::cout << "\n";
    }
}

uint32_t TicTacToeUser::readFromConsole() {
    uint32_t ret = 4294967295;
    long tempInput = 0;
    uint8_t n1 = 0; 
    uint8_t n2 = (playerTurn % playerCount) + 65;
    if (n2 > 90) {
        n1 = 65;
        n2 -= 26;
        while (n2 > 90) {
            n2 -= 26;
            n1++;
        }
    }
    if (n1) {
        std::cout << "\nPlayer "<<n1<<n2<<": Choose your move: ";
    } else {
        std::cout << "\nPlayer "<<n2<<": Choose your move: ";
    }
    while (true) {
        if (!(std::cin >> tempInput) || tempInput < -1 || tempInput >= boardSize*boardSize) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! Choose between 0 to "<<boardSize*boardSize-1<<": ";
        } else {
            ret = static_cast<uint32_t>(tempInput);
            break;
        }
    }
    return ret;
}