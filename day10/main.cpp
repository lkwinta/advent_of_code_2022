#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

enum OP_CODE {
    ADDX,
    NOOP
};

struct Instruction {
    OP_CODE opcode = NOOP;
    int cycles = 1;
    int argument = 0;
};

int main() {
    //input file
    ifstream data("data.txt");

    string s_line;
    string instruction;
    int argument;
    vector<Instruction> instructions;

    while(!data.eof()){
        if(data){
            getline(data, s_line);
            instruction = s_line.substr(0, 4);
            if(instruction == "addx")
                instructions.push_back({.opcode = ADDX, .cycles = 2, .argument = stoi(s_line.substr(5, s_line.length()-5))});
            else
                instructions.push_back({.opcode = NOOP, .cycles = 1, .argument = 0});
        }
    }

    int X = 1;
    int cycles = 1;
    map<int, int> x_value;
    x_value[1] = 1;
    for(auto& ins : instructions){
        if(ins.opcode == NOOP){
            cycles++;
            x_value[cycles] = X;
        } else {
            cycles++;
            x_value[cycles] = X;
            X += ins.argument;
            cycles++;
            x_value[cycles] = X;
        }
    }

    string screen[6];
    for(int k = 0; k < 6; k++) {
        for (int i = 0; i <= 39; i++) {
            if (x_value[40*k + i+1] == i || x_value[40*k + i+1] == i - 1 || x_value[40*k+i+1] == i +1)
                screen[k] += 'X';
            else
                screen[k] += '.';
        }
    }

    cout << x_value[20]*20 + x_value[60]*60 + x_value[100]*100 + x_value[140]*140 + x_value[180]*180 + x_value[220]*220<< endl;

    for(const string& s : screen)
        cout << s << endl;

    data.close();

    return 0;
}
