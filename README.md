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

- **User Interface**:
  - Interactive menu-driven interface
  - Selection of different scheduling algorithms
  - Customizable time quantum for Round Robin
  - Detailed metrics display with formatting

## Performance Metrics

For each algorithm, the program calculates and displays:
- **Completion Time**: When the process finishes
- **Turnaround Time**: Completion Time - Arrival Time
- **Waiting Time**: Turnaround Time - Burst Time
- **Average Turnaround Time**: Mean turnaround time for all processes
- **Average Waiting Time**: Mean waiting time for all processes

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
