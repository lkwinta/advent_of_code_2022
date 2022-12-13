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

void printSet(Set* head){
    if(head == nullptr) return;
    if (head->next == nullptr){
        cout << head->data << " ";
        return;
    }
    reverse(head->next, head->next + head->next_length);

    for(int i = 0; i<head->next_length; i++){
        printSet(&head->next[i]);
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
            while(s.top() != "["){
                set_current->next_length++;
                set_current->next = (Set*)realloc(set_current->next, set_current->next_length * sizeof(Set));
                set_current->next[set_current->next_length - 1] = Set();
                set_current->next[set_current->next_length - 1].data = stoi(s.top());
                s.pop();
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
                set_current->next_length++;
                set_current->next = (Set*)realloc(set_current->next, set_current->next_length * sizeof(Set));
                set_current->next[set_current->next_length - 1] = Set();
                set_current->next[set_current->next_length - 1].previous = set_current;
                set_current = &set_current->next[set_current->next_length - 1];
            }
        }
        else {
            if(c != ",")
                s.push(c);
        }
    }

    return set_head;
}

int main() {
   // for(const string& s : split("[1,[2,[3,[4,[5,6,7]]]],8,9]", "[,]"))
     //   cout << s << "|";
    cout << endl;

    //input file
    ifstream data("test.txt");

    string s_line;

    while(!data.eof()){
        if(data){
            data >> s_line;
            if(!s_line.empty()){
                Set* h = convertString(split(s_line, "[,]"));
                vector<int> res;
                convertSetToVector(h, res);
                for(int i : res)
                    cout << i << " ";
                cout << endl;
            }
        }
    }

    data.close();

    return 0;
}
