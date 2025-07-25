// Suggested code may be subject to a license. Learn more: ~LicenseLog:2439238379.
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

bool compareProcesses(const Process& a, const Process& b) {
    if (a.burst_time != b.burst_time) {
        return a.burst_time < b.burst_time;
    }
    return a.arrival_time < b.arrival_time;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cout << "Enter arrival time for process " << i + 1 << ": ";
        cin >> processes[i].arrival_time;
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> processes[i].burst_time;
    }

    sort(processes.begin(), processes.end(), compareProcesses);

    int current_time = 0;
    float total_turnaround_time = 0;
    float total_waiting_time = 0;

    for (int i = 0; i < n; ++i) {
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }
        processes[i].completion_time = current_time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;

        total_turnaround_time += processes[i].turnaround_time;
        total_waiting_time += processes[i].waiting_time;

        current_time = processes[i].completion_time;
    }

    cout << "\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; ++i) {
        cout << processes[i].id << "\t" << processes[i].arrival_time << "\t\t" << processes[i].burst_time << "\t\t"
             << processes[i].completion_time << "\t\t" << processes[i].turnaround_time << "\t\t"
             << processes[i].waiting_time << endl;
    }

    cout << "\nAverage Turnaround Time: " << total_turnaround_time / n << endl;
    cout << "Average Waiting Time: " << total_waiting_time / n << endl;

    return 0;
}
