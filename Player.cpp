/*****************************************************************************************************************************************************
** Author: Ignacio Procel
** Date: 12/06/19
** Description: This is the interface file for the Player class. Its data members represent
** various vital statistics for the player character in a game of Treasure quest.
******************************************************************************************************************************************************/
#include "Player.hpp"

/*****************************************************************************************************************************************************
** Player()
** Initialize data members. The higher the passed integer, the EASIER the game will be.
******************************************************************************************************************************************************/
Player::Player(int difficulty){
    strength_points = difficulty;
    victory = false;
}

/*****************************************************************************************************************************************************
** dec_strength()
** Reduces the players strength points by the passed amount. Can be passed a negative integer
** to increase strength.
******************************************************************************************************************************************************/
void Player::dec_strength(int lost){
    strength_points -= lost;
    if (strength_points < 0){
        strength_points == 0;
    }
}
