#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

struct Position {
    int row;
    int column;
};

struct Move {
    char direction;
    int units;
};

Position operator+(const Position& a, const Position& b) {
    return {a.row + b.row, a.column + b.column};
}

bool operator==(const Position& a, const Position& b) {
    return a.row == b.row && a.column == b.column;
}

bool operator<(const Position& a, const Position& b) {
    return a.row < b.row || (a.row == b.row && a.column < b.column);
}

Position operator-(const Position& a, const Position& b) {
    return {a.row - b.row, a.column - b.column};
}

Position operator/(const Position& a, int b) {
    return {a.row / b, a.column / b};
}

Position operator%(const Position& a, int b) {
    return {a.row % b, a.column % b};
}

bool areTouching(const Position& a, const Position& b){
    int rangeLeft = a.row - 1;
    int rangeRight = a.row + 1;
    int rangeTop = a.column - 1;
    int rangeBottom = a.column + 1;

    return (b.row >= rangeLeft && b.row <= rangeRight) && (b.column >= rangeTop && b.column <= rangeBottom);
}

int main() {
    //input file
    ifstream data("data.txt");

    map<char, Position> moves;
    moves['U'] = {-1, 0};
    moves['D'] = {1, 0};
    moves['L'] = {0, -1};
    moves['R'] = {0, 1};

    char direction;
    int units;

    Position headPosition = {0, 0};
    Position tailPosition = {0, 0};

    set<Position> visited;
    vector<Move> movesList;

    while(!data.eof()){
        if(data){
            data >> direction >> units;

            movesList.push_back({direction, units});
        }
    }

    for(auto move : movesList){
        for(int i = move.units; i > 0; i--){
            headPosition = headPosition + moves[move.direction];
            if(!areTouching(headPosition, tailPosition)){
                tailPosition = headPosition - moves[move.direction];
            }
            visited.insert(tailPosition);
        }
    }
    size_t visitedCount1 = visited.size();

    visited.clear();
    Position rope[10] = {{0, 0}, {0, 0},{0,0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};

    for (auto move : movesList){
        for(int i = move.units; i > 0; i--){
            rope[0] = rope[0] + moves[move.direction];
            for(int k = 1; k < 10; k++){
                if(!areTouching(rope[k], rope[k - 1])){
                   Position diff = rope[k - 1] - rope[k];
                   rope[k] = rope[k] + diff/2 + diff%2;
                }
            }
            visited.insert(rope[9]);
        }

    }

    cout << visitedCount1 << endl;
    cout << visited.size() << endl;

    data.close();

    return 0;
}
