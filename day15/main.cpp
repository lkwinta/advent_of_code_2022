#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct Position {
    int x;
    int y;
};

struct Record {
    Position sensor;
    Position beacon;
};

struct Range {
    int start;
    int end;

    [[nodiscard]] int getElements() const {
        if(start <= 0 && end >= 0)
            return abs(start-end)+1;
        return abs(start-end);
    }
};

bool operator <(Range a, Range b){
    return a.start < b.start || (a.start == b.start && a.end < b.end);
}

vector<string> split(const string& str, char delimiter){
    size_t pos = str.find(delimiter);
    size_t old_pos = 0;
    vector<string> result;

    while(pos != string::npos){
        result.push_back(str.substr(old_pos, pos-old_pos));
        old_pos = pos + 1;
        pos = str.find(delimiter, pos + 1);
    }
    result.push_back(str.substr(old_pos, pos-old_pos));

    return result;
}

int manhattan_distance(Position a, Position b){
    return abs(a.x-b.x) + abs(a.y-b.y);
}

vector<Range> reduce_range(vector<Range> ranges){
    vector<Range> result;
    sort(ranges.begin(), ranges.end());

    Range temp {ranges[0].start, ranges[0].end};

    for(int i = 1; i < ranges.size(); i++){
        if(ranges[i].start <= temp.end || ranges[i].start == temp.end + 1) {
            if (ranges[i].end > temp.end)
                temp.end = ranges[i].end;
        }
        else {
            result.push_back(temp);
            temp = ranges[i];
        }
    }
    result.push_back(temp);

    return result;
}

int main() {
    //input file
    ifstream data("data.txt");

    string s_line;
    vector<Record> records;

    while(!data.eof()){
        if(data){
            getline(data, s_line);

            auto line_split = split(s_line, ' ');

            records.push_back({
            {
            stoi(split(line_split[2].erase(line_split[2].length() - 1), '=')[1]),
            stoi(split(line_split[3].erase(line_split[3].length() - 1), '=')[1])
            },
            {
            stoi(split(line_split[8].erase(line_split[8].length()-1), '=')[1]),
            stoi(split(line_split[9], '=')[1])
            }
            });
        }
    }

    int line_number = 2000000;
    int max_line = 4000000;

    //int line_number = 10;
    //int max_line = 20;


    map<int, int> beacons;

    vector<Range> ranges;

    for(auto record : records){
        int distance = manhattan_distance(record.sensor, record.beacon);
        int required_distance = abs(line_number - record.sensor.y);

        if(record.sensor.y == line_number)
            ranges.push_back({record.sensor.x, record.sensor.x});
        if(record.beacon.y == line_number)
            beacons[record.beacon.x] = 1;

        if(required_distance <= distance){
            int radius = distance - required_distance;
            ranges.push_back({record.sensor.x - radius, record.sensor.x + radius});
        }
    }
    ranges = reduce_range(ranges);
    int sum = 0;
    for(auto r : ranges)
        sum += r.getElements();
    ranges.clear();
    Position beacon_found{};

    for(int i = 0; i <= max_line; i++){
        for(auto record : records){
            int distance = manhattan_distance(record.sensor, record.beacon);
            int required_distance = abs(i - record.sensor.y);

            if(record.sensor.y == i)
                ranges.push_back({record.sensor.x, record.sensor.x});

            if(required_distance <= distance){
                int radius = distance - required_distance;
                ranges.push_back({record.sensor.x - radius, record.sensor.x + radius});
            }
        }
        ranges = reduce_range(ranges);


        if(ranges.size() > 1) {
            for(int k = 1; k < ranges.size(); k++){
                if(ranges[k].start - ranges[k-1].end == 2){
                    int x_pos = (ranges[1].start + ranges[0].end)/2;
                    if(x_pos >= 0 and x_pos <= 4000000) {
                        beacon_found = {x_pos, i};
                        break;
                    }
                }
            }
        }
        ranges.clear();
    }

    unsigned long long int signal_strength = ((unsigned long long int)beacon_found.x) * 4000000 + beacon_found.y;

    cout << sum - beacons.size() << endl;
    cout << signal_strength << endl;

    data.close();

    return 0;
}
