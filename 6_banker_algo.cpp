#include <iostream>
using namespace std;

// Function to check if a process can finish with current available resources
bool canFinishProcess(int process, int need[][4], int available[], int n, int m) {
  for (int j = 0; j < m; j++) {
    if (need[process][j] > available[j]) {
      return false; // Process needs more resources than available
    }
  }
  return true;
}

int main() {
  // Number of processes and resources
  int n = 5;  // Processes (P0, P1, P2, P3, P4)
  int m = 4;  // Resources (R0, R1, R2, R3)

  // Allocation matrix (represents resources currently held by each process)
  int allocation[5][4] = {
    {3, 1, 2, 1},  // P0
    {2, 0, 0, 2},  // P1
    {1, 3, 2, 1},  // P2
    {2, 1, 1, 0},  // P3
    {0, 0, 2, 0}   // P4
  };

  // Maximum matrix (represents maximum resource needs of each process)
  int max_need[5][4] = {
    {7, 5, 3, 4},  // P0
    {4, 2, 2, 2},  // P1
    {5, 4, 2, 2},  // P2
    {2, 2, 2, 1},  // P3
    {4, 3, 3, 2}   // P4
  };

  // Available resources (initially available)
  int available[4] = {3, 3, 2, 1};

  // Finished processes (stores process IDs in safe sequence)
  int finished[n] = {0};

  // Number of finished processes
  int num_finished = 0;

  // Loop until all processes are finished or a deadlock is detected
  while (num_finished < n) {
    int safe = 0; // Flag to check if any process can finish in this iteration

    // Check for each process if it can finish with current available resources
    for (int i = 0; i < n; i++) {
      if (finished[i] == 0 && canFinishProcess(i, max_need, available, n, m)) {
        // Process can finish, update resources and mark as finished
        for (int j = 0; j < m; j++) {
          available[j] += allocation[i][j];
        }
        finished[i] = 1;
        safe = 1;
      }
    }

    // If no process can finish, deadlock detected
    if (safe == 0) {
      cout << "Deadlock detected. System is in unsafe state." << endl;
      break;
    }

    num_finished++;  // Increment finished process count
  }

  // If all processes finished, print the safe sequence
  if (num_finished == n) {
    cout << "Following is the SAFE Sequence" << endl;
    for (int i = 0; i < n - 1; i++) {
      cout << " P" << i << " ->";
    }
    cout << " P" << n - 1 << endl;
  }

  return 0;
}
