#include <stdio.h>
#include <stdlib.h>

// Process structure
typedef struct {
    int id;                 // Process ID
    int arrival_time;       // Arrival time
    int burst_time;         // CPU burst time
    int priority;           // Priority (for priority scheduling)
    int waiting_time;       // Time spent waiting
    int turnaround_time;    // Total time from arrival to completion
    int remaining_time;     // Remaining burst time (for Round Robin)
} Process;

// Function prototypes
void fcfs(Process processes[], int n);
void round_robin(Process processes[], int n, int quantum);
void calculate_metrics(Process processes[], int n);
void display_processes(Process processes[], int n);

int main() {
    int n, choice, quantum;

    // Input: Number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    // Input: Process details
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        printf("Enter priority for process %d: ", i + 1);
        scanf("%d", &processes[i].priority);

        processes[i].id = i + 1;                 // Assign process ID
        processes[i].remaining_time = processes[i].burst_time; // For RR
        processes[i].waiting_time = 0;          // Initialize waiting time
        processes[i].turnaround_time = 0;       // Initialize turnaround time
    }

    // Menu for scheduling algorithms
    printf("\nSelect Scheduling Algorithm:\n");
    printf("1. First-Come-First-Serve (FCFS)\n");
    printf("2. Round Robin (RR)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            fcfs(processes, n);
            break;
        case 2:
            printf("Enter time quantum for Round Robin: ");
            scanf("%d", &quantum);
            round_robin(processes, n, quantum);
            break;
        default:
            printf("Invalid choice! Exiting.\n");
            return 1;
    }

    // Calculate and display metrics
    calculate_metrics(processes, n);
    display_processes(processes, n);

    return 0;
}

// FCFS Scheduling
void fcfs(Process processes[], int n) {
    int current_time = 0;

    for (int i = 0; i < n; i++) {
        // Wait for process arrival
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }

        // Calculate waiting and turnaround times
        processes[i].waiting_time = current_time - processes[i].arrival_time;
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
        current_time += processes[i].burst_time; // Increment time
    }
}

// Round Robin Scheduling
void round_robin(Process processes[], int n, int quantum) {
    int current_time = 0, completed = 0;

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                if (processes[i].remaining_time > quantum) {
                    current_time += quantum;
                    processes[i].remaining_time -= quantum;
                } else {
                    current_time += processes[i].remaining_time;
                    processes[i].remaining_time = 0;

                    // Calculate turnaround and waiting times
                    processes[i].turnaround_time = current_time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                    completed++;
                }
            }
        }
    }
}

// Calculate average metrics
void calculate_metrics(Process processes[], int n) {
    int total_waiting_time = 0, total_turnaround_time = 0;

    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

// Display processes and their details
void display_processes(Process processes[], int n) {
    printf("\nProcess Details:\n");
    printf("ID\tArrival\tBurst\tPriority\tWaiting\tTurnaround\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\n",
               processes[i].id,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].priority,
               processes[i].waiting_time,
               processes[i].turnaround_time);
    }
}
