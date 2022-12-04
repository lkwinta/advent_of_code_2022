#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

struct range{
    int begin;
    int end;
};

range convert(const string& s_range, char delimiter = '-'){
    size_t pos = s_range.find(delimiter);
    range result{};
    result.begin = stoi(s_range.substr(0, pos));
    result.end = stoi(s_range.substr(pos + 1, s_range.length() - pos));

    return result;
}

bool contains(range r1, range r2){
    if ((r1.begin <= r2.begin && r1.end >= r2.end) ||
            (r2.begin <= r1.begin && r2.end >= r1.end))
        return true;
    else
        return false;
}

bool overlaps(range r1, range r2){
    if (r1.end < r2.begin || r2.end < r1.begin)
        return false;
    return true;
}

int main() {
    //input file
    ifstream data("data.txt");

    string s_line;
    string s_elf1;
    string s_elf2;

    int count_contains = 0;
    int count_overlaps = 0;

    while(!data.eof()){
        if(data){
            data >> s_line;
            size_t pos = s_line.find(',');
            s_elf1 = s_line.substr(0, pos);
            s_elf2 = s_line.substr(pos + 1, s_line.length() - pos);

            range range_elf1 = convert(s_elf1);
            range range_elf2 = convert(s_elf2);

            count_contains += contains(range_elf1, range_elf2);
            count_overlaps += overlaps(range_elf1, range_elf2);
        }
    }

    cout << count_contains << endl;
    cout << count_overlaps << endl;

    data.close();

    return 0;
}
