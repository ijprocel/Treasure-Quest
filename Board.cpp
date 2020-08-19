/*****************************************************************************************************************************************************
** Author: Ignacio Procel
** Date: 12/10/19
** Description: This is the implementation file for the Board class. This class creates a
** 2D vector of pointers to Space objects which can be used to play a game of Treasure Quest.
******************************************************************************************************************************************************/
#include "Board.hpp"

/*****************************************************************************************************************************************************
** Board()
** Board constructor. Randomly selects a template to build the game board, a 2D vector of
** objects derived from the Space class. Passes the template to the function that creates the board.
******************************************************************************************************************************************************/
Board::Board(){
    //Initialize and seed a random number engine to be used to permute a string
    std::default_random_engine rd;
    std::random_device seed_gen{};
    rd.seed(seed_gen());
    
    //Attempt to select a map from "maps.txt" An exception will be thrown if the size of the map
    //does not match the size of the board (map length == ROWS * COLS)
    string map;
    try{
        map = choose_map();
    }
    catch (string size_error){
        cout << size_error;
    }

    //String "map" will contain the characters 'A' and '.'
    //At random, some of the '.' characters will be replaced with 'x', '!', 'e', or 'O'.

    int spaces = std::count(map.begin(), map.end(), '.');

    string to_permute = "x!OO";
    for (int index = 0; index < 10; index++){
        to_permute += 'e';
    }
    while (to_permute.length() < spaces){
        to_permute += '.';
    }

    //At this point, to_permute will equal "x!00eeeeeeeeee", followed by
    //enough '.' characters so that its length is equal to "spaces".
    
    //Randomly permute "to_permute"
    std::shuffle(to_permute.begin(), to_permute.end(), rd);
    
    int to_permute_index = 0;                               //Will act as a pointer to a character in "to_permute"

    for (int index = 0; index < map.length(); index++){     //Iterate over each character in "map"
    
        if (map[index] == '.'){                             //If the character is equal to '.' ...
            map[index] = to_permute[to_permute_index];      //...set it equal to the "to_permute" character being pointed at...
            to_permute_index++;                             //...and update the pointer
        }
    }
    
    populate_board(map);        //Use "map" as a blueprint for the game board.
}

/*****************************************************************************************************************************************************
** string choose_map()
** Opens a text file containing game board templates and randomly choses one.
******************************************************************************************************************************************************/
string Board::choose_map(){
    //Initialize and seed a random number engine
    std::default_random_engine rd;
    std::random_device seed_gen{};
    rd.seed(seed_gen());

    std::fstream map_file_stream;
    string map;
    map_file_stream.open("maps.txt");

    int num_maps;                       
    map_file_stream >> num_maps;        //First line of "maps.txt" should contain the number of templates.
    int choose_map = std::uniform_int_distribution<int>{1, num_maps}(rd);

    map_file_stream.ignore();
    for(int index=0; index < choose_map; index++){
        getline(map_file_stream, map);
    }
    
    if (map.length() != (ROWS * COLS)){
        throw string("ERROR: Map string length and number of board spaces must be the same size\n");
    }

    return map;
}

/*****************************************************************************************************************************************************
** populate_board(string board_template)
** Builds a game board based on a passed template. The template will be a string containing:
** - 1 'x' character
** - 1 '!' character
** - 2 'O' characters
** - 10 'e' characters
** - Enough 'A' and '.' characters so that the length of board_template equals (ROWS * COLS)

** This function modifies the "board" private data member (A 2D Space* vector) by populating it
** with pointers to various objects derived from Space, with the type of derived object being 
** determined by the template.
******************************************************************************************************************************************************/
void Board::populate_board(string board_template){
    bool first_tp_found = false;
    Space *tp1, *tp2;

    //Iterate over the template. Use the character to decide what type of pointer will be placed
    //in "board" at the location pointed to by "row" and "col".
    int row=-1, col= COLS - 1, number = 0;
    for (char icon : board_template){

        col++;
        if (col == COLS){
            col = 0;
            row++;
            std::vector<Space*> new_row(COLS);
            board.push_back(new_row);
        }

        switch(icon){
            case('A'):  {board[row][col] = new Mountain('A');
                        number++;
                        break;}
            
            case('.'):  {board[row][col] = new Blank('.');
                        number++;
                        break;}

            case('e'):  {board[row][col] = new Enemy('.');  //Enemies are hidden on the board, so both Enemy and Blank cells will appear identical
                        number++;
                        break;}
            
            case('x'):  {board[row][col] = new Blank('x');
                        number++;
                        player_start[0] = row;
                        player_start[1] = col;
                        break;}
            
            case('!'):  {board[row][col] = new Finish('!');
                        number++;
                        break;}
            
            case('O'):  {board[row][col] = new Teleport('O');
                        number++;
                        if (!first_tp_found){           //Each Teleport space must know where the other one is in order
                            tp1 = board[row][col];      //for them to work as intended.
                            first_tp_found = true;
                            break;
                        }
                        tp2 = board[row][col];
                        break;}
        }
    }

    //Link the two teleport spaces to each other.
    tp1->set_other_teleport(tp2);
    tp2->set_other_teleport(tp1);

    /*
    The following for-loops set the eight Space* pointers that each Space-derived object
    has as data members. The pointers for *board[r][c] would point to the following objects:

    top -          *board[r+1][c]
    bottom -       *board[r-1][c]
    left -         *board[r][c-1]
    right -        *board[r][c+1]
    top_left -     *board[r+1][c-1]
    top_right -    *board[r+1][c+1]
    bottom_left -  *board[r-1][c-1]
    bottom_right - *board[r-1][c+1]
    */


    //Set the "left" and "right" pointers of each space on the Board.
    for (int row = 0; row < ROWS; row++){
        for (int col = 0; col < (COLS - 1); col++){
            Space *space = board[row][col],
            *next_space = board[row][col + 1];

            space->setRight(next_space);
            next_space->setLeft(space);
        }
    }

    //Set the "up" and "down" pointers of each space on the Board
    for (int col = 0; col < COLS; col++){
        for (int row = 0; row < (ROWS - 1); row++){
            Space *space = board[row][col],
            *next_space = board[row + 1][col];

            space->setTop(next_space);
            next_space->setBottom(space);            
        }
    }

    //Set the "top_right" and "bottom_left" pointers of each space on the Board
    for (int row = 0; row < (ROWS - 1); row++){
        for (int col = 0; col < (COLS - 1); col++){
            Space *space = board[row][col],
            *next_space = board[row + 1][col + 1];

            space->setTopRight(next_space);
            next_space->setBottomLeft(space);            
        }
    }

    //Set the "top_left" and "bottom_right" pointers of each space on the Board
    for (int row = (ROWS - 1); row > 0; row--){
        for (int col = 0; col < (COLS - 1); col++){
            Space *space = board[row][col],
            *next_space = board[row - 1][col + 1];

            space->setBottomRight(next_space);
            next_space->setTopLeft(space);            
        }
    }
}

/*****************************************************************************************************************************************************
** showBoard()
** Displays the board in its current state to the player.
******************************************************************************************************************************************************/
void Board::showBoard(){
    for (int row = (ROWS - 1); row > -1; row--){
        for (int col = 0; col < COLS; col++){
            cout << board[row][col]->getSprite() << " ";
        }
        cout << endl;
    }
    cout << endl;
}

/*****************************************************************************************************************************************************
** ~Board()
** Frees the memory pointed to by the pointers in "board"
******************************************************************************************************************************************************/
Board::~Board(){
    for (int row=0; row < ROWS; row++){
        for (int col=0; col < COLS; col++){
            delete board[row][col];
        }
    }
}