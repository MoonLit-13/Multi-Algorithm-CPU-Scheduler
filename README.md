# Multi-Algorithm CPU Scheduler - Implementation Summary

## Overview
A comprehensive C++ program implementing four major CPU scheduling algorithms used in operating systems.

## Implemented Algorithms

### 1. **FCFS (First Come First Served)**
- Processes are executed in the order they arrive
- Non-preemptive scheduling
- Simple and fair but may cause long waiting times

### 2. **SJF (Shortest Job First)**
- Selects the process with the shortest burst time
- Non-preemptive scheduling
- Minimizes average waiting time
- Can cause starvation of longer jobs

### 3. **Round Robin (RR)**
- Each process gets a fixed time quantum
- Preemptive scheduling
- If a process uses more than its quantum, it goes to the end of the queue
- Fair and prevents starvation
- Time quantum is user-defined

### 4. **Priority Scheduling**
- Processes are scheduled based on priority levels
- Lower priority number = higher priority
- Non-preemptive scheduling
- Can cause starvation of low-priority processes

## Features

- **Process Class**: Encapsulates process information
  - PID (Process ID)
  - Arrival Time
  - Burst Time
  - Priority Level
  - Completion Time, Turnaround Time, Waiting Time (calculated)

- **Scheduler Class**: Contains static methods for each algorithm
  - Calculates scheduling metrics for each process
  - Generates detailed scheduling results
  - Returns execution segments for visualization

- **Gantt Chart Visualization**:
  - ASCII-based visual representation of process scheduling
  - Shows process execution timeline with bars
  - Displays execution duration for each segment
  - Includes time markers and process details table
  - Supports preemptive scheduling visualization (multiple segments per process)

- **User Interface**:
  - Interactive menu-driven interface
  - Selection of different scheduling algorithms
  - Customizable time quantum for Round Robin
  - Detailed metrics display with formatting
  - Visual Gantt chart for each algorithm execution

## Performance Metrics

For each algorithm, the program calculates and displays:
- **Completion Time**: When the process finishes
- **Turnaround Time**: Completion Time - Arrival Time
- **Waiting Time**: Turnaround Time - Burst Time
- **Average Turnaround Time**: Mean turnaround time for all processes
- **Average Waiting Time**: Mean waiting time for all processes

## Gantt Chart Visualization

The program provides a detailed ASCII-based Gantt chart for each scheduling algorithm:

### Chart Components:
- **Timeline**: Visual representation showing when each process executes
- **Process Bars**: Equal signs (=) represent CPU time allocated to each process
- **Duration Labels**: Shows the duration of each execution segment in parentheses
- **Process Details Table**: Lists each process with exact start time, end time, and duration
- **Time Markers**: Numbered timeline reference

### Example Output (Round Robin with Quantum=2):
```
P1   |==(2)
P2   |  ==(2)
P3   |    ==(2)
...
P1   |                   ==(2)
P2   |                     ==(2)
```

The Gantt chart clearly shows:
- Non-preemptive algorithms (FCFS, SJF, Priority) with single execution blocks per process
- Preemptive algorithms (Round Robin) with multiple execution segments per process
- Idle time periods in the CPU schedule

## Sample Process Data

The program includes 5 sample processes:
- Process 1: Arrival=0, Burst=8, Priority=1
- Process 2: Arrival=1, Burst=4, Priority=2
- Process 3: Arrival=2, Burst=2, Priority=1
- Process 4: Arrival=3, Burst=1, Priority=3
- Process 5: Arrival=4, Burst=3, Priority=2

## Compilation

```bash
g++-13 -o "Multi-Algorithm CPU Scheduler" "Multi-Algorithm CPU Scheduler.cpp"
```

## Execution

```bash
./"Multi-Algorithm CPU Scheduler"
```

## Requirements Met

✓ Object-oriented design with Process class

✓ Multiple scheduling algorithms

✓ Correct calculation of scheduling metrics

✓ Interactive menu system

✓ Formatted output display

✓ Proper memory management

✓ User input validation capabilities

✓ Gantt chart visualization for all algorithms

✓ Execution segment tracking for preemptive and non-preemptive scheduling
