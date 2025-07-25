/*

FCFS CPU Scheduling with 0 as Arrival Time:

*/

#include <iostream>
#include <vector>
#include <numeric> // For std::accumulate

struct Process {
    int id;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};

void calculateFCFS(std::vector<Process>& processes) {
    // For FCFS with 0 arrival time, processes are executed in the order they are provided.
    // The first process's waiting time is 0.
    processes[0].waiting_time = 0;
    processes[0].turnaround_time = processes[0].burst_time;

    // Calculate waiting time and turnaround time for subsequent processes
    for (size_t i = 1; i < processes.size(); ++i) {
        processes[i].waiting_time = processes[i - 1].waiting_time + processes[i - 1].burst_time;
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
    }
}

void displayResults(const std::vector<Process>& processes) {
    std::cout << "Process ID\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (const auto& p : processes) {
        std::cout << p.id << "\t\t" << p.burst_time << "\t\t" << p.waiting_time << "\t\t" << p.turnaround_time << "\n";
    }

    // Calculate and display average waiting and turnaround time
    double total_waiting_time = 0;
    double total_turnaround_time = 0;

    for (const auto& p : processes) {
        total_waiting_time += p.waiting_time;
        total_turnaround_time += p.turnaround_time;
    }

    std::cout << "\nAverage Waiting Time: " << total_waiting_time / processes.size() << "\n";
    std::cout << "Average Turnaround Time: " << total_turnaround_time / processes.size() << "\n";
}

int main() {
    int num_processes;
    std::cout << "Enter the number of processes: ";
    std::cin >> num_processes;

    std::vector<Process> processes(num_processes);

    // Input burst times (arrival time is assumed to be 0 for all)
    for (int i = 0; i < num_processes; ++i) {
        processes[i].id = i + 1;
        std::cout << "Enter burst time for Process " << processes[i].id << ": ";
        std::cin >> processes[i].burst_time;
    }

    calculateFCFS(processes);
    displayResults(processes);

    return 0;
}