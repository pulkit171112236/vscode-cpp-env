#include <bits/stdc++.h>

// custom headers
#include "HEADERS\PRINTER.h"
#include "HEADERS\READER.h"
#include "HEADERS\mylib.h"

using namespace std;

int main() {
    // // declaring custom buffers
    // // ifstream cin("input.txt");
    // ofstream cout("output.txt");
    // // optional performance optimizations
    // ios_base::sync_with_stdio(false);
    // std::cin.tie(0);
    // // redirecting stdio to custom buffers
    // // std::cin.rdbuf(cin.rdbuf());
    // std::cout.rdbuf(cout.rdbuf());

    // generating the space
    ifstream dict_file("dict5.txt");
    set<string> dict_set;
    while (dict_file) {
        string word;
        dict_file >> word;
        dict_set.insert(word);
    }

    set<string> space = dict_set;
    string holder = "*****";
    set<char> absent[5];
    while (true) {
        // adding information to defined entities
        map<char, int> freq;
        string curr_word;
        cin >> curr_word;
        if (curr_word == "exit") break;
        string pattern;
        cin >> pattern;
        for (int i = 0; i < 5; i++) {
            char curr_letter = curr_word[i];
            char info = pattern[i];
            if (info == 'g') {
                holder[i] = curr_letter;
            } else if (info == 'b') {
                for (int i = 0; i < 5; i++) absent[i].insert(curr_letter);
            } else if (info == 'y') {
                absent[i].insert(curr_letter);
                freq[curr_letter]++;
            }
        }
        // generating the new space satisfying the entities
        set<string> new_space;
        for (auto word : space) {
            map<char, int> curr_freq;
            int i = 0;
            for (i = 0; i < 5; i++) {
                curr_freq[word[i]]++;
                if (holder[i] == '*') {
                    if (absent[i].count(word[i])) break;
                } else if (holder[i] != word[i])
                    break;
            }
            if (i == 5) {
                bool flag = true;
                for (auto el : freq) {
                    if (curr_freq[el.first] != el.second) {
                        flag = false;
                        break;
                    }
                }
                if (flag) new_space.insert(word);
            }
        }
        cout << new_space << endl;
        cout << "=======================================\n";
    }
    return 0;
}
