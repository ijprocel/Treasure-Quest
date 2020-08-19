/*****************************************************************************************************************************************************
** Author: Ignacio Procel
** Date: 12/10/19
** Description: This is the interface file for the Player class. Its data members represent
** various vital statistics for the player character in a game of Treasure quest. 
******************************************************************************************************************************************************/
#ifndef PLAYER_HPP 
#define PLAYER_HPP

#include <vector>

class Player
{
    private:
        std::vector<int> key_bag;
        int strength_points;
        bool victory;

    public:
        Player(int);

        //Getter methods for player attributes
            int  strength() {return strength_points;};
            int  keys()     {return key_bag.size();};
            bool status()   {return !(strength_points == 0);};
            bool won_game() {return victory;};

        //Methods  to modify player attributes as a result of game events.
            void dec_strength(int);
            void add_key()      {key_bag.push_back(1);};
            void flip_victory() {victory = !victory;};
};

#endif
