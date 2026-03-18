#include "roundrobin.h"

struct Block {
    string id;
    int start;
    int end;
};

void RoundRobin(vector<Process> p, int quantum) {
    int n = p.size();

    sort(p.begin(), p.end(), [](Process a, Process b) {
        return a.at < b.at;
    });

    queue<int> q;
    vector<bool> inQueue(n, false);
    vector<Block> gantt;

    for (int i = 0; i < n; i++) {
        p[i].remaining = p[i].bt;
        p[i].started = false;
    }

    int time = 0;

    for (int i = 0; i < n; i++) {
        if (p[i].at <= time) {
            q.push(i);
            inQueue[i] = true;
        }
    }

    if (q.empty()) {
        time = p[0].at;
        q.push(0);
        inQueue[0] = true;
    }

    while (!q.empty()) {
        int i = q.front();
        q.pop();

        int start = time;

        if (!p[i].started) {
            p[i].rt = time - p[i].at;
            p[i].started = true;
        }

        int exec = min(quantum, p[i].remaining);

        for (int t = 0; t < exec; t++) {
            time++;

            for (int j = 0; j < n; j++) {
                if (!inQueue[j] && p[j].at <= time) {
                    q.push(j);
                    inQueue[j] = true;
                }
            }
        }

        int end = time;
        gantt.push_back({p[i].id, start, end});

        p[i].remaining -= exec;

        if (p[i].remaining > 0) {
            q.push(i);
        } else {
            p[i].ct = time;
            p[i].tat = p[i].ct - p[i].at;
            p[i].wt = p[i].tat - p[i].bt;
        }
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

    cout << "\nTabla Round-Robin:\n";
    cout << "---------------------------------------------\n";
    cout << "ID\tAT\tBT\tCT\tTAT\tWT\tRT\n";

    double avgWT = 0, avgTAT = 0, avgRT = 0;

    for (auto &proc : p) {
        cout << proc.id << "\t"
             << proc.at << "\t"
             << proc.bt << "\t"
             << proc.ct << "\t"
             << proc.tat << "\t"
             << proc.wt << "\t"
             << proc.rt << "\n";

        avgWT += proc.wt;
        avgTAT += proc.tat;
        avgRT += proc.rt;
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