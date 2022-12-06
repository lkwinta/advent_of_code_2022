#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <map>

using namespace std;

vector<string> split(const string& str, char delimiter){
    vector<string> result;
    size_t pos = str.find(delimiter);
    size_t pos_old = 0;

    while(pos != string::npos){
        string s = str.substr(pos_old, pos - pos_old);
        //if(s.length() != 0)
            result.push_back(s);

        pos_old = pos + 1;
        pos = str.find(delimiter, pos_old);
    }
    result.push_back(str.substr(pos_old, str.length() - pos_old));
    return result;
}

struct command{
    char from;
    int how_many;
    char where;
};

int main() {
    //input file
    ifstream data("data.txt");

    string s_line;
    bool if_stack = false;

    queue<command> qc_commands;
    vector<string> vs_stack;
    map<char, vector<char>> mc_stack;
    vector<string> vs_command;

    while(!data.eof()){
        getline(data, s_line);
        if(!s_line.empty()){
            if(!if_stack){
                vs_stack.push_back(s_line);
            } else {
                vs_command = split(s_line, ' ');
                qc_commands.push({.from = vs_command[3][0], .how_many=stoi(vs_command[1]), .where = vs_command[5][0]});
            }
        } else {
            if_stack = true;
        }
    }

    for(int column = (int)vs_stack[vs_stack.size() - 1].length(); column >= 0; column--) {
        if(vs_stack.back()[column] != ' ' && vs_stack.back()[column] != '\0') {
            for (int row = (int)vs_stack.size() - 2; row >= 0; row--) {
                if (vs_stack[row].length() > column) {
                    if(vs_stack[row][column] != ' ')
                        mc_stack[vs_stack.back()[column]].push_back(vs_stack[row][column]);
                }
            }
        }
    }

    while(!qc_commands.empty()){
        command c = qc_commands.front();
        int size = (int)mc_stack[c.from].size();

        /*part1
        for(int i = size - -1; i >= size - c.how_many; i--){
            mc_stack[c.where].push_back(mc_stack[c.from][i]);
        }
        */

        //part2
        for(int i = size - c.how_many; i < size; i++){
            mc_stack[c.where].push_back(mc_stack[c.from][i]);
        }
        mc_stack[c.from].erase(mc_stack[c.from].end() - c.how_many, mc_stack[c.from].end());
        qc_commands.pop();
    }

    string output;

    for(pair<char, vector<char>> pair : mc_stack){
        output += pair.second.back();
    }

    cout << output << endl;

    data.close();

    return 0;
}
