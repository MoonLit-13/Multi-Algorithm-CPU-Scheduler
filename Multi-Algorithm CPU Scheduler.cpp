#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <climits>

using namespace std;

class Process {
    private:
        int PID;
        int arrivalTime;
        int burstTime;
        int priority;
        int remainingTime;

    public:
        int completionTime;
        int turnaroundTime;
        int waitingTime;

        Process(int PID, int arrivalTime, int burstTime, int priority) {
            this->PID = PID;
            this->arrivalTime = arrivalTime;
            this->burstTime = burstTime;
            this->priority = priority;
            this->remainingTime = burstTime;
            this->completionTime = 0;
            this->turnaroundTime = 0;
            this->waitingTime = 0;
        }

        // Getter methods (const - read-only, cannot modify object state)
        // Returns the unique Process ID identifier
        int getPID() const { return PID; }
        
        // Returns the time when this process arrives in the system
        int getArrivalTime() const { return arrivalTime; }
        
        // Returns the total CPU time required to complete this process
        int getBurstTime() const { return burstTime; }
        
        // Returns the priority level (lower number = higher priority)
        int getPriority() const { return priority; }
        
        // Returns the remaining CPU time still needed (changes during execution)
        int getRemainingTime() const { return remainingTime; }

        // Setter methods - modify process state during scheduling
        // Updates remaining time when a time quantum expires (used in Round Robin)
        void setRemainingTime(int time) { remainingTime = time; }
        
        // Records the completion time when process finishes execution
        void setCompletionTime(int time) { completionTime = time; }
        
        // Calculator methods - derive metrics from completion time and arrival time
        // Calculates turnaround time: how long from arrival to completion
        void calculateTurnaroundTime() { turnaroundTime = completionTime - arrivalTime; }
        
        // Calculates waiting time: total time waiting (turnaround - actual execution)
        void calculateWaitingTime() { waitingTime = turnaroundTime - burstTime; }
};

class Scheduler {
public:
    // FCFS - First Come First Served
    static void FCFS(vector<Process>& processes) {
        sort(processes.begin(), processes.end(),
             [](const Process& a, const Process& b) {
                 return a.getArrivalTime() < b.getArrivalTime();
             });

        int currentTime = 0;
        for (auto& p : processes) {
            if (currentTime < p.getArrivalTime()) {
                currentTime = p.getArrivalTime();
            }
            currentTime += p.getBurstTime();
            p.setCompletionTime(currentTime);
            p.calculateTurnaroundTime();
            p.calculateWaitingTime();
        }
    }

    // SJF - Shortest Job First (Non-preemptive)
    static void SJF(vector<Process>& processes) {
        vector<Process> result;
        vector<bool> processed(processes.size(), false);
        int currentTime = 0;
        int completed = 0;

        while (completed < processes.size()) {
            int shortest = -1;
            int shortestBurst = INT_MAX;

            for (int i = 0; i < processes.size(); i++) {
                if (!processed[i] && processes[i].getArrivalTime() <= currentTime &&
                    processes[i].getBurstTime() < shortestBurst) {
                    shortest = i;
                    shortestBurst = processes[i].getBurstTime();
                }
            }

            if (shortest == -1) {
                for (int i = 0; i < processes.size(); i++) {
                    if (!processed[i]) {
                        currentTime = processes[i].getArrivalTime();
                        shortest = i;
                        break;
                    }
                }
            }

            processed[shortest] = true;
            currentTime += processes[shortest].getBurstTime();
            processes[shortest].setCompletionTime(currentTime);
            processes[shortest].calculateTurnaroundTime();
            processes[shortest].calculateWaitingTime();
            completed++;
        }
    }

    // Round Robin
    static void RoundRobin(vector<Process>& processes, int timeQuantum) {
        queue<int> q;
        vector<int> remainingTime(processes.size());
        
        for (int i = 0; i < processes.size(); i++) {
            remainingTime[i] = processes[i].getBurstTime();
        }

        sort(processes.begin(), processes.end(),
             [](const Process& a, const Process& b) {
                 return a.getArrivalTime() < b.getArrivalTime();
             });

        for (int i = 0; i < processes.size(); i++) {
            q.push(i);
        }

        int currentTime = 0;
        while (!q.empty()) {
            int idx = q.front();
            q.pop();

            if (remainingTime[idx] > timeQuantum) {
                currentTime += timeQuantum;
                remainingTime[idx] -= timeQuantum;
                q.push(idx);
            } else {
                currentTime += remainingTime[idx];
                remainingTime[idx] = 0;
                processes[idx].setCompletionTime(currentTime);
                processes[idx].calculateTurnaroundTime();
                processes[idx].calculateWaitingTime();
            }
        }
    }

    // Priority Scheduling (Non-preemptive) - Lower priority number = higher priority
    static void PriorityScheduling(vector<Process>& processes) {
        vector<bool> processed(processes.size(), false);
        int currentTime = 0;
        int completed = 0;

        while (completed < processes.size()) {
            int highest = -1;
            int highestPriority = INT_MAX;

            for (int i = 0; i < processes.size(); i++) {
                if (!processed[i] && processes[i].getArrivalTime() <= currentTime &&
                    processes[i].getPriority() < highestPriority) {
                    highest = i;
                    highestPriority = processes[i].getPriority();
                }
            }

            if (highest == -1) {
                for (int i = 0; i < processes.size(); i++) {
                    if (!processed[i]) {
                        currentTime = processes[i].getArrivalTime();
                        highest = i;
                        break;
                    }
                }
            }

            processed[highest] = true;
            currentTime += processes[highest].getBurstTime();
            processes[highest].setCompletionTime(currentTime);
            processes[highest].calculateTurnaroundTime();
            processes[highest].calculateWaitingTime();
            completed++;
        }
    }
};

void displayResults(const vector<Process>& processes, const string& algorithmName) {
    cout << "\n" << string(80, '=') << endl;
    cout << "Algorithm: " << algorithmName << endl;
    cout << string(80, '=') << endl;
    cout << left << setw(8) << "PID" << setw(15) << "Arrival Time"
         << setw(12) << "Burst Time" << setw(18) << "Completion Time"
         << setw(15) << "Turnaround" << setw(12) << "Waiting" << endl;
    cout << string(80, '-') << endl;

    double avgTurnaround = 0, avgWaiting = 0;
    for (const auto& p : processes) {
        cout << left << setw(8) << p.getPID()
             << setw(15) << p.getArrivalTime()
             << setw(12) << p.getBurstTime()
             << setw(18) << p.completionTime
             << setw(15) << p.turnaroundTime
             << setw(12) << p.waitingTime << endl;
        avgTurnaround += p.turnaroundTime;
        avgWaiting += p.waitingTime;
    }

    avgTurnaround /= processes.size();
    avgWaiting /= processes.size();

    cout << string(80, '-') << endl;
    cout << "Average Turnaround Time: " << fixed << setprecision(2) << avgTurnaround << endl;
    cout << "Average Waiting Time: " << fixed << setprecision(2) << avgWaiting << endl;
}

// Function to execute the selected scheduling algorithm
void executeScheduler(vector<Process>& processes, int choice) {
    vector<Process> tempProcesses = processes;

    switch (choice) {
        case 1:
            // Execute FCFS algorithm
            Scheduler::FCFS(tempProcesses);
            displayResults(tempProcesses, "FCFS");
            break;
        case 2:
            // Execute SJF algorithm
            Scheduler::SJF(tempProcesses);
            displayResults(tempProcesses, "SJF");
            break;
        case 3: {
            // Execute Round Robin with user-defined time quantum
            int quantum;
            cout << "Enter time quantum for Round Robin: ";
            cin >> quantum;
            Scheduler::RoundRobin(tempProcesses, quantum);
            displayResults(tempProcesses, "Round Robin (Quantum = " + to_string(quantum) + ")");
            break;
        }
        case 4:
            // Execute Priority Scheduling algorithm
            Scheduler::PriorityScheduling(tempProcesses);
            displayResults(tempProcesses, "Priority Scheduling");
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
    }
}

int main() {
    // PID - Arrival Time - Burst Time - Priority
    // Change these values to test different scenarios
    vector<Process> processes = {
        Process(1, 0, 8, 1),
        Process(2, 1, 4, 2),
        Process(3, 2, 2, 1),
        Process(4, 3, 1, 3),
        Process(5, 4, 3, 2),
        Process(6, 5, 6, 2),
        Process(7, 6, 3, 1),
        Process(8, 7, 5, 3),
        Process(9, 8, 2, 2),
        Process(10, 9, 4, 1)
    };

    int choice;
    while (true) {
        cout << "\n" << string(80, '=') << endl;
        cout << "CPU SCHEDULING ALGORITHMS" << endl;
        cout << string(80, '=') << endl;
        cout << "1. FCFS (First Come First Served)" << endl;
        cout << "2. SJF (Shortest Job First)" << endl;
        cout << "3. Round Robin" << endl;
        cout << "4. Priority Scheduling" << endl;
        cout << "5. Exit" << endl;
        cout << string(80, '-') << endl;
        cout << "Enter your choice (1-5): ";
        cin >> choice;

        if (choice == 5) break;

        // Call the executeScheduler function with user choice
        executeScheduler(processes, choice);
    }

    cout << "\nThank you for using CPU Scheduler!" << endl;
    return 0;
}