#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

struct pos{
    int row;
    int col;
};

bool operator < (const pos& lhs, const pos& rhs){
    return lhs.row < rhs.row || (lhs.row == rhs.row && lhs.col < rhs.col);
}
bool operator ==(const pos& lhs, const pos& rhs){
    return lhs.row == rhs.row && lhs.col == rhs.col;
}
pos operator - (const pos& lhs, const pos& rhs){
    return {lhs.row - rhs.row, lhs.col - rhs.col};
}

char getValue(const vector<string>&b, const pos& p){
    if(b[p.row][p.col] != 'S' && b[p.row][p.col] != 'E')
        return b[p.row][p.col];
    else if(b[p.row][p.col] == 'S')
        return 'a';
    else
        return 'z';
}
bool pos_good(const vector<string>&b, const pos& p){
    return p.row >= 0 && p.row < b.size() && p.col >= 0 && p.col < b[0].size();
}

map<pos, int> visited;


int shortest_path(vector<string>& map, pos current_pos, pos previous_pos, int steps = 0){
    visited[current_pos] = steps;
    if(!pos_good(map, current_pos)){
        return INT32_MAX;
    }
    if(visited.find(current_pos) != visited.end() && visited[current_pos] <= steps){
        return visited[current_pos];
    }

    char currentHeight = getValue(map, current_pos);
    if (currentHeight == 'E')
        return steps;

    int left_steps = INT32_MAX;
    int right_steps = INT32_MAX;
    int up_steps = INT32_MAX;
    int down_steps = INT32_MAX;
    //left
    if(previous_pos != current_pos - pos{0, 1}){
        pos left = current_pos - pos{0, 1};
        if(pos_good(map, left) && abs(getValue(map, left) - currentHeight) < 2){
            left_steps = shortest_path(map, left, current_pos, steps + 1);
        }
    }
    //right
    if(previous_pos != current_pos - pos{0, -1}){
        pos right = current_pos - pos{0, -1};
        if(pos_good(map, right) && abs(getValue(map, right) - currentHeight) < 2){
            right_steps = shortest_path(map, right, current_pos, steps + 1);
        }
    }
    //up
    if(previous_pos != current_pos - pos{1, 0}){
        pos up = current_pos - pos{1, 0};
        if(pos_good(map, up) && abs(getValue(map, up) - currentHeight) < 2){
            up_steps = shortest_path(map, up, current_pos, steps + 1);
        }
    }
    //down
    if(previous_pos != current_pos - pos{-1, 0}){
        pos down = current_pos - pos{-1, 0};
        if(pos_good(map, down) && abs(getValue(map, down) - currentHeight) < 2){
            down_steps = shortest_path(map, down, current_pos, steps + 1);
        }
    }

    return min(left_steps, min(right_steps, min(up_steps, down_steps)));
}

int main() {
    //input file
    ifstream data("test.txt");

    string s_line;

    pos start {0,0};
    bool start_found_flag = false;
    pos end {0,0};
    bool end_found_flag = false;
    vector<string> map;

    while(!data.eof()){
        if(data){
            data >> s_line;
            map.push_back(s_line);
            if(!start_found_flag ){
                size_t p = s_line.find('S');
                if(p != string::npos){
                    start.col = (int)p;
                    start_found_flag = true;
                }else{
                    start.row++;
                }
            }
            if(!end_found_flag ){
                size_t p = s_line.find('E');
                if(p != string::npos){
                    end.col = (int)p;
                    end_found_flag = true;
                }
                else{
                    end.row++;
                }
            }
        }
    }

    cout << "start: " << start.row << " " << start.col << endl;
    cout << "end: " << end.row << " " << end.col << endl;
    int steps = shortest_path(map, start, start);

    cout << steps << endl;
    data.close();

    return 0;
}
