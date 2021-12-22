#include <bits/stdc++.h>
#include "HEADERS\PRINTER.h"

using namespace std;


int main() {
    while (cin) {
        string s; cin>>s;
        for (auto& c : s) {
            if (c == '[') c = '{';
            else if (c == ']') c = '}';
        }
        cout<<s;
    }
    return 0;
}
