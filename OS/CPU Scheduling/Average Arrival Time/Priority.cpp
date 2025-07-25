#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

bool compareArrival(const Process& a, const Process& b) {
    return a.arrival_time < b.arrival_time;
}

bool comparePriority(const Process& a, const Process& b) {
    return a.priority < b.priority;
}

void calculateTimes(vector<Process>& processes) {
    for (size_t i = 0; i < processes.size(); ++i) {
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }
}

void printResults(const vector<Process>& processes) {
    cout << "Process\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (const auto& p : processes) {
        cout << p.id << "\t\t" << p.arrival_time << "\t\t" << p.burst_time << "\t\t" << p.priority << "\t\t"
             << p.completion_time << "\t\t" << p.turnaround_time << "\t\t" << p.waiting_time << endl;
    }

    double avg_turnaround_time = 0;
    double avg_waiting_time = 0;
    for (const auto& p : processes) {
        avg_turnaround_time += p.turnaround_time;
        avg_waiting_time += p.waiting_time;
    }
    avg_turnaround_time /= processes.size();
    avg_waiting_time /= processes.size();

    cout << "\nAverage Turnaround Time: " << avg_turnaround_time << endl;
    cout << "Average Waiting Time: " << avg_waiting_time << endl;
}

void priority_non_preemptive(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), compareArrival);

    int current_time = 0;
    vector<Process> completed_processes;
    vector<Process> ready_queue;
    vector<Process> original_processes = processes;

    size_t process_index = 0;

    while (!processes.empty() || !ready_queue.empty()) {
        while (process_index < original_processes.size() && original_processes[process_index].arrival_time <= current_time) {
            ready_queue.push_back(original_processes[process_index]);
            process_index++;
        }

        if (ready_queue.empty()) {
            current_time++;
            continue;
        }

        sort(ready_queue.begin(), ready_queue.end(), comparePriority);

        Process current_process = ready_queue.front();
        ready_queue.erase(ready_queue.begin());

        current_time += current_process.burst_time;
        current_process.completion_time = current_time;
        completed_processes.push_back(current_process);

        // Remove the completed process from the original list
        for (size_t i = 0; i < processes.size(); ++i) {
            if (processes[i].id == current_process.id) {
                processes.erase(processes.begin() + i);
                break;
            }
        }
    }

    processes = completed_processes;
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b){
        return a.id < b.id;
    });
    calculateTimes(processes);
}

void priority_preemptive(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), compareArrival);

    int current_time = 0;
    vector<Process> completed_processes;
    vector<Process> ready_queue;
    vector<Process> original_processes = processes;

    for (size_t i = 0; i < processes.size(); ++i) {
        processes[i].remaining_burst_time = processes[i].burst_time;
    }

    size_t process_index = 0;

    while (!processes.empty()) {
        while (process_index < original_processes.size() && original_processes[process_index].arrival_time <= current_time) {
             bool already_in_queue = false;
             for(const auto& p : ready_queue) {
                 if (p.id == original_processes[process_index].id) {
                     already_in_queue = true;
                     break;
                 }
             }
             if (!already_in_queue) {
                 ready_queue.push_back(original_processes[process_index]);
             }
             process_index++;
        }

        if (ready_queue.empty()) {
            current_time++;
            continue;
        }

        sort(ready_queue.begin(), ready_queue.end(), comparePriority);

        Process* current_process = nullptr;
        for (auto& p : processes) {
            if (p.id == ready_queue[0].id) {
                current_process = &p;
                break;
            }
        }


        current_process->remaining_burst_time--;
        current_time++;

        if (current_process->remaining_burst_time == 0) {
            current_process->completion_time = current_time;
            completed_processes.push_back(*current_process);

            // Remove from processes vector
            for (size_t i = 0; i < processes.size(); ++i) {
                if (processes[i].id == current_process->id) {
                    processes.erase(processes.begin() + i);
                    break;
                }
            }
             // Remove from ready queue
            for (size_t i = 0; i < ready_queue.size(); ++i) {
                if (ready_queue[i].id == current_process->id) {
                    ready_queue.erase(ready_queue.begin() + i);
                    break;
                }
            }
        }
    }

    processes = completed_processes;
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b){
        return a.id < b.id;
    });
    calculateTimes(processes);
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cout << "Enter arrival time for Process " << i + 1 << ": ";
        cin >> processes[i].arrival_time;
        cout << "Enter burst time for Process " << i + 1 << ": ";
        cin >> processes[i].burst_time;
        cout << "Enter priority for Process " << i + 1 << ": ";
        cin >> processes[i].priority;
    }

    int choice;
    cout << "\nChoose scheduling type:\n";
    cout << "1. Non-preemptive Priority\n";
    cout << "2. Preemptive Priority\n";
    cout << "Enter your choice: ";
    cin >> choice;

    vector<Process> processes_copy = processes; // Make a copy for the other algorithm

    if (choice == 1) {
        cout << "\n--- Non-preemptive Priority Scheduling ---\n";
        priority_non_preemptive(processes);
        printResults(processes);
    } else if (choice == 2) {
        cout << "\n--- Preemptive Priority Scheduling ---\n";
        priority_preemptive(processes);
        printResults(processes);
    } else {
        cout << "Invalid choice.\n";
    }

    return 0;
}
