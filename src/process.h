#ifndef PROCESS_H
#define PROCESS_H

#include <bits/stdc++.h>
using namespace std;

struct Process {
    string id;
    int bt;
    int at;
    int priority;

    int remaining;
    bool started = false;

    int st;
    int ct;
    int tat;
    int wt;
    int rt;
};

#endif