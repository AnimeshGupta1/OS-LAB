#include <iostream>
using namespace std;

struct Process {
	int processID; // Process ID
	int burstTime; // Burst Time
	int arrivalTime; // Arrival Time
};

void calculateWaitingTime(Process proc[], int n, int waitingTime[], int timeQuantum) {
	int remainingBurstTime[n];
	for (int i = 0 ; i < n ; i++) 
		remainingBurstTime[i] = proc[i].burstTime; 

	int currentTime = 0; 

	while (true) {
		bool allProcessesDone = true; 

		for (int i = 0 ; i < n; i++) { 
			if (remainingBurstTime[i] > 0) { 
				allProcessesDone = false; 

				if (remainingBurstTime[i] > timeQuantum) { 
					currentTime += timeQuantum; 
					remainingBurstTime[i] -= timeQuantum; 
				} 
				else { 
					currentTime = currentTime + remainingBurstTime[i]; 
					waitingTime[i] = currentTime - proc[i].burstTime - proc[i].arrivalTime; 
					remainingBurstTime[i] = 0; 
				} 
			} 
		} 

		if (allProcessesDone) 
			break; 
	} 
} 

void calculateTurnAroundTime(Process proc[], int n, int waitingTime[], int turnAroundTime[]) {
	for (int i = 0; i < n ; i++) 
		turnAroundTime[i] = proc[i].burstTime + waitingTime[i]; 
} 

void calculateAverageTime(Process proc[], int n, int timeQuantum) {
	int waitingTime[n], turnAroundTime[n], totalWaitingTime = 0, totalTurnaroundTime = 0; 

	calculateWaitingTime(proc, n, waitingTime, timeQuantum); 

	calculateTurnAroundTime(proc, n, waitingTime, turnAroundTime); 

	cout << "PN\t " << "\tBT " << " WT " << " \tTAT\n"; 

	for (int i=0; i<n; i++) { 
		totalWaitingTime = totalWaitingTime + waitingTime[i]; 
		totalTurnaroundTime = totalTurnaroundTime + turnAroundTime[i]; 
		cout << " " << proc[i].processID << "\t\t" << proc[i].burstTime <<"\t " << waitingTime[i] <<"\t\t " << turnAroundTime[i] <<endl; 
	} 

	cout << "Average waiting time = " << (float)totalWaitingTime / (float)n; 
	cout << "\nAverage turn around time = " << (float)totalTurnaroundTime / (float)n; 
} 

int main() {
	Process proc[] = { { 1, 6, 2 }, { 2, 2, 5 }, { 3, 8, 1 }, { 4, 3, 0}, {5, 4, 4} };
	int n = sizeof(proc) / sizeof(proc[0]);

	int timeQuantum = 2; 
	calculateAverageTime(proc, n, timeQuantum); 
	return 0; 
} 
