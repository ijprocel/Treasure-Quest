/*****************************************************************************************************************************************************
** Author: Ignacio Procel
** Date: 11/15/19
** Description: This is the implementation file for the menu function. It contains a function that
** checks if a user's response to a prompt corresponds to a list of multiple choice options,
** and one that checks if an integer response lies within an upper and lower bound.
******************************************************************************************************************************************************/
#include "menu.hpp"

bool checkInt(string);                                  //Returns true if passed a string containing only numeric characters

/*******************************************************************************************************************************************************
** A function used to validate multiple choice input. It takes the following parameters:
** response - A string passed by reference, will hold the validated response
** choices - An array populated with the list of acceptable user inputs
** num_choices - The number of acceptable choices there are
** error_mess - The error message to be displayed when the user gives an invalid response
*******************************************************************************************************************************************************/
void ValidateMultChoice(string &response, string *choices, int num_choices, string error_mes){
    bool goodResponse=false;
    do{
        getline(cin, response);
        for (int index=0; index < num_choices; index++){        //Loop through the list of acceptable responses
            if (response == choices[index]){                    //If the input response matches one of them...
                goodResponse = true;                            //...update the bool that will break the loop
            }
        }
        
        if (!goodResponse){                                     //Otherwise, display the error message...
            cout << error_mes;
        }
    } while(!goodResponse);                                     //...and run the loop again.
}

/*******************************************************************************************************************************************************
** A function used to reset the controls. Validates that the user's input is in the list of acceptable
** inputs and then erases it from the list.
*******************************************************************************************************************************************************/
string ValidateNewControls(vector<string>& choices, int num_choices, string error_mes){
    bool goodResponse=false;
    string response;
    do{
        getline(cin, response);
        for (int index=0; index < num_choices; index++){        //Loop through the list of acceptable responses
            if (response == choices[index]){                    //If the input response matches one of them...
                goodResponse = true;                            //...update the bool that will break the loop
                choices.erase(choices.begin() + index);
                return response;
            }
        }
        
        if (!goodResponse){                                     //Otherwise, display the error message...
            cout << error_mes;
        }
    } while(!goodResponse);                                     //...and run the loop again.
}

/*******************************************************************************************************************************************************
** The ValidateInt main function and checkInt helper function are used to validate user integer input.
** ValidateInt takes three parameters:
** final          - an integer by reference that will be used to store the final output
** ubound, lbound - The (inclusive) range that the input must fall into.
*******************************************************************************************************************************************************/
void ValidateInt(int& final, int lbound, int ubound){
    string response; 
    std::istringstream int_stream;
    bool goodResponse = false;
    do{
        //Read in the user's response
        getline(cin, response);                         
        
        //If there are no non-numeric characters, aside from a negative sign...
        if (checkInt(response)){
            
            //...convert the input to an integer
            int_stream.str(response);
            int_stream >> final;
            int_stream.clear();

            //...and test it against the upper and lower bounds
            if (final <= ubound && final >= lbound){
                goodResponse = true;
            }
        }
        //Display the error message if not all tests were passed
        if (!goodResponse){
            cout << "Response must be an integer between " << lbound 
            << " and " << ubound << " inclusive\nEnter: "; 
        }

    }while (!goodResponse);
}

bool checkInt(string el_string){
    //If the first character is neither a digit nor a negative sign, return false
    if (!isdigit(el_string[0]) && el_string[0] != '-'){           
        return false;
    }

    //If any of the remaining characters are non-numeric, return false
    for (char character : el_string.substr(1, el_string.length())){
        if (!isdigit(character)){           
            return false;
        }
    }
    return true;
}