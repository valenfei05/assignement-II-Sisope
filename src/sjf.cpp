#include "sjf.h"
#include <algorithm>
#include <iomanip>

struct Block {
    string id;
    int start;
    int end;
};

bool compareArrival(Process a, Process b) {
    if (a.at < b.at) return true;
    if (a.at == b.at) return a.id < b.id;
    return false;
}

void initializeProcesses(vector<Process>& processes) {
    for (auto &p : processes) {
        p.remaining = p.bt;
        p.started = false;
        p.ct = 0;
        p.tat = 0;
        p.wt = 0;
        p.rt = 0;
    }
}

void runSjf(vector<Process>& processes) {
    int n = processes.size();
    int completed = 0, time = 0;

    vector<Block> gantt;

    initializeProcesses(processes);

    while (completed < n) {
        int selected = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].remaining > 0 && processes[i].at <= time) {
                if (selected == -1 ||
                    processes[i].bt < processes[selected].bt ||
                    (processes[i].bt == processes[selected].bt && processes[i].at < processes[selected].at) ||
                    (processes[i].bt == processes[selected].bt && processes[i].at == processes[selected].at && processes[i].id < processes[selected].id)) {
                    selected = i;
                }
            }
        }

        if (selected == -1) {
            time++;
        } else {
            int start = time;

            if (!processes[selected].started) {
                processes[selected].rt = time - processes[selected].at;
                processes[selected].started = true;
            }

            time += processes[selected].bt;

            processes[selected].remaining = 0;
            processes[selected].ct = time;

            gantt.push_back({processes[selected].id, start, time});

            completed++;
        }
    }

    for (auto &p : processes) {
        p.tat = p.ct - p.at;
        p.wt = p.tat - p.bt;
    }

    cout << "\nDiagrama:\n";
    for (auto &b : gantt) {
        cout << "| " << b.id << " ";
    }
    cout << "|\n";

    cout << gantt[0].start;
    for (auto &b : gantt) {
        cout << setw(5) << b.end;
    }
    cout << "\n";

    cout << "\nTabla SJF:\n";
    cout << "---------------------------------------------\n";
    cout << "ID\tAT\tBT\tCT\tTAT\tWT\tRT\n";

    double avgWT = 0, avgTAT = 0, avgRT = 0;

    sort(processes.begin(), processes.end(), compareArrival);

    for (auto &p : processes) {
        cout << p.id << "\t"
             << p.at << "\t"
             << p.bt << "\t"
             << p.ct << "\t"
             << p.tat << "\t"
             << p.wt << "\t"
             << p.rt << "\n";

        avgWT += p.wt;
        avgTAT += p.tat;
        avgRT += p.rt;
    }

    avgWT /= n;
    avgTAT /= n;
    avgRT /= n;

    cout << "---------------------------------------------\n";
    cout << "AVG\t-\t-\t-\t"
         << fixed << setprecision(2)
         << avgTAT << "\t"
         << avgWT << "\t"
         << avgRT << "\n";
}