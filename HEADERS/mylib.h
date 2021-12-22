// mylib.h HEADER FILE
// INCLUDES BASIC USEFUL FUNCTIONS
#ifndef MYLIB_H
#define MYLIB_H

#include <bits/stdc++.h>

#ifndef INS_DASH
#define INS_DASH cout << "--------------------------------------\n";
#endif

using namespace std;

///////////////////////  GRAPH CLASS (FINDING SHORTEST DISTANCE)
/////////////////////////////////////
class Graph {
    vector<vector<int>> mat;
    vector<vector<int>> ls;
    int _size = 0;
    struct Cmp {
        bool operator()(const pair<int, int>& p1,
                        const pair<int, int>& p2) const {
            if (p1.second < p2.second)
                return false;
            else if (p1.second == p2.second && p1.first < p2.first)
                return false;
            else
                return true;
        }
    };

   public:
    Graph(int n) {
        _size = n;
        ls.resize(n);
        mat.resize(n, vector<int>(n));
    }
    void clear() {
        mat.clear();
        ls.clear();
        _size = 0;
    }
    void insertEdge(int i, int j, int w = 1) {
        ls[i].push_back(j);
        mat[i][j] = w;
    }
    int getShortestPath(int start, int end) {
        // we apply dikshatra
        vector<int> visited(_size), dis(_size, INT_MAX);
        priority_queue<pair<int, int>, vector<pair<int, int>>, Cmp> pq;
        dis[start] = 0;
        pq.push({start, 0});
        while (!pq.empty() && pq.top().first != end) {
            pair<int, int> curr = pq.top();
            pq.pop();
            if (visited[curr.first]) continue;
            int v1 = curr.first;
            for (auto v2 : ls[v1]) {
                if (visited[v2]) continue;
                if (dis[v1] + mat[v1][v2] < dis[v2]) {
                    dis[v2] = dis[v1] + mat[v1][v2];
                    pq.push({v2, dis[v2]});
                }
            }
        }
        // cout<<"disVec:"<<dis<<endl;
        return dis[end];
    }
};

///////////////////////  GET RANDOM VECTOR   ///////////////////////////
vector<int> getRandomVector(int n, int _lim = 0) {
    vector<int> vec(n);
    if (_lim == 0) _lim = 10 * n;
    for (auto& elem : vec) {
        elem = (rand() % (2 * _lim)) - _lim;
    }
    return vec;
}

////////////////  GETTING CURRENT DAY OF A DATE (CALENDER)
/////////////////////////////
int myCalender(int d, int m, int y, bool print_on = false) {
    int cnt_year = y + y / 4 - y / 100 + y / 400;
    int magic_no[] = {0, 0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};
    function<bool(int)> isLeap = [](int x) {
        return x % 400 == 0 || (x % 100 != 0 && x % 4 == 0);
    };
    // we have counted extra one for all dates in leap year but no count upto 29
    // feb
    if (isLeap(y) && m <= 2) cnt_year--;
    int odd_days = (cnt_year + magic_no[m] + d - 1) % 7;
    if (print_on) {
        switch (odd_days) {
            case 0:
                cout << "sunday";
                break;
            case 1:
                cout << "monday";
                break;
            case 2:
                cout << "tuesday";
                break;
            case 3:
                cout << "wednesday";
                break;
            case 4:
                cout << "thursday";
                break;
            case 5:
                cout << "friday";
                break;
            case 6:
                cout << "saturday";
                break;
        }
    }
    return odd_days;
}

///////////////////////// FENWICK TREE
////////////////////////////////////////////////////////////
class Fenwick {
    vector<int> farr;
    int lsb(int idx) { return idx & -idx; }

   public:
    Fenwick(int n) { farr.resize(n + 1, 0); }
    Fenwick(vector<int>& vec) {
        int n = vec.size() - 1;
        farr.resize(n + 1);
        farr[0] = vec[0];
        for (int i = 1; i <= n; i++) {
            int par = i + lsb(i);
            farr[i] += vec[i];
            if (par <= n) farr[par] += farr[i];
        }
    }
    int prefixSum(int idx) {
        if (idx == 0) return farr[0];
        int sum = farr[0];
        while (idx) {
            sum += farr[idx];
            idx -= lsb(idx);
        }
        return sum;
    }
    void add(int idx, int val) {
        if (idx == 0) {
            farr[0] += val;
            return;
        }
        while (idx < farr.size()) {
            farr[idx] += val;
            idx += lsb(idx);
        }
    }
    int rangeSum(int idx1, int idx2) {
        if (idx1 == 0)
            return prefixSum(idx2);
        else
            return prefixSum(idx2) - prefixSum(idx1 - 1);
    }
    // void print() {
    //     cout<<"farr:"<<farr<<endl;
    // }
};

/////////////////////  SEGMENT TREE (MIN MAX RANGE)
//////////////////////////////////

class SegmentTree {
    vector<int> minSeg;
    vector<int> maxSeg;
    int n_el;

    // make sure that some part of s_range overlaps with given_range(left,
    // right)
    pair<int, int> minMaxHelper(int left, int right, int pos_seg, int s_left,
                                int s_right) {
        // debug
        // printf("calling minMax for segment %d to %d pos_seg is %d \n",s_left,
        // s_right, pos_seg); current segment is completely inside required
        // interval
        if (left <= s_left && s_right <= right) {
            return make_pair(minSeg[pos_seg], maxSeg[pos_seg]);
        } else {
            int s_mid = (s_left + s_right) / 2;
            // if left segment is completely out of reach
            if (s_mid < left)
                return minMaxHelper(left, right, 2 * pos_seg + 2, s_mid + 1,
                                    s_right);
            // if right segment is completely out of reach
            else if (right < s_mid + 1)
                return minMaxHelper(left, right, 2 * pos_seg + 1, s_left,
                                    s_mid);
            // else both segments have some part overlapping
            pair<int, int> range_left =
                minMaxHelper(left, right, 2 * pos_seg + 1, s_left, s_mid);
            pair<int, int> range_right =
                minMaxHelper(left, right, 2 * pos_seg + 2, s_mid + 1, s_right);
            int _min = min(range_left.first, range_right.first);
            int _max = max(range_left.second, range_right.second);
            return make_pair(_min, _max);
        }
    }
    int lessCountHelper(int left, int right, int el, int pos_seg, int s_left,
                        int s_right) {
        // base condition either segment is out of given interval or all values
        // in segment are higer than el
        if (right < s_left || s_right < left || minSeg[pos_seg] >= el) return 0;

        // totally favourable segment
        if (left <= s_left && s_right <= right && maxSeg[pos_seg] < el) {
            return s_right - s_left + 1;
        }
        // else
        int mid = (s_left + s_right) / 2;
        int left_count =
            lessCountHelper(left, right, el, 2 * pos_seg + 1, s_left, mid);
        int right_count =
            lessCountHelper(left, right, el, 2 * pos_seg + 2, mid + 1, s_right);
        return left_count + right_count;
    }
    void constructSegTree(vector<int>& nums, int pos_seg, int s_left,
                          int s_right) {
        // cout<<"constructing tree for "<<s_left<<"  to  "<<s_right<<"\n";
        // base condition
        if (s_left == s_right) {
            minSeg[pos_seg] = maxSeg[pos_seg] = nums[s_left];
            return;
        }
        // else construct left and right first then append result
        int mid = (s_left + s_right) / 2;
        constructSegTree(nums, 2 * pos_seg + 1, s_left, mid);
        constructSegTree(nums, 2 * pos_seg + 2, mid + 1, s_right);
        minSeg[pos_seg] = min(minSeg[2 * pos_seg + 1], minSeg[2 * pos_seg + 2]);
        maxSeg[pos_seg] = max(maxSeg[2 * pos_seg + 1], maxSeg[2 * pos_seg + 2]);
    }

   public:
    SegmentTree(vector<int>& nums) : n_el(nums.size()) {
        // n_el = nums.size();
        minSeg.resize(4 * n_el, -1);
        maxSeg.resize(4 * n_el, -1);
        constructSegTree(nums, 0, 0, n_el - 1);
    }
    pair<int, int> getMinMax(int left, int right) {
        if (left > right || left < 0 || right > n_el - 1) {
            cout << "_________________not valid range_____________________\n";
            throw -1;
        }
        return minMaxHelper(left, right, 0, 0, n_el - 1);
    }
    int getMin(int left, int right) {
        return minMaxHelper(left, right, 0, 0, n_el - 1).first;
    }
    int getLessCount(int left, int right, int el) {
        if (left > right || left < 0 || right > n_el) return 0;
        return lessCountHelper(left, right, el, 0, 0, n_el - 1);
    }
    // void test() {
    //     cout<<"minSeg:"<<minSeg<<endl;
    //     cout<<"maxSeg:"<<maxSeg<<endl;
    //     INS_DASH;
    //     for (int i = 0; i < n_el; i++) {
    //         for (int j = i; j < n_el; j++) {
    //             printf("minMax for range %d to %d\n" ,i, j);
    //             cout<<getMinMax(i, j)<<endl;
    //             INS_DASH;
    //         }
    //         INS_DASH
    //     }
    //     //cheking lessCount
    // }
    // void test2(vector<int>& arr) {
    //     INS_DASH
    //     for (int i = 0; i < arr.size(); i++) {
    //         printf("count less than %d in range %d to %d\n is %d", arr[i],
    //         i+1, n_el-1, getLessCount(i+1, n_el-1, arr[i])); INS_DASH
    //     }
    // }
};

/////////////////////////  PRIME ////////////////////////////
#define MAX 100007
class Prime {
    bitset<MAX> _primes;

   public:
    list<int> _list;
    Prime() {
        // intitially all primes
        _primes.flip();
        // removing 0,1
        _primes[0] = _primes[1] = 0;
        // resetting multiples upto sqrt(MAX)
        for (int i = 2; i <= MAX / i; i++) {
            // start should be prime
            if (_primes[i]) {
                // resetting from twice
                int curr = i << 1;
                while (curr < MAX) {
                    _primes[curr] = 0;
                    curr += i;
                }
            }
        }
        // feed to _list
        for (int i = 0; i < MAX; i++) {
            if (_primes[i]) _list.push_back(i);
        }
        // test();
    }
    bool isPrime(int elem) { return _primes[elem]; }
    list<int>& getList() { return _list; }
    vector<int> getPrimeFactors(int num) {
        vector<int> p_fac;
        for (auto el : _list) {
            if (num == 1)
                break;
            else if (isPrime(num)) {
                p_fac.push_back(num);
                break;
            } else if (num % el == 0) {
                p_fac.push_back(el);
                while (num % el == 0) {
                    num /= el;
                }
            }
        }
        return p_fac;
    }
    vector<pair<int, int>> factorization(int num) {
        vector<pair<int, int>> res;
        auto it = _list.begin();
        int curr, buff;
        buff = 0;
        while (num > 1) {
            curr = *it;
            if (curr > 100) break;

            if (num % curr == 0) {
                num /= curr;
                buff++;
            } else {
                if (buff) res.push_back(make_pair(curr, buff));
                buff = 0;
                advance(it, 1);
            }
        }
        if (buff) res.push_back(make_pair(curr, buff));
        return res;
    }
    // void test() {
    //     cout<<"prime list\n";
    //     INS_DASH
    //     for (auto elem : _list) cout<<elem<<endl;
    //     INS_DASH
    // }
} prime;

//////////////////////////////////////////////////////////////////////////////////////
#endif