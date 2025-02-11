#pragma once

#include <inttypes.h>

class TicTacToe {
    private:
        uint16_t size, sequence;
        uint8_t playerCount;
        uint8_t *players, *board;
    public:
        uint8_t* getBoard() const;
    
        TicTacToe();
        TicTacToe(uint16_t size, uint16_t sequence, uint8_t playerCount);
    
        ~TicTacToe();
    
        uint8_t calculate();
        uint8_t setMove(uint8_t player, uint32_t move);
};
    