#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

struct Item {
    char wins_to;
    char loses_to;
};

int main() {
    map<char, Item> items;
    //Rock(X) wins to Scissors(C) and loses Paper(B)
    items['A'] = {.wins_to = 'C', .loses_to = 'B'};
    //Paper(Z) wins to Rock(A) and loses Scissors(C)
    items['B'] = {.wins_to = 'A', .loses_to = 'C'};
    //Scissors(Z) wins to Paper(B) and loses Rock(A)
    items['C'] = {.wins_to = 'B', .loses_to = 'A'};

    //input file
    ifstream data("data.txt");

    //one line of data
    string s_opponent;
    string s_response;

    int score = 0;
    int score_2 = 0;

    //read file
    while(!data.eof()){
        if(data){
            data >> s_opponent >> s_response;
            char c_response = (char)((s_response[0] - 'X') + 'A');

            score += c_response - 'A' + 1;
            if(items[c_response].wins_to == s_opponent[0])
                score += 6;
            else if(items[c_response].loses_to == s_opponent[0])
                score += 0;
            else
                score += 3;

            char correct_play;
            if(s_response[0] == 'X'){
                //LOSS
                score_2 += 0;
                correct_play = items[s_opponent[0]].wins_to;
            } else if (s_response[0] == 'Y'){
                //DRAW
                score_2 += 3;
                correct_play = s_opponent[0];
            } else {
                //WIN
                score_2 += 6;
                correct_play = items[s_opponent[0]].loses_to;
            }
            score_2 += correct_play - 'A' + 1;
        }
    }
    cout << score << endl;
    cout << score_2 << endl;

    data.close();
    return 0;
}
