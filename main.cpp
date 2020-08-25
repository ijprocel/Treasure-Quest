/*****************************************************************************************************************************************************
** Author: Ignacio Procel
** Date: 12/10/19
** This is the main file for the implementation of Treasure Quest. A player moves around a board,
** battling enemies in hopes of acquiring keys that will unlock a great treasure.
******************************************************************************************************************************************************/
#include "menu.hpp"
#include "Board.hpp"
#include "Player.hpp"

#include <iomanip>

char getMove(string*, int);
void map_keys(string*, int);
void show_intro();

/*****************************************************************************************************************************************************
** main()
** Calling main allows a game of Treasure Quest to be played.
******************************************************************************************************************************************************/
int main(){
    const int NUM_CONTROLS = 8;
    string response = "y";
    do{
        show_intro();           //Display the introduction

        //Set the game controls
        string key_list[NUM_CONTROLS] = {"1", "2", "3", "4", "6", "7", "8", "9"}, temp;
        map_keys(key_list, NUM_CONTROLS);

        Player player(30);      //Initialize Player object with 30 strength points
        Board game_board;       //Initialize a game board

        //Get the player's starting location and display the player's strength
        Space* current_space = game_board.getPlayerStart();

        do {
            cout << "---------------------------------------------------------------------------------------\n"
            << "Player strength: " << player.strength() << "\n"
            <<"Player Keys: " << player.keys() << "\n" << endl;
            game_board.showBoard();

            char move = getMove(key_list, NUM_CONTROLS);
            current_space = current_space->move_player(move, &player);

        }while((player.status()) && (!player.won_game()));      //If the player still has strength points and
                                                                //has not won the game, player takes another turn.
        cout << "------------------------------------------------------------------------------------------\n";

        if (player.won_game()){
            cout << "You win!\n";
        }
        else {
            cout << "Game over!\n";
        }

        cout << "Would you like to play again? (y/n) ";
        string acceptable_responses[2] = {"y", "n"},
        error_mes = "Please respond with 'y' or 'n'. Enter: ";
        ValidateMultChoice(response, acceptable_responses, 2, error_mes);       //See menu.hpp/cpp
        cout << endl;

    }while(response == "y");

    return 0;
}

/*****************************************************************************************************************************************************
** getMove(string* controls, const int NUM_CONTROLS)
** Prompts the user to input their next move and returns the appropriate character.

** controls - The list of single-character game controls.
** NUM_CONTROLS - The number of game controls.
******************************************************************************************************************************************************/
char getMove(string* controls, const int NUM_CONTROLS){

    string error_mes = "Invalid move. Enter: ", response;
    cout << "Enter your move: ";
    ValidateMultChoice(response, controls, NUM_CONTROLS, error_mes);
    cout << endl;

    vector<string> acceptable_moves = {"1", "2", "3", "4", "6", "7", "8", "9"};

    //This loop translates the user's move input to the value that later functions are expecting.
    //If the user has chosen to use the default controls, the value of "response" does not change.
    for (int index=0; index < NUM_CONTROLS; index++){
        if (response == controls[index]){
            response = acceptable_moves[index];
        }
    }

    return response[0];     //Function returns a char, not string.
}

/*****************************************************************************************************************************************************
** map_keys(string* key_list)
** This function allows the player to use different controls than the default if desired.
** If the player does want custom controls, they must provide a key for all eight. Only single
** keys are allowed.

** The "key_list" parameter is a pointer to an array that holds the game controls. It initially
** contains the default controls and will be modified if the user wants to designate custom ones.
******************************************************************************************************************************************************/
void map_keys(string* key_list, const int NUM_CONTROLS){
    cout << "This game is designed to be played with the number pad.\n"
    "The controls are as follows:\n\n"
    "Move SW: 1\nMove S:  2\nMove SE: 3\nMove W:  4\n"
    "Move E:  6\nMove NW: 7\nMove N:  8\nMove NE: 9\n\n"

    "Would you like to use different controls? (y/n) ";

    string acceptable_responses[2] = {"y", "n"},
    error_mes = "Please respond with 'y' or 'n'. Enter: ", response;
    ValidateMultChoice(response, acceptable_responses, 2, error_mes);       //See menu.hpp/cpp
    cout << endl;

    if (response == "y"){
        vector<string> moves =                     //Will be looped through and written to terminal
        {"SW", "S", "SE", "W", "E", "NW", "N", "NE"};

        vector<string> usable_char_list;           //Will be populated with the characters listed below
        
        string usable_chars = "0123456789"              //Usable chars are any digit, letter, or symbol that can be
        "abcdefghijklmnopqrstuvwxyz"                    //typed without using the Shift key.
        "-=[];',./+*";

        //Populate usable_char_list
        for (char u_char : usable_chars){
            string s(1, u_char);
            usable_char_list.push_back(s);
        }

        cout << "Each control must be a single character. You may use any character from the following list:\n";
        cout << usable_chars << endl << endl;

        for (int index=0; index < NUM_CONTROLS; index++){
            cout << "What key would you like to use to move "           //Prompt user for next control
            << moves[index] << "? ";

            string error_mes = "That is either an invalid control key," 
            " or it has already been used. Enter: ",
            new_control = ValidateNewControls(usable_char_list,         //Validates that desired control is in the list of acceptable controls
            usable_char_list.size(), error_mes);                        //and removes already-used keys from the list. See menu.cpp for details.

            key_list[index] = new_control;
        }
        cout << endl;

        //Display the new controls to the user.
        cout << "New controls:\n";
        for (int index=0; index < NUM_CONTROLS; index++){
            cout << std::left;
            cout << std::setw(9);
            cout << "Move " + moves[index] + ":" << key_list[index] << endl;
        }
        cout << endl;
    }
}

void show_intro(){
    cout << "Welcome to Treasure Quest!\n\n"
    "A deathbed confession by your grandfather has revealed an incredible secret: the location of a vault containing untold riches!\n\n"
    "But there's a catch: the only way into the vault is with four different keys, stolen many years ago by bandits.\n"
    "Luckily, they also stole a fake map leading to the vault. Fearing for his life and the lives of his family when the bandits realized\nthe deception, your grandfather fled far away.\n\n"
    "Now he, old, tired, and nearing the end, has given you the means to claim your birthright.\n"
    "You must travel to the land of his youth, track down the keys, and find the vault.\n\n"
    "Good luck!\n(press Enter)";
    string x;
    getline(cin, x);

    cout << "\n\n"
    "NW       N       NE\n"
    "                   \n"
    "    . . . A . .    \n"
    "    A A A . . .    \n"
    "W   O A . . . .   E\n"
    "    . . . A . A    \n"
    "    . A A . . .    \n"
    "    . O ! . . x    \n"
    "                   \n"
    "SW       S       SE\n\n"
    
    "BASIC GAMEPLAY:\n"
    "Your grandfather's map will be your guide, with each location in the land marked with a symbol.\n"
    "x - Represents you. You may move in any of the eight directions shown.\n"
    "A - Impassable mountains. You'll have to find ways around them.\n"
    "O - Two portals created by ancient, unknown magic. Step into one and you'll immediately be transported to the other!\n"
    "! - The location of the vault. Make your way here when you've acquired all four keys.\n"
    ". - Settlements. These are where you will search for the bandits.\n"
    "Be warned: the journey from one place to another takes a toll. You will lose one strength point each time you move. \n"
    "Run out of strength and your journey ends.\n(press Enter)";
    getline(cin, x);
    
    cout << "\n\n"
    "BATTLE:\n"
    "To gain the keys from the bandits, you must defeat them in battle.\n"
    "Each one has a maximum possible attack power of between 6 and 10. Their actual attack may be weaker.\n"
    "You will launch your own attack. To do so, you will wager a certain number of your strength points,\nwith the power of your attack being equal to that number.\n"
    "If your attack is weaker than the bandit's, you will lose the fight and lose all the strength points that you wagered.\n"
    "If your attack is equal to or greater than the bandit's, you win the fight, losing only some of the strength points that you wagered, and win a key.\n(press Enter)";
    getline(cin, x);
    cout << "\n\n\n\n" << endl;
}