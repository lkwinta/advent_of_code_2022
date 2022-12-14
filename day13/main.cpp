#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <stack>
#include <iomanip>

using namespace std;

struct Set {
    int data = 0;
    int next_length = 0;
    Set* next = nullptr;
    Set* previous = nullptr;

    void resize(){
        next_length++;
        next = (Set*)realloc(next, next_length * sizeof(Set));
        next[next_length - 1] = Set();
    }
};

vector<string> split(const string& str, const string& delimiter){
    vector<string> result;
    size_t current_pos = 0;
    size_t last_pos = 0;

    for(char c : str){
        if(delimiter.find(c) != string::npos){
            string temp = str.substr(last_pos, current_pos - last_pos);
            if(!temp.empty())
                result.push_back(temp);
            result.emplace_back(1, c);
            last_pos = current_pos + 1;
        }

        current_pos++;
    }
    return result;
}

void printSet(Set* head, int deep = 0){
    if(head == nullptr) return;
    for (int i = 0; i < head->next_length ; i++) {
        if(head->next[i].next == nullptr){
            cout << head->next[i].data << "(" << deep << ")" << " ";
        }
        else
            printSet(&head->next[i], deep + 1);
    }
}

void convertSetToVector(Set* head, vector<int>& result){
    if (head == nullptr) return;

    for (int i = 0; i  < head->next_length ; i++) {
        if(head->next[i].next == nullptr){
            result.push_back(head->next[i].data);
        }
        else
            convertSetToVector(&head->next[i], result);
    }
}

Set* convertString(const vector<string> &input){
    stack<string> s;

    Set *set_head = nullptr;
    Set *set_current = nullptr;

    for(const string& c : input){
        if(c == "]"){
            int temp_len = set_current->next_length - 1;
            while(s.top() != "["){
                if(set_current->next[temp_len].next_length == 0) {
                    set_current->next[temp_len].data = stoi(s.top());
                    s.pop();
                }
                temp_len--;
            }
            s.pop();
            set_current = set_current->previous;
        }
        else if (c == "["){
            s.push(c);

            if(set_head == nullptr){
                set_head = new Set();
                set_current = set_head;
            }
            else{
                set_current->resize();
                set_current->next[set_current->next_length - 1].previous = set_current;
                set_current = &set_current->next[set_current->next_length - 1];
            }
        }
        else {
            if(c != ",") {
                s.push(c);
                set_current->resize();
            }
        }
    }

    return set_head;
}

int main() {
    //input file
    ifstream data("test.txt");

    string s_line;
    vector<pair<Set*, Set*>> pairs;
    Set* h1 = nullptr;
    Set* h2 = nullptr;

    while(!data.eof()){
        if(data){
            data >> s_line;
                Set* h = convertString(split(s_line, "[,]"));
                if(h1 == nullptr)
                    h1 = h;
                else if(h2 == nullptr)
                    h2 = h;
                else {
                    pairs.emplace_back(h1, h2);
                    h1 = h2 = nullptr;
                }

        }
    }

    data.close();

    return 0;
}
