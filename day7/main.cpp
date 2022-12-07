#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

struct file {
    unsigned long long size = 0;
    string file_name;
};

struct directory {
    vector<directory> children;
    vector<file> files;

    directory* parent = nullptr;
    string directory_name = "/";

    unsigned long long size = 0;
};

directory catalogue;
directory* current_directory;

void command_parser(const string& str){
    string s_command = str.substr(0, 2);
    string s_argument;
    if(str.length() > 2){
        s_argument = str.substr(3, str.length() - 3);
    }
    if(s_command == "cd") {
        if(s_argument != "/" && s_argument != ".."){
            for(directory& d : current_directory->children){
                if(d.directory_name == s_argument){
                    current_directory = &d;
                    return;
                }
            }
            current_directory->children.push_back({.parent = current_directory, .directory_name=s_argument});
            current_directory = &current_directory->children.back();
        } else if (s_argument == "..") {
            current_directory = current_directory->parent;
        }
    }
}

void fill_sizes(directory& d){
    for(directory& child : d.children){
        fill_sizes(child);
        d.size += child.size;
    }
    for(file& f : d.files){
        d.size += f.size;
    }
}

void find_sizes(directory& d, unsigned long long max_size, vector<unsigned long long int>& result){
    if(d.size <= max_size){
        result.push_back(d.size);
    }
    for(directory& child : d.children){
        find_sizes(child, max_size, result);
    }
}

void find_sizes(directory& d, vector<unsigned long long int>& result){
    if(d.size > 0){
        result.emplace_back( d.size);
    }
    for(directory& child : d.children){
        find_sizes(child, result);
    }
}

int main() {
    current_directory = &catalogue;

    //input file
    ifstream data("data.txt");

    string s_line;

    while(!data.eof()){
        if(data){
            getline(data, s_line);
            if(s_line[0] == '$'){
                command_parser(s_line.substr(2, s_line.length() - 2));
            } else if (s_line.substr(0, 3) == "dir"){
                string name = s_line.substr(4, s_line.length()-4);
                current_directory->children.push_back({.parent = current_directory, .directory_name=name});
            } else {
                size_t pos = s_line.find(' ');
                string size = s_line.substr(0, pos);
                string name = s_line.substr(pos+1, s_line.length()-pos-1);

                current_directory->files.push_back({.size = stoull(size), .file_name=name});
            }
        }
    }

    fill_sizes(catalogue);
    vector<unsigned long long int> result;
    find_sizes(catalogue, 100000, result);

    unsigned long long int sum = 0;
    for(unsigned long long int i : result){
        sum += i;
    }

    unsigned long long int total_size = 70000000;
    unsigned long long int free_size = total_size - catalogue.size;
    unsigned long long int update_size = 30000000;
    unsigned long long int required_size = update_size-free_size;

    vector< unsigned long long int> sizes;
    find_sizes(catalogue, sizes);
    unsigned long long int min = 70000000;

    for(unsigned long long int p : sizes){
        if(p >= required_size && p < min){
            min = p;
        }
    }

    cout << sum << endl;
    cout << min << endl;

    data.close();
    return 0;
}
