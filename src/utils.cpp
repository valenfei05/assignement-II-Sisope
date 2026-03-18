#include "utils.h"
#include <fstream>
#include <sstream>

static string trim(const string& s) {
    const string whitespace = " \t\r\n";
    size_t start = s.find_first_not_of(whitespace);
    if (start == string::npos) {
        return "";
    }
    size_t end = s.find_last_not_of(whitespace);
    return s.substr(start, end - start + 1);
}

vector<Process> readFile(string filename) {
    vector<Process> processes;
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cout << "Error al abrir el archivo\n";
        return processes;
    }

    while (getline(file, line)) {
        string trimmedLine = trim(line);
        if (trimmedLine.empty() || trimmedLine[0] == '#') {
            continue;
        }

        vector<string> fields;
        string token;
        stringstream ss(trimmedLine);
        while (getline(ss, token, ';')) {
            fields.push_back(trim(token));
        }

        if (fields.size() < 5) {
            continue;
        }

        Process p;
        p.id = fields[0];
        p.bt = stoi(fields[1]);
        p.at = stoi(fields[2]);
        p.priority = stoi(fields[4]);

        processes.push_back(p);
    }

    file.close();
    return processes;
}