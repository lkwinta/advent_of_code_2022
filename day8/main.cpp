#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    //input file
    ifstream data("test.txt");

    string s_line;

    while(!data.eof()){
        if(data){
            data >> s_line;

        }
    }

    data.close();

    return 0;
}
