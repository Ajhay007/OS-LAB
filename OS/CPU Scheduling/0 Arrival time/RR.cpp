/*
Round Robin Implementation with 0 Arrival Time

*/


#include <iostream>
#include <vector>
#include <numeric>
#include <queue>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

struct Process {
    int pid;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
    int completionTime;
};

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    cout << "Enter burst time for each process:" << endl;
    for (int i = 0; i < n; ++i) {
        processes[i].pid = i + 1;
        cout << "P" << processes[i].pid << ": ";
        cin >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].waitingTime = 0;
        processes[i].turnaroundTime = 0;
    }

    int timeQuantum;
    cout << "Enter the time quantum: ";
    cin >> timeQuantum;

    queue<Process*> readyQueue;
    for (int i = 0; i < n; ++i) {
        readyQueue.push(&processes[i]);
    }

    int currentTime = 0;

    cout << "\nProcess Execution Order:" << endl;
    while (!readyQueue.empty()) {
        Process* currentProcess = readyQueue.front();
        readyQueue.pop();

        int executeTime = min(currentProcess->remainingTime, timeQuantum);

        cout << "Executing P" << currentProcess->pid << " for " << executeTime << " units." << endl;

        pid_t child_pid = fork();

        if (child_pid == 0) { // Child process
            // Simulate process execution
            usleep(executeTime * 100000); // Simulate work
            exit(0); // Child finishes
        } else if (child_pid > 0) { // Parent process
            waitpid(child_pid, NULL, 0); // Wait for the child to finish

            currentTime += executeTime;
            currentProcess->remainingTime -= executeTime;

            if (currentProcess->remainingTime == 0) {
                currentProcess->completionTime = currentTime;
                currentProcess->turnaroundTime = currentProcess->completionTime - 0; // Arrival time is 0
                currentProcess->waitingTime = currentProcess->turnaroundTime - currentProcess->burstTime;
            } else {
                readyQueue.push(currentProcess);
            }
        } else {
            cerr << "Fork failed for process P" << currentProcess->pid << endl;
            return 1; // Indicate an error
        }
    }

    cout << "\nProcess Results:" << endl;
    cout << "PID\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time" << endl;
    for (const auto& p : processes) {
        cout << p.pid << "\t" << p.burstTime << "\t\t" << p.completionTime << "\t\t" << p.turnaroundTime << "\t\t" << p.waitingTime << endl;
    }

    double totalWaitingTime = 0;
    double totalTurnaroundTime = 0;
    for (const auto& p : processes) {
        totalWaitingTime += p.waitingTime;
        totalTurnaroundTime += p.turnaroundTime;
    }

    cout << "\nAverage Waiting Time: " << totalWaitingTime / n << endl;
    cout << "Average Turnaround Time: " << totalTurnaroundTime / n << endl;

    return 0;
}
