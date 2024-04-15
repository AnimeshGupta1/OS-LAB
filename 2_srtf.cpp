#include <bits/stdc++.h>
using namespace std;

struct Process {
	int processID; // Process ID
	int burstTime; // Burst Time
	int arrivalTime; // Arrival Time
};

void findWaitingTime(Process proc[], int n, int waitingTime[]) {
	int remainingTime[n];

	for (int i = 0; i < n; i++)
		remainingTime[i] = proc[i].burstTime;

	int complete = 0, currentTime = 0, minBurst = INT_MAX;
	int shortestIndex = 0, finishTime;
	bool check = false;

	while (complete != n) {

		for (int j = 0; j < n; j++) {
			if ((proc[j].arrivalTime <= currentTime) &&
			(remainingTime[j] < minBurst) && remainingTime[j] > 0) {
				minBurst = remainingTime[j];
				shortestIndex = j;
				check = true;
			}
		}

		if (check == false) {
			currentTime++;
			continue;
		}

		remainingTime[shortestIndex]--;

		minBurst = remainingTime[shortestIndex];
		if (minBurst == 0)
			minBurst = INT_MAX;

		if (remainingTime[shortestIndex] == 0) {

			complete++;
			check = false;

			finishTime = currentTime + 1;

			waitingTime[shortestIndex] = finishTime -
						proc[shortestIndex].burstTime -
						proc[shortestIndex].arrivalTime;

			if (waitingTime[shortestIndex] < 0)
				waitingTime[shortestIndex] = 0;
		}
		currentTime++;
	}
}

void findTurnAroundTime(Process proc[], int n, int waitingTime[], int turnAroundTime[]) {
	for (int i = 0; i < n; i++)
		turnAroundTime[i] = proc[i].burstTime + waitingTime[i];
}

void findAverageTime(Process proc[], int n) {
	int waitingTime[n], turnAroundTime[n], totalWaitingTime = 0, totalTurnaroundTime = 0;

	findWaitingTime(proc, n, waitingTime);

	findTurnAroundTime(proc, n, waitingTime, turnAroundTime);

	cout << " P\t\t"
		<< "BT\t\t"
		<< "WT\t\t"
		<< "TAT\t\t\n";

	for (int i = 0; i < n; i++) {
		totalWaitingTime = totalWaitingTime + waitingTime[i];
		totalTurnaroundTime = totalTurnaroundTime + turnAroundTime[i];
		cout << " " << proc[i].processID << "\t\t"
			<< proc[i].burstTime << "\t\t " << waitingTime[i]
			<< "\t\t " << turnAroundTime[i] << endl;
	}

	cout << "\nAverage waiting time = "
		<< (float)totalWaitingTime / (float)n;
	cout << "\nAverage turn around time = "
		<< (float)totalTurnaroundTime / (float)n;
}

int main() {
	Process proc[] = { { 1, 6, 2 }, { 2, 2, 5 },
					{ 3, 8, 1 }, { 4, 3, 0}, {5, 4, 4} };
	int n = sizeof(proc) / sizeof(proc[0]);

	findAverageTime(proc, n);
	return 0;
}
