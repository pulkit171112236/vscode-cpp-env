#include <bits/stdc++.h>

// custom headers
#include "HEADERS/PRINTER.h"
#include "HEADERS/READER.h"
#include "HEADERS/mylib.h"

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
        // if priorities are equal then but later at top if arrived before
        if (a.prior == b.prior) return a.arrival > b.arrival;
        // if pririties are differ then but later at top if higher priority
        else
            return a.prior < b.prior;
    }
};

struct CompArrivalLess {
    bool operator()(const Process& a, const Process& b) const {
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
    vector<int> clock_instance;
    priority_queue<Process, vector<Process>, CompPriorLess> pq;  // job queue
    int clock = 0;

    // create process-list
    for (int i = 0; i < n; i++) proc_list[i] = Process(i, at[i], bt[i], p[i]);
    // sort jobs based on arrival time
    sort(proc_list.begin(), proc_list.end(), CompArrivalLess());
    cout << proc_list << "\n";

    // loop on all the processes
    for (int i = 0; i < n; i++) {
        Process curr_proc = proc_list[i];
        int clock_next = curr_proc.arrival;  // time instance when next job arrives
        // execute the jobs from job-queue untill the arrival of next job
        while (!pq.empty() && clock < clock_next) {
            Process job = pq.top();
            pq.pop();
            // clock is lagging compared to jobs which are remaining
            if (clock < job.arrival) clock = job.arrival;
            // calculated available time-slot at cpu
            int time_slot = clock_next - clock;
            if (job.burst <= time_slot) {
                // whole job to be executed
                if (!job_chart.empty() && job_chart.back().id == job.id) {
                    job_chart.back().burst += job.burst;
                } else {
                    job_chart.push_back(job);
                    clock_instance.push_back(clock);
                }
                // advance the clock
                clock = clock + job.burst;
            } else {
                // job is larger then alloted time_slot
                // put the accomodable part of job in running state and put the remaing part in job queue
                if (!job_chart.empty() && job_chart.back().id == job.id) {
                    job_chart.back().burst += time_slot;
                } else {
                    job_chart.push_back(Process(job.id, job.arrival, time_slot, job.prior));
                    clock_instance.push_back(clock);
                }
                pq.push(Process(job.id, job.arrival, job.burst - time_slot, job.prior));
                // advance the clock
                clock = clock_next;
            }
        }
        pq.push(curr_proc);
        print(pq);
    }
    while (!pq.empty()) {
        Process job = pq.top();
        pq.pop();
        if (clock < job.arrival) clock = job.arrival;
        if (!job_chart.empty() && job_chart.back().id == job.id) {
            job_chart.back().burst += job.burst;
        } else {
            job_chart.push_back(job);
            clock_instance.push_back(clock);
        }
        clock = clock + job.burst;
    }
    for (int i = 0; i < job_chart.size(); i++) {
        cout << "t:" << clock_instance[i] << "  " << job_chart[i];
    }
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
    ps(n, at, bt, p);
    return 0;
}
