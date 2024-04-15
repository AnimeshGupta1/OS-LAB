#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int process_id;
    int arrival_time;
    int burst_time;
};

bool compareArrivalTime(const Process &a, const Process &b) {
    return a.arrival_time < b.arrival_time;
}

void fcfs(vector<Process> &processes) {
    // Sort the processes based on arrival time
    sort(processes.begin(), processes.end(), compareArrivalTime);

    // Initialize variables
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int current_time = 0;

    cout << "Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";

    for (const auto &p : processes) {
        // Calculate waiting time
        int waiting_time = max(0, current_time - p.arrival_time);

        // Calculate turnaround time
        int turnaround_time = waiting_time + p.burst_time;

        // Update total waiting and turnaround time
        total_waiting_time += waiting_time;
        total_turnaround_time += turnaround_time;

        // Update current time
        current_time += p.burst_time;

        // Print process details
        cout << p.process_id << "\t" << p.arrival_time << "\t\t" << p.burst_time << "\t\t" << waiting_time << "\t\t" << turnaround_time << "\n";
    }

    // Calculate average waiting and turnaround time
    double avg_waiting_time = static_cast<double>(total_waiting_time) / processes.size();
    double avg_turnaround_time = static_cast<double>(total_turnaround_time) / processes.size();

    cout << "\nAverage Waiting Time: " << avg_waiting_time << endl;
    cout << "Average Turnaround Time: " << avg_turnaround_time << endl;
}

int main() {
    // Example processes: (process_id, arrival_time, burst_time)
    vector<Process> processes = {
        {1, 0, 7},
        {2, 2, 4},
        {3, 4, 1},
        {4, 5, 4},
        {5, 6, 3}
    };

    fcfs(processes);

    return 0;
}
