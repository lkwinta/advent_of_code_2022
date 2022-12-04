#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

int main() {
    //input file
    ifstream data("data.txt");

    //one line of data
    string s_opponent;
    string s_response;

    int sum_of_priorities = 0;
    int sum_of_badges = 0;

    string rucksack;
    set<char> compartment_1;
    set<char> compartment_2;
    vector<char> intersection;

    //read file
    while(!data.eof()){
        if(data){
            data >> rucksack;
            size_t compartment_length = rucksack.length()/2;

            for (size_t i = 0; i < compartment_length; i++){
                compartment_1.insert(rucksack[i]);
                compartment_2.insert(rucksack[i+compartment_length]);
            }

            std::set_intersection(compartment_1.begin(), compartment_1.end(), compartment_2.begin(), compartment_2.end(),
                                  back_inserter(intersection));


            for(char c : intersection){
                if (c < 'a')
                    sum_of_priorities += (c - 'A' + 27);
                else
                    sum_of_priorities += (c - 'a' + 1);
            }

            compartment_1.clear();
            compartment_2.clear();
            intersection.clear();
        }
    }
    cout << sum_of_priorities << endl;

    data.close();

    string elf1;
    string elf2;
    string elf3;

    set<char> intersection_2;
    set<char> intersection_3;

    data.open("data.txt");
    while(!data.eof()){
        if(data){
            data >> elf1 >> elf2 >> elf3;
            set<char> set_elf1(begin(elf1), end(elf1));
            set<char> set_elf2(begin(elf2), end(elf2));
            set<char> set_elf3(begin(elf3), end(elf3));

            set_intersection(set_elf1.begin(), set_elf1.end(), set_elf2.begin(), set_elf2.end(), inserter(intersection_2, intersection_2.end()));
            set_intersection(set_elf3.begin(), set_elf3.end(), intersection_2.begin(), intersection_2.end(), inserter(intersection_3, intersection_3.end()));

            for(char c : intersection_3){
                if (c < 'a')
                    sum_of_badges += (c - 'A' + 27);
                else
                    sum_of_badges += (c - 'a' + 1);
            }

            intersection_2.clear();
            intersection_3.clear();
        }
    }

    cout << sum_of_badges << endl;

    data.close();

    return 0;
}
