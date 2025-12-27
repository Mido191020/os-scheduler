# CPU Scheduling Simulator

A simple C++ simulator for CPU scheduling algorithms based on OSTEP concepts.

## Status

**Completed: M1 & M2**

### M1: FIFO Scheduler
Basic First-In, First-Out scheduling with turnaround time metrics. Demonstrates the Convoy Effect where long jobs block short ones.

### M2: SJF Scheduler  
Shortest Job First scheduling that solves the Convoy Effect by running shortest jobs first, improving average turnaround time by ~50%.

## Build & Run

```bash
g++ main.cpp -o scheduler
./scheduler
```

## Example Results

**FIFO:** Jobs A(30s), B(20s), C(10s) → Avg Turnaround = 46.67 ticks  
**SJF:** Jobs C(10s), B(20s), A(30s) → Avg Turnaround = 33.33 ticks

## Roadmap

* [x] M1: FIFO & Turnaround Time
* [x] M2: Shortest Job First (SJF)
* [ ] M3: Preemptive STCF
* [ ] M4: Round Robin
* [ ] M5: I/O Handling
