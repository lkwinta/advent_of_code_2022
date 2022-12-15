#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <stack>
#include <iomanip>

using namespace std;

struct Set {
    int data = -1;
    int next_length = 0;
    Set* next = nullptr;
    Set* previous = nullptr;

    void resize(){
        next_length++;
        next = (Set*)realloc(next, next_length * sizeof(Set));
        next[next_length - 1] = Set();
    }
};

struct Item{
    int data;
    int deepLevel;
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
            cout << head->next[i].data << " ";
        }
        else
            printSet(&head->next[i], deep + 1);
    }
}

void convertSetToVector(Set* head, vector<Item>& result, int deep = 0){
    if (head == nullptr) return;

    for (int i = 0; i  < head->next_length ; i++) {
        if(head->next[i].next == nullptr){
            result.push_back({head->next[i].data, deep});
        }
        else
            convertSetToVector(&head->next[i], result, deep + 1);
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

//implement enum as result type
enum VAL{
    SMALLER,
    EQUAL,
    GREATER,
};

VAL leftSmallerThanRight(Set* left, Set* right){
    if(left->next == nullptr && right->next == nullptr){
        if(left->data != -1 && right->data != -1)
            if(left->data > right->data)
                return GREATER;
            else if (left->data == right->data)
                return EQUAL;
            else
                return SMALLER;
        else
            if(left->data != -1 && right->data == -1)
                return GREATER;
            else
                return SMALLER;
    }
    else if(left->next != nullptr && right->next == nullptr){
        VAL result;
        for(int i = 0; i < left->next_length; i++){
            if(left->next[i].data == -1 && right->data==-1)
                return GREATER;
            result = leftSmallerThanRight(&left->next[i], right);
            if(result != EQUAL)
                return result;
        }
        return result;
    }
    else if(left->next == nullptr && right->next != nullptr){
        VAL result;
        for(int i = 0; i < right->next_length; i++){
            result = leftSmallerThanRight(left, &right->next[i]);
            if(result != EQUAL)
                return result;
        }
        return result;
    }
    else {
        VAL result;
        for(int i = 0; i < left->next_length && i < right->next_length; i++){
            result = leftSmallerThanRight(&left->next[i], &right->next[i]);
            if(result != EQUAL)
                return result;
        }

        if(result == EQUAL){
            if(left->next_length < right->next_length){
                return SMALLER;
            } else if ( left->next_length > right->next_length) {
                return GREATER;
            } else {
                return EQUAL;
            }
        }

        return result;
    }
}

int main() {
    //input file
    ifstream data("t.txt");

    string s_line;
    vector<Set*> sets;

    while(!data.eof()){
        if(data){
            data >> s_line;
            if (!s_line.empty())
            {
                Set* h = convertString(split(s_line, "[,]"));
                printSet(h);
                cout << endl;
                sets.push_back(h);
            }
        }
    }

    int index = 1;
    int sum = 0;
    for(int i = 1; i <  sets.size(); i+=2){
        VAL res = leftSmallerThanRight(sets[i-1], sets[i]);
        cout << "i: "  << index << " | res: " << (res==SMALLER )<< endl;
        sum += (res==SMALLER)*index;
        index++;
    }

    cout << "sum: " << sum << endl;

    data.close();

    return 0;
}
