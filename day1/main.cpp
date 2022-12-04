#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    //input file
    ifstream data("data.txt");

    //one line of data
    string s_calories;
    int i_calories_sum = 0;
    vector<int> v_calories;

    //read file
    while(!data.eof()){
        getline(data, s_calories);
        if(!s_calories.empty()){
            i_calories_sum  += stoi(s_calories);
        } else {
            v_calories.push_back(i_calories_sum);
            i_calories_sum = 0;
        }
    }
    v_calories.push_back(i_calories_sum);
    sort(v_calories.begin(), v_calories.end());

    cout <<  v_calories[v_calories.size()-1] << endl;
    cout << v_calories[v_calories.size()-1] + v_calories[v_calories.size()-2] + v_calories[v_calories.size()-3] << endl;

    data.close();
    return 0;
}
