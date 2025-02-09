#pragma once

#include <iostream>
#include <memory>

#include "TicTacToe.hpp"

class TicTacToeLocal : public TicTacToe {
    private:
        uint16_t boardSize, sequence;
        uint8_t playerCount, playerTurn = 0;
        TicTacToe* t;
    public:    
        TicTacToeLocal(uint16_t boardSize, uint16_t sequence, uint8_t playerCount);
        TicTacToeLocal(); 
    private:
        uint8_t gameLoop();
        void printToConsole(uint8_t width);
        uint32_t readFromConsole();
        
        
};
    