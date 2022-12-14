#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

struct Point2D {
    int x;
    int y;
};

struct Line2D {
    Point2D start;
    Point2D end;
};

struct Sand {
    Point2D pos;

    bool move(string map[500]){
        if(map[pos.y+1][pos.x] != '#' && map[pos.y+1][pos.x] != 'o'){
            map[pos.y+1][pos.x] = 'o';
            map[pos.y][pos.x] = '.';
            pos.y++;
            return true;
        } else if (map[pos.y+1][pos.x-1] != '#' && map[pos.y+1][pos.x-1] != 'o'){
            map[pos.y+1][pos.x-1] = 'o';
            map[pos.y][pos.x] = '.';
            pos.y++;
            pos.x--;
            return true;
        } else if (map[pos.y+1][pos.x+1] != '#' && map[pos.y+1][pos.x+1] != 'o'){
            map[pos.y+1][pos.x+1] = 'o';
            map[pos.y][pos.x] = '.';
            pos.y++;
            pos.x++;
            return true;
        } else
            return false;
    }
};

vector<Line2D> parseLine(const string& line){
    size_t pos = line.find("->");
    size_t old_pos = 0;
    vector<string> pairs;
    vector<Point2D> points;
    vector<Line2D> lines;

    while(pos != string::npos){
        pairs.push_back(line.substr(old_pos, pos - old_pos));
        old_pos = pos + 3;
        pos = line.find("->", old_pos + 2);
    }
    pairs.push_back(line.substr(old_pos, pos - old_pos));

    for(string& s : pairs){
        pos = s.find(',');
        points.push_back({stoi(s.substr(0, pos)), stoi(s.substr(pos+1, s.length() - pos))});
    }

    for(size_t i = 1; i < points.size(); i++){
        lines.push_back({points[i - 1], points[i]});
    }

    return lines;
}

int sign(int n){
    if (n > 0)
        return 1;
    else if(n < 0)
        return -1;
    else
        return 0;
}

int main() {
    //input file
    ifstream data("data.txt");
    ofstream out("out.txt");

    string s_line;

    string map[500];
    for(auto & i : map){
        i.append(1000, '.');
    }

    int max_y = 0;

    while(!data.eof()){
        if(data){
            getline(data, s_line);
            vector<Line2D> lines = parseLine(s_line);
            for(Line2D line : lines){
                for(int i = 0; i <= abs(line.end.y - line.start.y); i++)
                    map[line.start.y + i*sign(line.end.y - line.start.y)][line.start.x ] = '#';
                for(int i = 0; i <= abs(line.end.x - line.start.x); i++)
                    map[line.start.y][line.start.x + i*sign(line.end.x - line.start.x) ] = '#';

                if(line.start.y > max_y)
                    max_y = line.start.y;
                if(line.end.y > max_y)
                    max_y = line.end.y;
            }
        }
    }

    for(int i = 0; i < 1000; i++){
        map[max_y+2][i] = '#';
    }

    Sand currentSand = {{500, 0}};
    int sand_counter = 0;
    int sand_counter_2 = 0;
    while(currentSand.pos.y < max_y) {
        currentSand = {{500, 0}};
        while (currentSand.move(map) && currentSand.pos.y < max_y);
        sand_counter++;
        sand_counter_2++;
    }

    while (currentSand.move(map));

    while(map[0][500] != 'o'){
        currentSand = {{500, 0}};
        map[0][500] = 'o';
        while (currentSand.move(map));
        sand_counter_2++;
    }

    data.close();
    for(auto & i : map){
        out << i << endl;
    }
    out.close();
    cout << sand_counter - 1 << endl;
    cout << sand_counter_2 << endl;

    return 0;
}
