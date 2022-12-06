#include <iostream>
#include <fstream>
#include <string>
#include <set>


using namespace std;

struct fourth{
    char a;
    char b;
    char c;
    char d;
};

bool is_distinct(fourth f){
    return f.a != f.b && f.a != f.c && f.a != f.d && f.b != f.c && f.b != f.d && f.c != f.d;
}

bool is_distinct(const char* tab, int len){
    set<char> s;
    for(int i = 0; i < len; i++) {
        s.insert(tab[i]);
    }
    if(s.size() == len)
        return true;
    return false;
}

int main() {
    //input file
    ifstream data("data.txt");

    string s_input;

    data >> s_input;
    fourth f = {s_input[0], s_input[1], s_input[2], s_input[3]};
    for(size_t i = 4; i < s_input.length(); i++){
        f.a = f.b;
        f.b = f.c;
        f.c = f.d;
        f.d = s_input[i];
        if(is_distinct(f)){
            cout << i + 1 << endl;
            break;
        }
    }
    const char* tab;

    for(size_t i = 14; i < s_input.length(); i++){
        tab = s_input.substr(i - 14, 14).c_str();
        if(is_distinct(tab, 14)){
            cout << i << endl;
            break;
        }
    }

    data.close();

    return 0;
}
