#include <bits/stdc++.h>

// custom headers
#include "HEADERS\PRINTER.h"
#include "HEADERS\READER.h"
#include "HEADERS\mylib.h"

using namespace std;

struct Process {
    int id;
    int arrival;
    int burst;  // remaining cpu time
    int prior;
    Process(int i, int a, int b, int p) : id(i), arrival(a), burst(b), prior(p) {}
    Process(){};
};

/////////// PRINT PROCESS /////////////////////////////////////////////////
ostream& operator<<(ostream& os, const Process& j) {
    os << "Process( pid:" << j.id << " arrival " << j.arrival << " burst " << j.burst << " prior " << j.prior << ")\n";
    return os;
}

struct CompPriorLess {
    bool operator()(const Process& a, const Process& b) {
        return a.prior < b.prior;
    }
};

struct CompArrivalLess {
    bool operator()(Process a, Process b) {
        return a.arrival < b.arrival;
    }
};

void print(priority_queue<Process, vector<Process>, CompPriorLess> pq) {
    while (!pq.empty()) {
        Process j = pq.top();
        pq.pop();
        cout << j;
    }
    cout << "--------------------------------\n";
}
void ps(int n, vector<int> at, vector<int> bt, vector<int> p) {
    vector<Process> proc_list(n);
    vector<Process> job_chart;
    priority_queue<Process, vector<Process>, CompPriorLess> pq;  // job queue

    for (int i = 0; i < n; i++) proc_list[i] = Process(i, at[i], bt[i], p[i]);
    sort(proc_list.begin(), proc_list.end(), CompArrivalLess());
    cout << proc_list << "\n";
    int clock = 0;
    // looping all process
    for (int i = 0; i < n; i++) {
        Process curr_proc = proc_list[i];
        int clock_next = curr_proc.arrival;
        // execute the jobs which arrived before the current process
        while (!pq.empty() && pq.top().start_time < clock_next) {
            Job job = pq.top();
            pq.pop();
            // clock is lagging compared to job arrival
            if (clock < job.start_time) clock = job.start_time;
            // calculated available time-slot at cpu
            int time_slot = clock_next - clock;
            if (job.burst <= time_slot) {
                // whole job to be executed
                job_chart.push_back(Job(job.p_id, clock, job.burst, job.prior));
                // advance the clock
                clock = clock + job.burst;
            } else {
                // job is larger then alloted time_slot
                // put the part of job in running state and put the remaing part in job queue
                job_chart.push_back(Job(job.p_id, clock, time_slot, job.prior));
                pq.push(Job(job.p_id, clock_next, job.burst - time_slot, job.prior));
                // advance the clock
                clock = clock_next;
            }
        }
        pq.push(Job(curr_proc.id, curr_proc.arrival, curr_proc.burst, curr_proc.prior));
        print(pq);
    }
    while (!pq.empty()) {
        Job job = pq.top();
        if (clock < job.start_time) clock = job.start_time;
        job_chart.push_back(Job(job.p_id, clock, job.burst, job.prior));
        clock = clock + job.burst;
        pq.pop();
    }
    cout << job_chart << endl;
}
int main() {
    // declaring custom buffers
    ifstream cin("input.txt");
    ofstream cout("output.txt");
    // optional performance optimizations
    ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    // redirecting stdio to custom buffers
    std::cin.rdbuf(cin.rdbuf());
    std::cout.rdbuf(cout.rdbuf());

    int n;
    cin >> n;
    vector<int> at(n), bt(n), p(n);
    for (int i = 0; i < n; i++) cin >> at[i];
    for (int i = 0; i < n; i++) cin >> bt[i];
    for (int i = 0; i < n; i++) cin >> p[i];
    cout << "------test-------- \n";
    ps(n, at, bt, p);
    return 0;
}
