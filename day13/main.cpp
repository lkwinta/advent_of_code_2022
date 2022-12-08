#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    //input file
    ifstream data("data.txt");

    string s_line;

    while(!data.eof()){
        if(data){
            data >> s_line;
        }
    }

    data.close();

    return 0;
}
