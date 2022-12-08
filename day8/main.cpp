#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

bool is_visible(const vector<string>& forest, int row, int column){
    bool left_ok = true;
    bool right_ok = true;
    bool up_ok = true;
    bool down_ok = true;

    char height = forest[row][column];

    for(int i = column - 1; i >= 0; i--){
        if(forest[row][i] >= height){
            left_ok = false;
            break;
        }
    }

    for(int i = column + 1; i < forest[row].size(); i++){
        if(forest[row][i] >= height){
            right_ok = false;
            break;
        }
    }

    for(int i = row - 1; i >= 0; i--){
        if(forest[i][column] >= height){
            up_ok = false;
            break;
        }
    }

    for(int i = row + 1; i < forest.size(); i++){
        if(forest[i][column] >= height){
            down_ok = false;
            break;
        }
    }

    return left_ok || right_ok || up_ok || down_ok;
}

int calc_scenic_score(const vector<string>& forest, int row, int column){
    int distance_left = 0;
    int distance_right = 0;
    int distance_up = 0;
    int distance_down = 0;

    char height = forest[row][column];

    for(int i = column - 1; i >= 0; i--){
        distance_left++;
        if(forest[row][i] >= height){
            break;
        }
    }

    for(int i = column + 1; i < forest[row].size(); i++){
        distance_right++;
        if(forest[row][i] >= height) {
            break;
        }
    }

    for(int i = row - 1; i >= 0; i--){
        distance_up++;
        if(forest[i][column] >= height){
            break;
        }
    }

    for(int i = row + 1; i < forest.size(); i++){
        distance_down++;
        if(forest[i][column] >= height){
            break;
        }
    }

   // cout << distance_left << " " << distance_right << " " << distance_up << " " << distance_down << endl;

    return distance_down * distance_up * distance_left * distance_right;
}

int main() {
    //input file
    ifstream data("data.txt");

    string s_line;
    vector<string> vs_lines;

    while(!data.eof()){
        if(data){
            data >> s_line;
            vs_lines.push_back(s_line);
        }
    }

    int columns = (int)vs_lines[0].size();
    int rows = (int)vs_lines.size();

    int trees_outside = 2*columns + 2*rows - 4;
    int highest_score = 0;

    for(int i = 1; i < rows - 1; i++){
        for(int j = 1; j < columns - 1; j++){
            trees_outside += is_visible(vs_lines, i, j);

            int score = calc_scenic_score(vs_lines, i, j);

            if(score > highest_score){
                highest_score = score;
            }
        }
    }

    //cout << calc_scenic_score(vs_lines, 1, 2) << endl;

    cout << trees_outside << endl;
    cout << highest_score << endl;

    data.close();

    return 0;
}
