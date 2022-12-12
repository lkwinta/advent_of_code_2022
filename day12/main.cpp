#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <chrono>

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
pos operator + (const pos& lhs, const pos& rhs){
    return {lhs.row + rhs.row, lhs.col + rhs.col};
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


void shortest_path(vector<string>& map, pos current_pos, pos previous_pos, int steps = 0, bool reverse = false){
    if(!pos_good(map, current_pos))
        return;
    if(current_pos == previous_pos)
        return;
    if(!reverse && steps != 0 && getValue(map,current_pos) - getValue(map, previous_pos) >= 2 )
        return;
    if(reverse && steps != 0 && getValue(map,current_pos) - getValue(map, previous_pos) <= -2 )
        return;
    if(visited.find(current_pos) != visited.end() && visited[current_pos] <= steps)
        return;

    visited[current_pos] = steps;

    shortest_path(map, current_pos + pos{0, -1}, current_pos, steps + 1, reverse);
    shortest_path(map, current_pos + pos{0, 1}, current_pos, steps + 1, reverse);
    shortest_path(map, current_pos + pos{-1, 0}, current_pos, steps + 1, reverse);
    shortest_path(map, current_pos + pos{1, 0}, current_pos, steps + 1, reverse);
}

int main() {
    //input file
    ifstream data("data.txt");

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

    shortest_path(map, start, pos{-1, -1});
    cout << visited[end] << endl;

    int min_dist = visited[end];

    visited.clear();
    shortest_path(map, end, pos{-1, -1}, 0,true);

    for(int i = 0; i < map.size(); i++){
        for(int j = 0; j < map[0].length(); j++){
            if(getValue(map, pos{i, j}) == 'a'){
                int dist = visited[pos{i, j}];
                if(dist != 0 && dist < min_dist)
                    min_dist = dist;
            }
        }
    }

    cout << min_dist;

    data.close();

    return 0;
}
