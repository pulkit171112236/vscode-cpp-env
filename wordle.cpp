#include <bits/stdc++.h>
using namespace std;

#define COMMON_THRESHHOLD 3
#define WORD_SIZE 5

void printSet(set<string>& s) {
    for (auto word : s) {
        cout << word << " ";
    }
    cout << "\n";
}

int game(set<string>& dict_set, set<string>& dict_common) {
    cout << "===================== WORDLE-HELPER ======================\n";

    // space is the referenced dictionary which is assumed to include all possible solutions
    set<string> space = dict_set;

    // entitie to filter the space
    string holder = "*****";
    set<char> absent[5];

    // adding information to defined entities based on choice and pattern
    while (true) {
        map<char, int> freq;
        string choice;
        cout << "add-info: ";
        cin >> choice;

        // exit
        if (choice == "exit")
            return 0;

        // restart
        else if (choice == "restart" || choice == "reset")
            return 1;

        // else continue the game
        string pattern;
        cin >> pattern;

        if (choice.size() != 5 || pattern.size() != 5) {
            cout << "invalid input\n";
            continue;
        }
        for (int i = 0; i < WORD_SIZE; i++) {
            char curr_letter = choice[i];
            char info = pattern[i];
            if (info == 'g') {
                holder[i] = curr_letter;
            } else if (info == 'b') {
                for (int i = 0; i < WORD_SIZE; i++) absent[i].insert(curr_letter);
            } else if (info == 'y') {
                absent[i].insert(curr_letter);
                freq[curr_letter]++;
            }
        }
        // generating the new space satisfying the entities
        set<string> new_space;
        set<string> common;
        for (auto word : space) {
            map<char, int> curr_freq;
            int i = 0;
            for (i = 0; i < WORD_SIZE; i++) {
                curr_freq[word[i]]++;
                if (holder[i] == '*') {
                    if (absent[i].count(word[i])) break;
                } else if (holder[i] != word[i])
                    break;
            }
            if (i == WORD_SIZE) {
                bool flag = true;
                for (auto el : freq) {
                    if (curr_freq[el.first] < el.second) {
                        flag = false;
                        break;
                    }
                }
                if (flag) {
                    new_space.insert(word);
                    if (dict_common.count(word)) {
                        common.insert(word);
                    }
                }
            }
        }
        space = new_space;
        cout << "common: ";
        printSet(common);
        if (common.size() <= COMMON_THRESHHOLD) {
            cout << "all: ";
            printSet(space);
        }
        cout << "----------------------------------------------------\n";
    }
}

int main() {
    // generating the space
    ifstream dict_file("dict5.txt");
    ifstream dict_common_file("dict5_common.txt");
    set<string> dict_set;
    set<string> dict_common_set;
    while (dict_file) {
        string word;
        dict_file >> word;
        dict_set.insert(word);
    }
    while (dict_common_file) {
        string word;
        dict_common_file >> word;
        dict_common_set.insert(word);
    }
    while (game(dict_set, dict_common_set)) {
    }
    return 0;
}
