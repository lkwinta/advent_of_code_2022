#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    //input file
    ifstream data("data.txt");

    string s_line;

    while(!data.eof()){
        if(data){
            getline(data, s_line);

        }
    }

    data.close();

    return 0;
}
