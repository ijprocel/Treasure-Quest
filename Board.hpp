/*****************************************************************************************************************************************************
** Author: Ignacio Procel
** Date: 12/10/19
** Description: This is the interface file for the Board class. This class creates a
** 2D vector of pointers to Space objects which can be used to play a game of Treasure Quest.
******************************************************************************************************************************************************/
#ifndef BOARD_HPP 
#define BOARD_HPP

#include <fstream>
#include <algorithm>

#include "Space.hpp"

class Board
{
    private:
        const int ROWS = 6, COLS = 6;           //Board dimensions
        std::vector<std::vector<Space*>> board;

        int player_start[2];                    //Starting position of the player

        //Called by constructor. Used to choose a template for and create the board.
        string choose_map();
        void   populate_board(string);

    public:
        Board();

        Space* getPlayerStart(){return board[player_start[0]][player_start[1]];};

        void showBoard();

        ~Board();
};

#endif
