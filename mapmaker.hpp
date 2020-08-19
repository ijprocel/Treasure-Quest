/*****************************************************************************************************************************************************
** Author: Ignacio Procel
** Date: 12/10/19
** Description: This contains the code that creates the playable maps for Treasure Quest. Maps had to be made manually to avoid
** an unplayable map being randomly generated.
*****************************************************************************************************************************************************/
#include <iostream>
#include <string>
#include <fstream>

using std::string;
using std::fstream;

/*****************************************************************************************************************************************************
** main()
******************************************************************************************************************************************************/
void get_maps(string*);

int write_maps(){
    const int NUM_MAPS = 10;

    string maps[NUM_MAPS];
    get_maps(maps);

    fstream file_stream;
    file_stream.open("maps.txt", fstream::out);

    file_stream << NUM_MAPS << "\n";

    for (int index=0; index < NUM_MAPS; index++){
        file_stream << maps[index] << "\n";
    }

    file_stream.close();
}
void get_maps(string* maps){
    maps[0] = "......"
              ".AA..."
              "...A.A"
              ".A...."
              "AAA..."
              "...A..";
    
    maps[1] = ".A..A."
              "A....."
              "...A.A"
              ".A...."
              "A.A..."
              ".A.A..";

    maps[2] = ".....A"
              ".AA..A"
              ".A.A.."
              ".....A"
              "..A..A"
              "....A.";

    maps[3] = ".A..A."
              "..A..."
              "..AA.A"
              "...A.."
              "A.A..."
              "....A.";
    
    maps[4] = "....A."
              "AA...."
              ".A..A."
              "..AA.."
              "A....."
              "...A..";
    
    maps[5] = "A....."
              "AA...."
              "A...AA"
              "....A."
              "....A."
              "......";
    
    maps[6] = "......"
              "..AA.."
              "A.A..."
              "..AA.."
              ".A..A."
              "...A..";
    
    maps[7] = "...A.."
              "..AA.."
              "A.A..."
              "......"
              "AAA.A."
              "......";

    maps[8] = "A...A."
              ".A...."
              ".AA..."
              "..AA.."
              "....A."
              "......";
    
    maps[9] = "......"
              "..AA.."
              ".A..A."
              "..AA.."
              ".A...."
              "...A..";
}