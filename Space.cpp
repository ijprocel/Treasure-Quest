/*****************************************************************************************************************************************************
** Author: Ignacio Procel
** Date: 11/20/19
** Description: This is the implementation file for the constructors of the Space abstract class
** and its derived classes.
******************************************************************************************************************************************************/
#include "Space.hpp"

/*****************************************************************************************************************************************************
** Base()
** Base constructor. Initializes data members.
******************************************************************************************************************************************************/
Space::Space(char sprite){
    this->sprite = sprite;

    left = right = top = bottom = top_left = 
    top_right = bottom_left = bottom_right = nullptr;
}

/*****************************************************************************************************************************************************
** Mountain()
** Mountain constructor. Sets default sprite and calls Space constructor.
******************************************************************************************************************************************************/
Mountain::Mountain(char icon) : Space(icon){
    default_sprite = 'A';
}

/*****************************************************************************************************************************************************
** Mountain::interact()
** Does nothing since player cannot occupy a Mountain space.
******************************************************************************************************************************************************/
void Mountain::interact(Player* player){
    return;
}

/*****************************************************************************************************************************************************
** Teleport()
** Teleport constructor. Sets default sprite and calls Space constructor.
******************************************************************************************************************************************************/
Teleport::Teleport(char icon) : Space(icon){
    default_sprite = 'O';
}

/*****************************************************************************************************************************************************
** Teleport::interact()
******************************************************************************************************************************************************/
void Teleport::interact(Player* player){
    travel_cost(player);
    cout << "Prepare to teleport! " << endl;
    sprite = 'x';
}

/*****************************************************************************************************************************************************
** Finish()
** Finish constructor. Sets default sprite and calls Space constructor.
******************************************************************************************************************************************************/
Finish::Finish(char icon) : Space(icon){
    default_sprite = '!';
}

/*****************************************************************************************************************************************************
** Finish::interact(Player* player)
** Checks if the game-winning condition has been achieved and updates Player's "victory" parameter if so
******************************************************************************************************************************************************/
void Finish::interact(Player* player){
    travel_cost(player);
    sprite = 'x';

    if (player->keys() < 4){
        cout << "You've reached the vault!\nBut you've only acquired " << player->keys() << " keys.\n"
        "Return with 4 keys to unlock the treasure within!" << endl;
        return;
    }

    cout << "You've reached the vault with all 4 keys and reclaimed the family treasure!" << endl;

    player->flip_victory();
}

/*****************************************************************************************************************************************************
** Enemy()
** Enemy constructor. Sets default sprite, "already_fought", and calls Space constructor.
******************************************************************************************************************************************************/
Enemy::Enemy(char icon) : Space(icon){
    default_sprite = '.';
    already_fought = false;
}

/*****************************************************************************************************************************************************
** Finish::interact(Player* player)
** Runs the combat subroutine if the following conditions are met:
    - Player has at least 1 strength point
    - This Space's combat subroutine has not already been run
    - The player has not acquired the 4 keys needed for victory

** Combat flows as follows:
    - Maximum power of the enemy is randomly chosen [6, 10]
    - Actual enemy attack is chosen [1, max power]
    - Player wagers [1, max power] strength points, which are decremented from their total
    - If player attack >= enemy attack, player wins. Recovers half of wagered strength points and gains a key
    - Otherwise, all strength points wagered remain lost.
******************************************************************************************************************************************************/
void Enemy::interact(Player* player){

    travel_cost(player);
    sprite = 'x';

    //Stop here if player has no strength points left
    if (!player->status()){
        return;
    }

    if (!already_fought && (player->keys() < 4)){
        //Initialize and seed a random number engine
        std::default_random_engine rd;
        std::random_device seed_gen{};
        rd.seed(seed_gen());

        cout << "You've found one of the bandits! Prepare for battle!\n\n";
        
        //Randomly generate enemy attack.
        int enemy_strength = std::uniform_int_distribution<int>{6, 10}(rd);
        int enemy_attack = std::uniform_int_distribution<int>{1, enemy_strength}(rd);

        cout << "The bandit has a maximum attack of " << enemy_strength << "\n"
        "How many strength points would you like to wager? (1 to " << enemy_strength << ") ";
        
        //Get player's wager, subtract it from their strength points.
        int wager;
        ValidateInt(wager, 1, enemy_strength);
        player->dec_strength(wager);

        cout << "Strength points remaining: " << player->strength() << "\n"
        << "Enemy attack: " << enemy_attack << "\n" << endl;
        
        //Check if player's attack is enough to defeat the enemy.
        if (wager >= enemy_attack){
            cout << "You've defeated the bandit and recovered a key!\n" << endl;
            player->add_key();
            player->dec_strength(-(wager / 2));
            cout << "You've also recovered half of the strength points that you wagered.\n"
            "Strength points remaining: " << player->strength() << endl;
        }
        else {
            cout << "You failed to defeat the bandit. He escapes with a key.\n"
            "Strength points remaining: " << player->strength() << endl;
        }

        already_fought = true;

        cout << "Press Enter to continue: ";
        string temp;
        getline(cin, temp);
    }
    else {
        cout << "None of the bandits have been seen here. You stop and rest for the night." << endl;
    }
}

/*****************************************************************************************************************************************************
** Blank constructor. updates the various space attributes to those of a Blank
** 'name' parameter is optional. If no name is passed, a default value is used ("Blank").
******************************************************************************************************************************************************/
Blank::Blank(char icon) : Space(icon){
    default_sprite = '.';
}

/*****************************************************************************************************************************************************
** Empty
******************************************************************************************************************************************************/
void Blank::interact(Player* player){
    travel_cost(player);
    cout << "None of the bandits have been seen here. You stop and rest for the night." << endl;
    sprite = 'x';
}

/*****************************************************************************************************************************************************
** Space::move_player(char move, Player* player)
** Called by the player's current space to move to the next space. Returns a pointer to the next space.
******************************************************************************************************************************************************/
Space* Space::move_player(char move, Player* player){
    Space* ptr_to_next=nullptr;
    
    switch(move){
        case('1'):  ptr_to_next = bottom_left;
                    break;
        case('2'):  ptr_to_next = bottom;
                    break;
        case('3'):  ptr_to_next = bottom_right;
                    break;
        case('4'):  ptr_to_next = left;
                    break;
        case('6'):  ptr_to_next = right;
                    break;
        case('7'):  ptr_to_next = top_left;
                    break;
        case('8'):  ptr_to_next = top;
                    break;
        case('9'):  ptr_to_next = top_right;
                    break;
    }

    //Spaces are initialized with all adjacent pointers set to null. If a space is on the edge of
    //the board, the appropriate spaces remain set to null.

    if (!ptr_to_next){
        cout << "You cannot move off the edge of the board" << endl;
        return this;
    }
    
    char next_sprite = ptr_to_next->getSprite();

    switch(next_sprite){
        //Case Mountain: Player can't move, return current postition as next position
        case('A'):  cout << "A mountain blocks your path..." << endl;
                    return this;

        //Case Teleport: Return the pointer to the other Teleport space
        case('O'):  ptr_to_next = ptr_to_next->get_ot();
        
        //If execution arrives here, the player will be moved from the current space, so the
        //current space's sprite must be reset to its default.
        default:    sprite = default_sprite;
    }

    //Call the next Space's interact function.
    ptr_to_next->interact(player);

    return ptr_to_next;
}

/*****************************************************************************************************************************************************
** Space::travel_cost(Player* player)
** Decreases the player's strength by 1. Called each time they move to a new space, before any interactions.
******************************************************************************************************************************************************/
void Space::travel_cost(Player* player){
    player->dec_strength(1);
    
    cout << "Your travels have made you weary. You have " <<  player->strength()
    << " strength point";

    if (player->strength() != 1){
        cout << 's';
    }
    cout << " remaining.\n" << endl;
}