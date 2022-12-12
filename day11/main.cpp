#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <set>

using namespace std;

//#define PART_1
#define PART_2

#ifdef PART_1
#define N 20
#elif defined PART_2
#define N 10000
#endif

struct Monkey {
    long long int number;
    vector<long long int> items;
    long long int (*op)(long long int, long long int);
    long long int argument;
    long long int test;

    long long int target_if_true;
    long long int target_if_false;
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

    long long int modulo = 1;

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
                        monkey.op = [](long long int a, long long int b){return a + b;};
                    } else {
                        monkey.op = [](long long int a, long long int b) { return a * b; };
                    }
                    if(argument != "old")
                        monkey.argument = stoi(argument);
                    else
                        monkey.argument = -1;
                } else if(s_line.find("Test:") != string::npos){
                    size_t pos = s_line.find("by");
                    string test = s_line.substr(pos + 2, s_line.length() - pos -2);
                    monkey.test = stoi(test);
                    modulo *= monkey.test;
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
        for(long long int item : m.items){
            cout << item << " ";
        }
        cout << endl;
        cout << "Op: ";
        if(m.op(2,3) == 5)
            cout << "+";
        else
            cout << "*";
        cout << endl;
        cout << "Argument: " << m.argument << endl;
        cout << "Test: " << m.test << endl;
        cout << "Target if true: " << m.target_if_true << endl;
        cout << "Target if false: " << m.target_if_false << endl;
        cout << "-------------------";
        cout << endl;
    }

    auto* count = new long long int[monkeys.size()]();

    for(long long int i = 0; i < N; i++){
        for(Monkey& m: monkeys) {
            while(!m.items.empty()){
                long long int item = m.items.front();
                m.items.erase(m.items.begin());
                count[m.number]++;
                if(m.argument != -1)
#ifdef PART_1
                    item = m.op(item, m.argument) % modulo;
#elif defined PART_2
                    item = m.op(item, m.argument) % modulo;
#endif
                else
#ifdef PART_1
                    item = m.op(item, item) % modulo;
#elif defined PART_2
                    item = m.op(item, item) % modulo;
#endif
#ifdef PART_1
                item /= 3;
#endif
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
    return 0;
}
