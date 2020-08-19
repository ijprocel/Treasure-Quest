/*****************************************************************************************************************************************************
** Author: Ignacio Procel
** Date: 11/15/19
** Description: This is the interface file for the menu function. It contains a function that
** checks if a user's response to a prompt corresponds to a list of multiple choice options,
** and one that checks if an integer response lies within an upper and lower bound.
******************************************************************************************************************************************************/
#ifndef MENU_HPP 
#define MENU_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

void ValidateInt(int& final, int lbound, int ubound);
void ValidateMultChoice(string &response, string *choices, int num_choices, string error_mes);
string ValidateNewControls(vector<string>& choices, int num_choices, string error_mes);
#endif
