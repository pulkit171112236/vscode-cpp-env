#ifndef READER_H
#define READER_H

#include <bits/stdc++.h>

using namespace std;

vector<int> toVector(string line) {
    vector<int> res;
    stringstream ss(line);
    while (ss.peek() == ' ' || ss.peek() == '\n') ss.ignore();
    if (ss.peek() == '[' || ss.peek() == '{' || ss.peek() == '(') ss.ignore();
    ss.peek();
    while (ss.good()) {
        while (ss.peek() == ' ') ss.ignore();
        if (ss.peek() == -1 || ss.peek() == ']' || ss.peek() == '}' ||
            ss.peek() == ')')
            break;
        string num;
        getline(ss, num, ',');
        res.push_back(stoi(num));
    }
    return res;
}
vector<int> readVec(string file_name = "input.txt") {
    ifstream in_file(file_name);
    string temp;
    getline(in_file, temp, ']');
    return toVector(temp);
}
vector<vector<int>> readMat(string file_name) {
    vector<vector<int>> mat;
    ifstream in_file(file_name);
    while (isblank(in_file.peek()) || in_file.peek() == '\n') in_file.ignore();
    if (in_file.peek() == '[' || in_file.peek() == '{' || in_file.peek() == '(')
        in_file.ignore();
    while (in_file.good()) {
        while (isblank(in_file.peek()) || in_file.peek() == '\n' ||
               in_file.peek() == ',')
            in_file.ignore();
        if (in_file.peek() == ']') break;
        string vec_input;
        getline(in_file, vec_input, ']');
        // cout<<"reading vec <"<<vec_input<<endl<<">\n";
        mat.push_back(toVector(vec_input));
        // cout<<"------------------\n";
    }
    return mat;
}

vector<string> readStrings(string file_name = "input.txt") {
    vector<string> res;
    ifstream in_file(file_name);
    while (in_file.good()) {
        while (in_file.peek() == ' ' || in_file.peek() == '\n')
            in_file.ignore();
        string s;
        getline(in_file, s, '\n');
        res.push_back(s);
        in_file.peek();
    }
    return res;
}
#endif