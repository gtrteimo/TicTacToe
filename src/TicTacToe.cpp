
#include "include/TicTacToe.hpp"

uint8_t* TicTacToe::getBoard() const{
    return board;
}

TicTacToe::TicTacToe() : TicTacToe(3, 3, 2) {}
TicTacToe::TicTacToe(uint16_t size, uint16_t sequence, uint8_t playerCount) : size(size), sequence(sequence), playerCount(playerCount) {
    if (size < 3) {
        size = 3;
    }
    if (playerCount < 2||playerCount > 200  ) {
        playerCount = 2;
    }
    if (sequence>size||sequence<1) {
        sequence=size;
    }

    players = new uint8_t[playerCount];
    for (uint8_t i=0; i<playerCount; i++) {
        players[i]= i + 1;
    }
    board = new uint8_t[size*size]();
}

TicTacToe::~TicTacToe() {
    delete [] board;
    delete [] players;
}

/**
 * Function: calculate
 * -----------------------------------
 * Given an size×size grid (represented as a 1D array board), this function checks all rows, columns,
 * and both diagonals for a sequence of sequence consecutive identical numbers (ignoring zeros).
 *
 * If such a winning sequence is found, the function immediately returns the nonzero value.
 * Otherwise, it checks if any sequence-length line could become a winning sequence in the future
 * (treating 0 as a wildcard). In that case, the function returns 255.
 *
 * If neither a winning sequence nor a future possibility is found, the function returns 0.
 *
 * Parameters:
 *   size - the grid size (grid is size x size), must be greater than 2.
 *   sequence - the sequence length to check (0 < sequence <= size).
 *   board - the 1D array of size*size uint8_t containing grid values (each value is in 0..200).
 *
 * @return uint8_t - the winning number, or 255 if a future possibility exists, or 0 if neither.
 */
uint8_t TicTacToe::calculate() {
    bool possibilityFound = false;
    /* Directions to check:
       0: right, 1: down, 2: diagonal down-right, 3: diagonal down-left */
    const int8_t drow[4] = { 0, 1, 1, 1 };
    const int8_t dcol[4] = { 1, 0, 1, -1 };

    for (uint16_t i = 0U; i < size; i++) {
        for (uint16_t j = 0U; j < size; j++) {
            for (uint8_t d = 0U; d < 4U; d++) {
                /* Check if a sequence of length sequence fits in this direction.
                   Compute the ending row and column. */
                int row_end = (int)i + ((int)sequence - 1) * (int)drow[d];
                int col_end = (int)j + ((int)sequence - 1) * (int)dcol[d];
                if (row_end < 0 || row_end >= (int)size ||
                    col_end < 0 || col_end >= (int)size) {
                    continue;
                }

                bool win = true;
                bool poss = true;
                uint8_t winningCandidate = 0U;
                uint8_t possCandidate = 0U;

                for (uint16_t k = 0U; k < sequence; k++) {
                    int r = (int)i + (int)k * (int)drow[d];
                    int c = (int)j + (int)k * (int)dcol[d];
                    // uint16_t index = (uint16_t)r * size + (uint16_t)c;
                    uint32_t tempIndex = static_cast<uint32_t>(r) * static_cast<uint32_t>(size) + static_cast<uint32_t>(c);
                    uint16_t index = static_cast<uint16_t>(tempIndex);
                    
                    uint8_t cell = board[index];

                    /* For a winning sequence, all cells must be nonzero and equal */
                    if (k == 0U) {
                        if (cell == 0U) {
                            win = false;
                        } else {
                            winningCandidate = cell;
                        }
                    } else {
                        if (cell != winningCandidate) {
                            win = false;
                        }
                    }
                    /* For a potential future win, all nonzero cells (if any) must be identical.
                       Zeros are treated as wildcards. */
                    if (cell != 0U) {
                        if (possCandidate == 0U) {
                            possCandidate = cell;
                        } else if (cell != possCandidate) {
                            poss = false;
                        }
                    }
                } /* end for each cell in the sequence */

                if (win) {
                    /* Winning sequence found; return its value immediately */
                    return winningCandidate;
                }
                if (poss) {
                    possibilityFound = true;
                }
            }
        }
    }
    return possibilityFound ? 255U : 0U;
}

