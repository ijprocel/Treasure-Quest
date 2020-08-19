/*****************************************************************************************************************************************************
** Author: Ignacio Procel
** Date: 12/06/19
** Description: This is the interface file for the Space class. A Board object pointing to a
** number of Space objects is used to play Treasure Quest.
******************************************************************************************************************************************************/
#ifndef SPACE_HPP 
#define SPACE_HPP

#include <random>
#include "Player.hpp"
#include "menu.hpp"

using std::cout;
using std::endl;
using std::string;

class Space
{
    protected:
        //Each Space object contains pointers to up to 8 other adjacent Space objects
            
            Space *left, *right, *top, *bottom;         //Pointers to horizontally adjacent spaces
            Space *top_left, *top_right,                //Pointers to diagonally adjacent spaces
            *bottom_left, *bottom_right;
        
        //When the game board is written to the terminal a character is used to represent each Space.
        //The Space's "sprite" data member contains that character.
            
            char default_sprite,        //The sprite ordinarily used by the Space, depends on the derived type.

            sprite;                     //The sprite currently used by the space. If the space is currently
                                        //occupied by the player, sprite = 'x'. Otherwise, sprite = default_sprite.

    public:
        Space(char);        //Sets eight position pointers to null and sprite to the passed char value

        //Setter methods for each of the eight pointers
            void setLeft    (Space* sp_ptr){left = sp_ptr;};
            void setRight   (Space* sp_ptr){right = sp_ptr;};
            void setTop     (Space* sp_ptr){top = sp_ptr;};
            void setBottom  (Space* sp_ptr){bottom = sp_ptr;};

            void setTopLeft     (Space* sp_ptr){top_left  = sp_ptr;};
            void setTopRight    (Space* sp_ptr){top_right  = sp_ptr;};
            void setBottomLeft  (Space* sp_ptr){bottom_left  = sp_ptr;};
            void setBottomRight (Space* sp_ptr){bottom_right  = sp_ptr;};

        char getSprite(){return sprite;};

        Space* move_player(char, Player*);  //Returns a pointer to the space the player wants to move to,
                                            //with the char parameter representing 1 of 8 move choices.
        
        virtual void interact(Player*) = 0; //Determines how the Player interacts with the Space. Different
                                            //for each derived type.
        
        void   travel_cost(Player*);        //Called by each derived type's interact() function (except Mountain).
                                            //Reduces the Player's strength points by 1.

        //These functions are overridden by and only used by Teleport objects. Defined here as well to
        //allow full polymorphic behavior using Space pointers.
            virtual void set_other_teleport(Space*){return;};
            virtual Space* get_ot(){return nullptr;};
};

//Mountain spaces simply don't allow the player to occupy them.
class Mountain : public Space
{
    public:
        Mountain(char icon);
        virtual void interact(Player*); //Does nothing, since the player can't occupy Mountain spaces.
};

//Each board contains 2 Teleport spaces. If the player moves to one, they're instantly teleported to the other.
class Teleport : public Space
{
    private:
        Space* other_teleport;      //Pointer to the other Teleport space. Set in the Board constructor.
    public:
        Teleport(char icon);
        
        //Getter and setter methods for other_teleport
            virtual void set_other_teleport(Space* other_teleport){this->other_teleport = other_teleport;};
            virtual Space* get_ot(){return other_teleport;};

        //Calls travel_cost(), displays dialogue, changes "sprite" to 'x'
            virtual void interact(Player*);
};

class Finish : public Space
{
    public:
        Finish(char icon);

        //Calls travel_cost(), displays dialogue, changes "sprite" to 'x'
        //Also checks if the game-winning condition has been achieved and updates Player's "victory" parameter if so
            virtual void interact(Player*);
};

class Enemy : public Space
{
    private:
        bool already_fought;        //Initialized to "false", flipped to "true" after enemy is fought once

    public:
        Enemy(char icon);
        //Calls travel_cost(), displays dialogue, changes "sprite" to 'x'
        //Also implements the combat subroutine and modifies the Player object accordingly.
            virtual void interact(Player*);
};

class Blank : public Space
{
    public:
        Blank(char icon);
        //Calls travel_cost(), displays dialogue, changes "sprite" to 'x'
            virtual void interact(Player*);
};

#endif
