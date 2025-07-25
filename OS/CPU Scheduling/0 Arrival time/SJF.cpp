/*

Shortest Job First with arrival time of 0

*/


#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int id;
    int burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};

bool compareProcesses(const Process& a, const Process& b) {
    return a.burst_time < b.burst_time;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cout << "Enter burst time for process " << processes[i].id << ": ";
        cin >> processes[i].burst_time;
    }

    sort(processes.begin(), processes.end(), compareProcesses);

    int current_time = 0;
    float total_turnaround_time = 0;
    float total_waiting_time = 0;
    float total_response_time = 0;

    for (int i = 0; i < n; ++i) {
        processes[i].start_time = current_time;
        processes[i].completion_time = current_time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time;
        processes[i].waiting_time = processes[i].start_time;
        processes[i].response_time = processes[i].start_time;

        current_time = processes[i].completion_time;

        total_turnaround_time += processes[i].turnaround_time;
        total_waiting_time += processes[i].waiting_time;
        total_response_time += processes[i].response_time;
    }

    cout << "\nProcess\tBurst Time\tStart Time\tCompletion Time\tTurnaround Time\tWaiting Time\tResponse Time\n";
    cout << "-------------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < n; ++i) {
        cout << processes[i].id << "\t" << processes[i].burst_time << "\t\t"
             << processes[i].start_time << "\t\t" << processes[i].completion_time << "\t\t"
             << processes[i].turnaround_time << "\t\t" << processes[i].waiting_time << "\t\t"
             << processes[i].response_time << endl;
    }

    cout << "\nAverage Turnaround Time: " << total_turnaround_time / n << endl;
    cout << "Average Waiting Time: " << total_waiting_time / n << endl;
    cout << "Average Response Time: " << total_response_time / n << endl;

    return 0;
}
