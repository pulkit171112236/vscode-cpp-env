#ifndef PRINTER_H
#define PRINTER_H

#include <bits/stdc++.h>

#define INS_DASH cout << "----------------------------------------\n";
#define DL(i) cout << "_______line_" << i << "______________\n";

using namespace std;

/////////// PRINT PAIR /////////////////////////////////////////////////
template <typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& _pair) {
    os << "(" << _pair.first << ", " << _pair.second << ")";
    return os;
}

/////////// PRINT TUPLE /////////////////////////////////////////////////
template <typename T1, typename T2, typename T3>
ostream& operator<<(ostream& os, const tuple<T1, T2, T3>& _tuple) {
    os << "[" << get<0>(_tuple) << ", " << get<1>(_tuple) << ", "
       << get<2>(_tuple) << "]";
    return os;
}

////////// PRINT VECTOR //////////////////////////////////////////////////
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& vec) {
    os << "[ ";
    for (auto elem : vec) {
        // if (elem == INT_MAX) os<<"+inf ";
        // else if (elem == INT_MIN) os << "-inf ";
        // else
        os << elem << "  ";
    }
    os << "]";
    return os;
}
//////// PRINT UNORDERD_SET////////////////////////////////////////////
template <typename T>
ostream& operator<<(ostream& os, unordered_set<T>& _uset) {
    os << "[ ";
    for (auto elem : _uset) {
        os << elem << "  ";
    }
    os << "]";
    return os;
}
///// PRINT ORDERED_SET//////////////////////////
template <typename T>
ostream& operator<<(ostream& os, set<T>& _uset) {
    os << "[ ";
    for (auto elem : _uset) {
        os << elem << "  ";
    }
    os << "]";
    return os;
}
///// PRINT ORDERED_SET//////////////////////////
template <typename T, typename T2>
ostream& operator<<(ostream& os, set<T, T2>& _uset) {
    os << "[ ";
    for (auto elem : _uset) {
        os << elem << "  ";
    }
    os << "]";
    return os;
}
///// PRINT ORDERED_SET//////////////////////////
template <typename T, typename T2>
ostream& operator<<(ostream& os, multiset<T, T2>& _uset) {
    os << "[ ";
    for (auto elem : _uset) {
        os << elem << "  ";
    }
    os << "]";
    return os;
}
/////// PRINT MATRIX ///////////////////////////////////////////////
template <typename T>
ostream& operator<<(ostream& os, const vector<vector<T>>& matrix) {
    os << "[ MATRIX ]\n";
    if (matrix.size() == 0) {
        os << "(empty)\n\n";
        return os;
    }
    int n = matrix[0].size();
    os << "X| ";
    for (int i = 0; i < n; i++) os << i << "\t";
    os << endl;
    os << "==================================\n";
    int row = 0;
    for (auto vec : matrix) {
        os << row++ << "| ";
        for (auto elem : vec) {
            // if (elem == INT_MAX)
            //     cout<<"+inf\t";
            // else if (elem == INT_MIN)
            //     cout<<"-inf\t";
            // else
            os << elem << "\t";
        }
        os << endl;
    }
    os << "-----------------------------------\n";
    return os;
}

///////////// PRINT UNORDERED_MAP ///////////////////////////////
template <typename T1, typename T2>
ostream& operator<<(ostream& os, unordered_map<T1, T2>& _umap) {
    os << "[";
    for (auto elem : _umap) {
        os << "[" << elem.first << ": " << elem.second << "] ";
    }
    os << "]";
    return os;
}

///////////// PRINT MAP ///////////////////////////////
template <typename T1, typename T2>
ostream& operator<<(ostream& os, map<T1, T2>& _umap) {
    os << "[";
    for (auto elem : _umap) {
        os << "[" << elem.first << ": " << elem.second << "] ";
    }
    os << "]";
    return os;
}

///////////// PRINT QUEUE //////////////////////////
template <typename T>
ostream& operator<<(ostream& os, queue<T> q) {
    os << "[ ";
    while (!q.empty()) {
        os << q.front() << " ";
        q.pop();
    }
    os << "]";
    return os;
}

/////////////////  PRINT LIST /////////////////////////
template <typename T>
ostream& operator<<(ostream& os, const list<T>& _list) {
    os << "[ ";
    for (auto elem : _list) {
        os << elem << " -> ";
    }
    os << " X ]";
    return os;
}

/////////////////////////////////////////////////////////////////////////
#endif