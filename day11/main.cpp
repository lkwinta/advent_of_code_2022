#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

struct Monkey {
    int number;
    vector<int> items;
    int (*op)(int, int);
    int argument;
    int test;

    int target_if_true;
    int target_if_false;
};

vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;

    size_t pos = s.find(delimiter);
    size_t old_pos = 0;

    while(pos != string::npos) {
        tokens.push_back(s.substr(old_pos, pos - old_pos));
        old_pos = pos + 1;
        pos =  s.find(delimiter, pos + 1);
    }
    tokens.push_back(s.substr(old_pos, pos - old_pos));

    return tokens;
}

int main() {
    //input file
    ifstream data("data.txt");

    string s_line;
    vector<Monkey> monkeys;
    Monkey monkey;

    while(!data.eof()){
        if(data){
            getline(data, s_line);
            if(s_line.empty()){
                monkeys.push_back(monkey);
                monkey.items.clear();
                monkey = {};
            } else {
                if (s_line.find("Monkey") != string::npos){
                    monkey.number = stoi(s_line.substr(7, s_line.length()-7));
                }
                else if(s_line.find("Starting items:") != string::npos){
                    size_t pos = s_line.find(':');
                    string items = s_line.substr(pos + 2, s_line.length() - pos - 2);
                    vector<string> items_split = split(items, ',');
                    for(auto& item : items_split){
                        monkey.items.push_back(stoi(item));
                    }
                } else if (s_line.find("Operation:") != string::npos){
                    size_t pos = s_line.find("old");
                    string op = s_line.substr(pos + 4, s_line.length() - pos - 4);
                    char operator_char = op[0];
                    string argument = op.substr(2, op.length() - 2);
                    if(operator_char == '+'){
                        monkey.op = [](int a, int b){return a + b;};
                    } else {
                        monkey.op = [](int a, int b) { return a * b; };
                    }
                    if(argument != "old")
                        monkey.argument = stoi(argument);
                    else
                        monkey.argument = -1;
                } else if(s_line.find("Test:") != string::npos){
                    size_t pos = s_line.find("by");
                    string test = s_line.substr(pos + 2, s_line.length() - pos -2);
                    monkey.test = stoi(test);
                } else if(s_line.find("If true:") != string::npos){
                    size_t pos = s_line.find("monkey");
                    string target = s_line.substr(pos + 6, s_line.length() - pos - 6);
                    monkey.target_if_true = stoi(target);
                } else if(s_line.find("If false:") != string::npos){
                    size_t pos = s_line.find("monkey");
                    string target = s_line.substr(pos + 6, s_line.length() - pos - 6);
                    monkey.target_if_false = stoi(target);
                }
            }
        }
    }
    monkeys.push_back(monkey);
    for(const Monkey& m: monkeys){
        cout << "Monkey: " << m.number << endl;
        cout << "Items: ";
        for(int item : m.items){
            cout << item << " ";
        }
        cout << endl;
        cout << "Argument: " << m.argument << endl;
        cout << "Test: " << m.test << endl;
        cout << "Target if true: " << m.target_if_true << endl;
        cout << "Target if false: " << m.target_if_false << endl;
        cout << endl;

    }

    int* count = new int[monkeys.size()]();

    for(int i = 0; i < 20; i++){
        for(Monkey& m: monkeys) {
            while(!m.items.empty()){
                count[m.number]++;
                int item = m.items.front();
                m.items.erase(m.items.begin());
                if(m.argument != -1)
                    item = m.op(item, m.argument);
                else
                    item = m.op(item, item);
                item /= 3;
                if(item % m.test == 0){
                    monkeys[m.target_if_true].items.push_back(item);
                } else {
                    monkeys[m.target_if_false].items.push_back(item);
                }
            }
        }
    }
    sort(count, count + monkeys.size());
    cout << count[monkeys.size() - 1] * count[monkeys.size() - 2] << endl;

    data.close();
    delete[] count;
    return 0;
}
