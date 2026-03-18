#include "./utils.h"
#include "./roundrobin.h"
#include "./sjf.h"

int main(int argc, char* argv[]) {

    if (argc < 3) {
        cout << "Uso:\n";
        cout << "./scheduler -algoritmo archivo.txt [quantum]\n";
        cout << "Algoritmos: -rr -sjf\n";
        return 1;
    }

    string algoritmo = argv[1];
    string filename = argv[2];

    vector<Process> processes = readFile(filename);

    if (algoritmo == "-rr") {
        if (argc < 4) {
            cout << "Error: debes indicar el quantum para Round Robin\n";
            return 1;
        }

        int q = stoi(argv[3]);
        RoundRobin(processes, q);
    }
    else if (algoritmo == "-sjf") {
        runSjf(processes);
    }
    else {
        cout << "Algoritmo no valido\n";
    }

    return 0;
}