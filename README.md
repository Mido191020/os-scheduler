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

**How it works:** Jobs execute in the order they arrive.

**The problem:** Long jobs create a "convoy effect" where short jobs get stuck waiting behind them, causing poor average turnaround time.

**Status:** Implemented in `M1/` and `main.cpp`

---

### Milestone 2: SJF (Shortest Job First)

**How it works:** Always picks the job with the shortest total duration.

**What it solves:** Eliminates the convoy effect by prioritizing short jobs.

**The limitation:** Non-preemptive design means it can't interrupt a running job, even if a shorter one arrives.

**Status:** Implemented in `M2_STCF/` and `main.cpp`

---

### Milestone 3: STCF (Shortest Time-to-Completion First)

**How it works:** Preemptive version of SJF. At every tick, the scheduler checks if any job has less remaining time than the current one.

**What it solves:** Handles late arrivals efficiently through preemption.

**Performance:** Achieves optimal average turnaround time.

**Status:** Implemented in `M2_STCF/` and `main.cpp`

---

### Milestone 4: Round Robin (RR)

**How it works:** Each job runs for a fixed time slice (quantum) before the scheduler switches to the next job in a circular queue.

**What it solves:** Optimizes response time and fairness. No job waits too long before getting CPU time, which is critical for interactive systems.

**The trade-off:** Average turnaround time suffers compared to STCF/SJF due to constant context switching.

**Status:** Implemented in `main.cpp`

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
