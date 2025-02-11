#pragma once

#include <iostream>
#include <memory>

#include "TicTacToe.hpp"

class TicTacToeUser : public TicTacToe {
    private:
        bool gui;
        uint16_t boardSize, sequence;
        uint8_t playerCount, playerTurn = 0;
        TicTacToe* t;
    public:    
        TicTacToeUser(uint16_t boardSize, uint16_t sequence, uint8_t playerCount);
        TicTacToeUser(); 
    private:
        uint8_t gameLoop();
        void printToConsole(uint8_t width);
        uint32_t readFromConsole();
        
        
};
    