# OS-Scheduler (SchedLab)

A C++ scheduler simulation engine for exploring CPU scheduling algorithms. This project implements core concepts from OSTEP Chapter 7, examining the trade-offs between Turnaround Time, Response Time, and Fairness in operating systems.

---

## Project Structure

This repository uses a "Snapshot" approach to preserve code at each learning stage:

```text
os-scheduler/
├── M1/                  # Milestone 1: FIFO & Basic Metrics
├── M2_STCF/            # Milestones 2 & 3: SJF & STCF with Preemption
├── M3_Round_Robin/     # Milestone 4: Round Robin implementation
├── main.cpp            # Current active engine (all policies: FIFO, SJF, STCF, RR)
├── CMakeLists.txt      # Build configuration
└── README.md           # This file
```

---

## What This Project Does

This simulator helps you understand how different CPU scheduling algorithms work and why operating systems make specific design choices. Each algorithm has strengths and weaknesses that become clear through experimentation.

---

## Scheduling Algorithms

### Milestone 1: FIFO (First-In, First-Out)

First Come First Served (FIFO/FCFS) is a scheduling algorithm in which the process that arrives first is executed first. It is a simple and easy-to-understand algorithm, but it can lead to poor performance if there are processes with long burst times.

**How it works:** Jobs execute in the order they arrive. The process that arrives first is executed first, regardless of its burst time or priority.

**The problem:** Long jobs create a "convoy effect" where short jobs get stuck waiting behind them, causing poor average turnaround time. This algorithm does not have any mechanism for prioritizing processes, so it is considered a non-preemptive algorithm.

**Use case:** Commonly used in batch systems where the order of the processes is important.

**Status:** Implemented in `M1/` and `main.cpp`

---

### Milestone 2: SJF (Shortest Job First)

Shortest Process Next (SJF/SPN) is a scheduling algorithm that prioritizes the execution of processes based on their burst time, or the amount of time they need to complete their task. It is a non-preemptive algorithm which means that once a process starts executing, it runs until completion or until it enters a waiting state.

**How it works:** The algorithm maintains a queue of processes, where each process is given a burst time when it arrives. The process with the shortest burst time is executed first, and as new processes arrive, they are added to the queue and sorted based on their burst time.

**What it solves:** Eliminates the convoy effect by prioritizing short jobs. This can be beneficial in situations where the objective is to minimize the average waiting time for processes, since shorter processes will be executed first.

**The limitation:** Non-preemptive design means it can't interrupt a running job, even if a shorter one arrives. This can lead to longer running processes being blocked by shorter ones in some scenarios.

**Status:** Implemented in `M2_STCF/` and `main.cpp`

---

### Milestone 3: STCF (Shortest Time-to-Completion First)

Shortest Remaining Time (STCF/SRT) is a scheduling algorithm that is similar to the Shortest Process Next (SPN) algorithm, but it is a preemptive algorithm. This means that once a process starts executing, it can be interrupted by a new process with a shorter remaining time.

**How it works:** The algorithm maintains a queue of processes, where each process is given a burst time when it arrives. At every tick, the scheduler checks if any job has less remaining time than the current one. The process with the shortest remaining time is executed first, and as new processes arrive, they are added to the queue and sorted based on their remaining time.

**What it solves:** Handles late arrivals efficiently through preemption. The algorithm can adapt to changes in the remaining time as processes execute, making it useful when burst time is not known in advance.

**Performance:** Achieves optimal average turnaround time. Minimizes average waiting time for processes since shorter processes will be executed first.

**Status:** Implemented in `M2_STCF/` and `main.cpp`

---

### Milestone 4: Round Robin (RR)

Round Robin (RR) is a scheduling algorithm that uses a time-sharing approach to divide CPU time among processes. Each job runs for a fixed time slice (quantum) before the scheduler switches to the next job in a circular queue.

**How it works:** The algorithm maintains a queue of processes, where each process is given a quantum of time to execute on the CPU. When a process's quantum expires, it is moved to the back of the queue, and the next process in the queue is given a quantum of time to execute.

**What it solves:** Optimizes response time and fairness. No job waits too long before getting CPU time, which is critical for interactive systems. This helps to avoid the issue of starvation, which occurs when a process with a long burst time prevents other processes from executing.

**The trade-off:** Average turnaround time suffers compared to STCF/SJF due to constant context switching. The quantum can be adjusted depending on the requirements of the system.

**Status:** Implemented in `M3_Round_Robin/` and `main.cpp`

---

## Technical Details

**Language:** C++

**Design:** Monolithic structure in `main.cpp` for educational clarity

**Policy Switching:** Uses function pointers to dynamically select between FIFO, SJF, STCF, and RR

**Logging:** Tracks context switches and only logs when the CPU changes tasks

**Metrics:** Calculates Turnaround Time (completion - arrival) and Response Time (first run - arrival)

---

## Performance Comparisons

### Scenario 1: The Late Arrival Problem

Job A (100 ticks) starts running. Job B (20 ticks) arrives at T=90.

| Algorithm | Decision Based On | What Happens | Avg Turnaround |
|-----------|------------------|--------------|----------------|
| **SJF** | Total duration | Preempts Job A (100 > 20) | 70 ticks |
| **STCF** | Remaining time | Continues Job A (10 < 20) | 65 ticks (better) |

STCF wins because it considers remaining time, not total duration.

---

### Scenario 2: Interactive Workload

Three jobs (5 seconds each) arrive at T=0.

| Algorithm | Avg Response Time | Avg Turnaround Time |
|-----------|------------------|---------------------|
| **STCF** | 5.0s (poor) | 10.0s (optimal) |
| **RR** | 2.0s (optimal) | 12.0s (poor) |

Round Robin prioritizes getting each job started quickly, while STCF minimizes total completion time. The right choice depends on whether you're building a batch system or an interactive one.

---

## How to Run

### Using G++ (Command Line)

```bash
g++ main.cpp -o main
./main
```

### Using CMake (CLion or VS Code)

1. Open the project in your IDE
2. Reload the CMake configuration
3. Build and run the `main` target

---

## What's Next

- [x] Milestone 1: FIFO & Basic Metrics
- [x] Milestone 2: SJF & Convoy Effect Resolution
- [x] Milestone 3: STCF & Preemptive Scheduling
- [x] Milestone 4: Round Robin (Response Time Optimization)
- [ ] Milestone 5: I/O Overlap Simulation
- [ ] Milestone 6: Multi-Level Feedback Queue (MLFQ)

---

## Why This Matters

Understanding scheduling is fundamental to systems programming. This simulator lets you see the concrete consequences of algorithm design choices. When you run these simulations, you'll understand why:

- Interactive systems use time-slicing (Round Robin)
- Batch systems prefer shortest-job-first approaches
- Modern operating systems use sophisticated multi-level queues
- There's no single "best" scheduler—it depends on your workload

---

## Resources

- **OSTEP Chapter 7:** Scheduling Introduction
