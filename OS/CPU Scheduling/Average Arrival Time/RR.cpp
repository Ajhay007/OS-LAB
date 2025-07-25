#include <iostream>
#include <vector>
#include <queue>
#include <numeric>
#include <algorithm>

using namespace std;

struct Process {
    int id;
    int burst_time;
    int remaining_time;
    int arrival_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cout << "Enter arrival time for process " << processes[i].id << ": ";
        cin >> processes[i].arrival_time;
        cout << "Enter burst time for process " << processes[i].id << ": ";
        cin >> processes[i].burst_time;
        processes[i].remaining_time = processes[i].burst_time;
    }

    int time_quantum;
    cout << "Enter the time quantum: ";
    cin >> time_quantum;

    queue<int> ready_queue;
    vector<bool> in_queue(n, false);
    int current_time = 0;
    int completed_processes = 0;

    // Sort processes by arrival time initially
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrival_time < b.arrival_time;
    });

    int process_index = 0; // To keep track of processes arriving

    while (completed_processes < n) {
        // Add arrived processes to the ready queue
        while (process_index < n && processes[process_index].arrival_time <= current_time) {
            if (!in_queue[processes[process_index].id - 1]) {
                ready_queue.push(processes[process_index].id - 1);
                in_queue[processes[process_index].id - 1] = true;
            }
            process_index++;
        }

        if (ready_queue.empty()) {
            // If no process is ready, increment time to the next arrival
            current_time++;
            continue;
        }

        int current_process_index = ready_queue.front();
        ready_queue.pop();
        in_queue[current_process_index] = false;

        int execution_time = min(processes[current_process_index].remaining_time, time_quantum);
        processes[current_process_index].remaining_time -= execution_time;
        current_time += execution_time;

        // Add any processes that arrived during the execution
        while (process_index < n && processes[process_index].arrival_time <= current_time) {
             if (!in_queue[processes[process_index].id - 1]) {
                ready_queue.push(processes[process_index].id - 1);
                in_queue[processes[process_index].id - 1] = true;
            }
            process_index++;
        }

        if (processes[current_process_index].remaining_time == 0) {
            processes[current_process_index].completion_time = current_time;
            processes[current_process_index].turnaround_time = processes[current_process_index].completion_time - processes[current_process_index].arrival_time;
            processes[current_process_index].waiting_time = processes[current_process_index].turnaround_time - processes[current_process_index].burst_time;
            completed_processes++;
        } else {
            ready_queue.push(current_process_index);
             in_queue[current_process_index] = true;
        }
    }

    cout << "\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    double total_turnaround_time = 0;
    double total_waiting_time = 0;

    // Sort back by process ID for output clarity
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.id < b.id;
    });

    for (const auto& p : processes) {
        cout << p.id << "\t" << p.arrival_time << "\t\t" << p.burst_time << "\t\t"
             << p.completion_time << "\t\t" << p.turnaround_time << "\t\t" << p.waiting_time << endl;
        total_turnaround_time += p.turnaround_time;
        total_waiting_time += p.waiting_time;
    }

    cout << "\nAverage Turnaround Time: " << total_turnaround_time / n << endl;
    cout << "Average Waiting Time: " << total_waiting_time / n << endl;

    return 0;
}
