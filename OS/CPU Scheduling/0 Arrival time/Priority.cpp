/*

Priority scheduling with arrival time of 0 and it included both pre-emptive and non-pre-emptive

*/

/*

In Priority scheduling, preemptive scheduling allows a higher priority process to interrupt a currently running process, while non-preemptive scheduling does not interrupt the running process, even if a higher priority process arrives. In the preemptive approach, the currently running process is either moved to the ready queue or blocked, and the higher priority process gets the CPU. In the non-preemptive method, the current process runs to completion before any other process can access the CPU. 

Definitions:
Preemptive Priority Scheduling:
If a process with a higher priority arrives while another process is running, the currently running process is interrupted, and the new, higher priority process begins execution. This ensures that critical tasks with higher priority are addressed quickly.

Non-Preemptive Priority Scheduling:
Once a process starts executing, it runs to completion without interruption, even if a higher priority process enters the ready queue. The higher priority process will have to wait until the currently running process finishes its execution. 

Examples:
Preemptive Priority Scheduling:

Imagine three processes, P1, P2, and P3, with priorities 2, 1, and 3 respectively, where lower numbers mean higher priority. 
At time 0, P1 arrives and starts running (priority 2).
At time 1, P2 arrives with a higher priority (priority 1) than P1. P1 is preempted and P2 starts executing.
At time 3, P2 finishes. If P3 (priority 3) had arrived earlier, it would have been running at this point.
At time 3, P1 resumes execution until it completes.

Non-Preemptive Priority Scheduling:
Using the same processes (P1, P2, P3) with priorities 2, 1, and 3: 
At time 0, P1 arrives and starts running (priority 2).
At time 1, P2 arrives with a higher priority (priority 1). P1 continues to run because the scheduling is non-preemptive.
P1 runs to completion.
At time 3, P2 starts running (priority 1).
At time 5, P2 finishes.
At time 5, P3 (priority 3) starts running.


*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int id;
    int burst_time;
    int priority;
    int arrival_time;
    int remaining_burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

bool compareProcesses(const Process& a, const Process& b) {
    if (a.priority != b.priority) {
        return a.priority < b.priority; // Lower priority number means higher priority
    }
    return a.id < b.id;
}

bool compareProcessesArrivalTime(const Process& a, const Process& b) {
    if (a.arrival_time != b.arrival_time) {
        return a.arrival_time < b.arrival_time;
    }
    if (a.priority != b.priority) {
        return a.priority < b.priority;
    }
    return a.id < b.id;
}

void calculate_times(vector<Process>& processes) {
    for (int i = 0; i < processes.size(); ++i) {
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }
}

void print_results(const vector<Process>& processes) {
    cout << "Process ID\tBurst Time\tPriority\tArrival Time\tCompletion Time\tTurnaround Time\tWaiting Time" << endl;
    for (const auto& p : processes) {
        cout << p.id << "\t\t" << p.burst_time << "\t\t" << p.priority << "\t\t" << p.arrival_time << "\t\t"
             << p.completion_time << "\t\t" << p.turnaround_time << "\t\t" << p.waiting_time << endl;
    }

    double total_turnaround_time = 0;
    double total_waiting_time = 0;
    for (const auto& p : processes) {
        total_turnaround_time += p.turnaround_time;
        total_waiting_time += p.waiting_time;
    }

    cout << "\nAverage Turnaround Time: " << total_turnaround_time / processes.size() << endl;
    cout << "Average Waiting Time: " << total_waiting_time / processes.size() << endl;
}

void priority_non_preemptive(vector<Process> processes) {
    sort(processes.begin(), processes.end(), compareProcesses);

    int current_time = 0;
    for (int i = 0; i < processes.size(); ++i) {
        current_time += processes[i].burst_time;
        processes[i].completion_time = current_time;
    }

    calculate_times(processes);
    cout << "\nNon-Preemptive Priority Scheduling (Arrival time 0):" << endl;
    print_results(processes);
}

void priority_preemptive(vector<Process> processes) {
    int n = processes.size();
    int current_time = 0;
    int completed_processes = 0;

    vector<Process> ready_queue;
    vector<bool> process_arrived(n, false);
    vector<Process> original_processes = processes; // To store original burst times

    for(int i = 0; i < n; ++i) {
        processes[i].remaining_burst_time = processes[i].burst_time;
    }


    while (completed_processes < n) {
        // Add arrived processes to the ready queue
        for (int i = 0; i < n; ++i) {
            if (!process_arrived[i] && original_processes[i].arrival_time <= current_time) {
                ready_queue.push_back(processes[i]);
                process_arrived[i] = true;
            }
        }

        if (ready_queue.empty()) {
            current_time++;
            continue;
        }

        // Sort ready queue by priority (lower number is higher priority)
        sort(ready_queue.begin(), ready_queue.end(), compareProcesses);

        // Execute the process with the highest priority
        Process& current_process = ready_queue[0];

        current_process.remaining_burst_time--;
        current_time++;

        // Update the remaining burst time in the main processes vector
        for(int i = 0; i < n; ++i) {
            if (processes[i].id == current_process.id) {
                processes[i].remaining_burst_time = current_process.remaining_burst_time;
                break;
            }
        }

        if (current_process.remaining_burst_time == 0) {
            current_process.completion_time = current_time;
            completed_processes++;

            // Update the completion time in the main processes vector
            for(int i = 0; i < n; ++i) {
                if (processes[i].id == current_process.id) {
                    processes[i].completion_time = current_process.completion_time;
                    break;
                }
            }

            // Remove from ready queue
            ready_queue.erase(ready_queue.begin());
        }
    }

    calculate_times(processes);
    cout << "\nPreemptive Priority Scheduling (Arrival time 0):" << endl;
    print_results(processes);
}


int main() {
    vector<Process> processes = {
        {1, 10, 2, 0},
        {2, 5, 0, 0},
        {3, 8, 1, 0},
        {4, 3, 3, 0}
    };

    priority_non_preemptive(processes);
    priority_preemptive(processes);

    return 0;
}
