#include "fcfs.h"

void compute_fcfs(vector<Process> &p) {
    stable_sort(p.begin(), p.end(), [](const Process &a, const Process &b){
        if (a.at != b.at) return a.at < b.at;
        return a.id < b.id;
    });
    int cur = 0;
    for (auto &pr : p) {
        int start = max(cur, pr.at);
        pr.st = start;
        pr.ct = pr.st + pr.bt;
        pr.tat = pr.ct - pr.at;
        pr.wt = pr.st - pr.at;
        pr.rt = pr.st - pr.at;
        cur = pr.ct;
    }
}

void print_table(const vector<Process> &p) {
    cout << "FCFS Scheduling\n\n";
    int wID = 8, wAT = 8, wBT = 8, wRT = 8, wTAT = 8, wWT = 8, wCT = 8;
    int totalw = wID + wAT + wBT + wRT + wTAT + wWT + wCT;
    cout << left << setw(wID) << "ID" << setw(wAT) << "AT" << setw(wBT) << "BT" << setw(wRT) << "RT" << setw(wTAT) << "TAT" << setw(wWT) << "WT" << setw(wCT) << "CT" << "\n";
    cout << string(totalw, '-') << "\n";
    double sum_tat=0, sum_wt=0, sum_rt=0, sum_ct=0, sum_at=0, sum_bt=0;
    for (auto &pr : p) {
        cout << left << setw(wID) << pr.id << setw(wAT) << pr.at << setw(wBT) << pr.bt << setw(wRT) << pr.rt << setw(wTAT) << pr.tat << setw(wWT) << pr.wt << setw(wCT) << pr.ct << "\n";
        sum_tat += pr.tat;
        sum_wt += pr.wt;
        sum_rt += pr.rt;
        sum_ct += pr.ct;
        sum_at += pr.at;
        sum_bt += pr.bt;
    }
    cout << fixed << setprecision(2);
    cout << string(totalw, '-') << "\n";
    cout << left << setw(wID) << "AVG" << setw(wAT) << (sum_at / p.size()) << setw(wBT) << (sum_bt / p.size()) << setw(wRT) << (sum_rt / p.size()) << setw(wTAT) << (sum_tat / p.size()) << setw(wWT) << (sum_wt / p.size()) << setw(wCT) << (sum_ct / p.size()) << "\n";
}

void print_gantt(const vector<Process> &p) {
    const int max_width = 80;
    int n = (int)p.size();
    int seg_w = max(3, max_width / max(1, n));
    int width = seg_w * n;
    int extra = 20;
    string top(width+extra, ' ');
    string names(width+extra, ' ');
    string times(width+extra, ' ');
    for (int i=0;i<n;++i) {
        int ps = i * seg_w;
        int pe = (i+1) * seg_w;
        if (ps < 0) ps = 0;
        if (pe > width) pe = width;
        top[ps] = '|';
        top[pe] = '|';
        for (int k = ps+1; k < pe; ++k) top[k] = '-';
        string id = p[i].id;
        int mid = (ps + pe) / 2;
        int start_name = mid - (int)id.size()/2;
        if (start_name < ps+1) start_name = ps+1;
        for (size_t j=0;j<id.size() && start_name + (int)j < pe; ++j) names[start_name + j] = id[j];
        string s = to_string(p[i].st);
        for (size_t j=0;j<s.size() && ps + (int)j < (int)times.size(); ++j) times[ps + j] = s[j];
    }
    string s_end = to_string(p.back().ct);
    int pe_last = width;
    for (size_t j=0;j<s_end.size() && pe_last + (int)j < (int)times.size(); ++j) times[pe_last + j] = s_end[j];
    cout << "\nGantt:\n";
    cout << top << "\n";
    cout << times << "\n";
    cout << names << "\n";
}

void fcfs(vector<Process> &procs) {
	compute_fcfs(procs);
	print_table(procs);
	print_gantt(procs);
}