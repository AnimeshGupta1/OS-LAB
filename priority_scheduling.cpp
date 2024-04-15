#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// Structure to represent a process
struct Process {
    int pid;        // Process ID
    int burst_time; // CPU Burst time required
    int priority;   // Priority of this process
};

// Function to sort the Process according to priority
bool comparePriority(Process a, Process b) {
    return (a.priority > b.priority);
}

// Function to find the waiting time for all processes
void calculateWaitingTime(const vector<Process>& processes, vector<int>& waiting_times) {
    waiting_times[0] = 0; // Waiting time for the first process is 0

    // Calculate waiting time for subsequent processes
    for (size_t i = 1; i < processes.size(); i++) {
        waiting_times[i] = processes[i - 1].burst_time + waiting_times[i - 1];
    }
}

// Function to calculate turnaround time
void calculateTurnaroundTime(const vector<Process>& processes, const vector<int>& waiting_times, vector<int>& turnaround_times) {
    // Calculate turnaround time by adding burst_time and waiting_time
    for (size_t i = 0; i < processes.size(); i++) {
        turnaround_times[i] = processes[i].burst_time + waiting_times[i];
    }
}

// Function to calculate average time
void calculateAverageTime(const vector<Process>& processes) {
    vector<int> waiting_times(processes.size(), 0);
    vector<int> turnaround_times(processes.size(), 0);
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    // Calculate waiting and turnaround times
    calculateWaitingTime(processes, waiting_times);
    calculateTurnaroundTime(processes, waiting_times, turnaround_times);

    // Display processes along with all details
    cout << "\nProcesses " << " Burst time " << " Waiting time " << " Turnaround time\n";

    // Calculate total waiting time and total turnaround time
    for (size_t i = 0; i < processes.size(); i++) {
        total_waiting_time += waiting_times[i];
        total_turnaround_time += turnaround_times[i];
        cout << " " << processes[i].pid << "\t\t" << processes[i].burst_time << "\t "
             << waiting_times[i] << "\t\t " << turnaround_times[i] << endl;
    }

    // Calculate and display average waiting time and average turnaround time
    cout << "\nAverage waiting time = " << (float)total_waiting_time / processes.size();
    cout << "\nAverage turnaround time = " << (float)total_turnaround_time / processes.size();
}

// Priority Scheduling Algorithm
void priorityScheduling(vector<Process>& processes) {
    // Sort processes by priority
    sort(processes.begin(), processes.end(), comparePriority);

    cout << "Order in which processes gets executed:\n";
    for (size_t i = 0; i < processes.size(); i++) {
        cout << processes[i].pid << " ";
    }

    calculateAverageTime(processes);
}

int main() {
    // Example processes
vector<Process> processes = {
        { 1, 10, 3 }, 
        { 2, 8, 2 }, 
        { 3, 6, 1 }, 
        { 4, 4, 0 }, 
        { 5, 2, 1 },
        { 6, 5, 2 },
        { 7, 7, 1 },
        { 8, 3, 0 }
    };
    // Number of processes
    int n = processes.size();

    // Priority Scheduling Algorithm
    priorityScheduling(processes);

    return 0;
}
