#include "psjf.h"
#include <algorithm>
#include <iomanip>
#include <queue>

struct Block {
    string id;
    int start;
    int end;
};

static bool compareArrival(Process a, Process b) {
    if (a.at != b.at) return a.at < b.at;
    return a.id < b.id;
}

static void initializeProcesses(vector<Process>& processes) {
    for (auto& p : processes) {
        p.remaining = p.bt;
        p.started = false;
        p.ct = 0;
        p.tat = 0;
        p.wt = 0;
        p.rt = 0;
    }
}

struct CompareRemaining {
    bool operator()(const Process* a, const Process* b) const {
        if (a->remaining != b->remaining) return a->remaining > b->remaining;
        if (a->at != b->at) return a->at > b->at;
        return a->id > b->id;
    }
};

void runPsjf(vector<Process>& processes) {
    int n = processes.size();
    if (n == 0) return;

    sort(processes.begin(), processes.end(), compareArrival);
    initializeProcesses(processes);

    priority_queue<Process*, vector<Process*>, CompareRemaining> pq;
    vector<Block> gantt;

    int completed = 0;
    int time = 0;
    int nextArrival = 0;

    while (completed < n) {
        while (nextArrival < n && processes[nextArrival].at <= time) {
            pq.push(&processes[nextArrival]);
            nextArrival++;
        }

        if (pq.empty()) {
            time = processes[nextArrival].at;
            continue;
        }

        Process* current = pq.top();
        pq.pop();

        if (!current->started) {
            current->rt = time;
            current->started = true;
        }

        if (gantt.empty() || gantt.back().id != current->id) {
            gantt.push_back({current->id, time, time + 1});
        } else {
            gantt.back().end++;
        }

        current->remaining--;
        time++;

        while (nextArrival < n && processes[nextArrival].at <= time) {
            pq.push(&processes[nextArrival]);
            nextArrival++;
        }

        if (current->remaining == 0) {
            current->ct = time;
            current->tat = current->ct - current->at;
            current->wt = current->tat - current->bt;
            completed++;
        } else {
            pq.push(current);
        }
    }

    cout << "\nDiagrama:\n";
    for (auto& b : gantt) {
        cout << "| " << b.id << " ";
    }
    cout << "|\n";

    cout << gantt[0].start;
    for (auto& b : gantt) {
        cout << setw(5) << b.end;
    }
    cout << "\n";

    cout << "\nTabla PSJF:\n";
    cout << "---------------------------------------------\n";
    cout << "ID\tAT\tBT\tCT\tTAT\tWT\tRT\n";

    double avgCT = 0, avgWT = 0, avgTAT = 0, avgRT = 0;

    for (auto& p : processes) {
        cout << p.id << "\t"
             << p.at << "\t"
             << p.bt << "\t"
             << p.ct << "\t"
             << p.tat << "\t"
             << p.wt << "\t"
             << p.rt << "\n";

        avgCT += p.ct;
        avgWT += p.wt;
        avgTAT += p.tat;
        avgRT += p.rt;
    }

    avgCT /= n;
    avgWT /= n;
    avgTAT /= n;
    avgRT /= n;

    cout << "---------------------------------------------\n";
    cout << "AVG\t-\t-\t"
         << fixed << setprecision(2)
         << avgCT << "\t"
         << avgTAT << "\t"
         << avgWT << "\t"
         << avgRT << "\n";
}
