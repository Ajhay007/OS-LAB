// Suggested code may be subject to a license. Learn more: ~LicenseLog:2064155668.
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

bool compareArrival(const Process& a, const Process& b) {
    return a.arrival_time < b.arrival_time;
}

int main() {
    
    int n;
    std::cout << "Enter the number of processes: ";
    std::cin >> n;

    std::vector<Process> processes(n);

    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        std::cout <<endl<< "Enter arrival time for Process " << i + 1 << ": ";
        std::cin >> processes[i].arrival_time;
        std::cout <<"Enter burst time for Process " << i + 1 << ": ";
        std::cin >> processes[i].burst_time;
    }

    std::sort(processes.begin(), processes.end(), compareArrival);

    int current_time = 0;
    float total_turnaround_time = 0;
    float total_waiting_time = 0;

    for (int i = 0; i < n; ++i) {
        if (processes[i].arrival_time > current_time) {
            current_time = processes[i].arrival_time;
        }
        processes[i].completion_time = current_time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;

        current_time = processes[i].completion_time;

        total_turnaround_time += processes[i].turnaround_time;
        total_waiting_time += processes[i].waiting_time;
    }

    std::cout << "\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; ++i) {
        std::cout << processes[i].id << "\t" << processes[i].arrival_time << "\t\t" << processes[i].burst_time << "\t\t"
                  << processes[i].completion_time << "\t\t" << processes[i].turnaround_time << "\t\t"
                  << processes[i].waiting_time << std::endl;
    }

    float avg_turnaround_time = total_turnaround_time / n;
    float avg_waiting_time = total_waiting_time / n;

    std::cout << "\nAverage Turnaround Time: " << avg_turnaround_time << std::endl;
    std::cout << "Average Waiting Time: " << avg_waiting_time << std::endl;

    return 0;
}
