#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <windows.h>

using namespace std;

int main() {
    //input file
    ifstream data("data.txt");

    string s_line;

   /* while(!data.eof()){
        if(data){
            data >> s_line;
        }
    }*/

    string tab[5];
    tab[0] = "................................................";
    tab[1] = "................................................";
    tab[2] = "................................................";
    tab[3] = "................................................";
    tab[4] = "................................................";

    for(int i = 0; i < tab[0].length(); i++){
        tab[2][i] = 'o';
        for(int j = 0; j < 5; j++){
            std::cout << tab[j] << endl;
        }
        Sleep(500);
        std::cout << std::flush;
        tab[2][i] = '.';

    }

    data.close();

    return 0;
}
