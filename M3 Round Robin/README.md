# Round Robin (RR) Scheduler

A C++ implementation of the Round Robin scheduling algorithm demonstrating time-slicing, fairness, and response time optimization.

---

## Overview

This program simulates a Round Robin scheduler processing 10 jobs with a **time quantum of 2 ticks**. It shows how circular queuing achieves fair CPU allocation and fast response times in interactive systems.

---

## The Algorithm

### How It Works

1. Place all jobs in a circular queue
2. Execute current job for time quantum (2 ticks) or until completion
3. Switch to next job using modulo: `(x + 1) % total_jobs`
4. Skip finished jobs automatically
5. Repeat until all jobs complete

### Key Characteristics

- **Preemptive:** Jobs are interrupted after their quantum expires
- **Fair:** Every job gets equal CPU time slices
- **Circular:** Queue wraps around to ensure continuous progress
- **Interactive:** Optimized for quick response, not fast completion

---

## Test Workload

10 jobs with decreasing durations, all arriving at T=0:

```
Job 1:  100 ticks
Job 2:   90 ticks
Job 3:   80 ticks
...
Job 10:  10 ticks
```

This workload highlights Round Robin's fairness advantage over FIFO.

---

## Data Structure

```cpp
struct jobs {
    int Id;                // Job identifier
    int arrival_time;      // When job arrives (all 0 here)
    int duration;          // Total execution time needed
    int remaining;         // Ticks left to complete
    int completion_time;   // When job finishes
    int first_run_time;    // When job first runs (-1 = not started)
    status job_status;     // READY, RUNNING, or FINISHED
}
```

---

## Performance Metrics

### Turnaround Time
**Formula:** `Completion Time - Arrival Time`

Total time from job arrival to completion. Round Robin has **higher turnaround** due to context switching.

### Response Time
**Formula:** `First Run Time - Arrival Time`

Time before a job first executes. Round Robin has **lower response** because jobs start quickly.

---

## Sample Output

```
Time 2 : Job 1 running. Remaining: 98
Time 4 : Job 2 running. Remaining: 88
...
done RR

--- Final Metrics ---
Job 1: Turnaround = 1098, Response = 0 ticks
Job 2: Turnaround = 1088, Response = 2 ticks
...
Job 10: Turnaround = 1008, Response = 18 ticks
--------------------------------
Avg Turnaround = 1053 ticks
Avg Response   = 9 ticks (This should be low!)
```

---

## The Core Trade-off

| Metric | Round Robin | FIFO/SJF |
|--------|-------------|----------|
| **Avg Turnaround** | High (1053 ticks) | Low (optimal) |
| **Avg Response** | Low (9 ticks) | High (450+ ticks) |
| **Fairness** | Excellent | Poor |
| **Use Case** | Interactive systems | Batch processing |

Round Robin **sacrifices completion speed for responsiveness**.

---

## Why This Matters

### Response Time Comparison

**Round Robin:**
- Job 1 starts at T=0 (response: 0)
- Job 10 starts at T=18 (response: 18)

**FIFO (if used):**
- Job 1 starts at T=0 (response: 0)
- Job 10 starts at T=450 (response: 450)

For interactive applications, waiting 450 ticks is unacceptable. Users need immediate feedback.

---

## Time Quantum Impact

The quantum size critically affects performance:

| Quantum | Response Time | Context Switches | Behavior |
|---------|---------------|------------------|----------|
| 1 tick | Excellent | Excessive overhead | Too much switching |
| 2 ticks | Very Good | Balanced | Current setting |
| 10 ticks | Good | Reduced | Less responsive |
| 100 ticks | Poor | Minimal | Becomes FIFO-like |

**Current setting (2 ticks):** Demonstrates Round Robin characteristics without excessive overhead.

---

## How to Run

### Quick Start
```bash
g++ -o rr main.cpp
./rr
```

### Using CMake
```bash
mkdir build && cd build
cmake ..
make
./rr
```

---

## Code Components

### Main Functions

**`generate_workload()`**
Creates 10 test jobs with decreasing durations (100, 90, 80, ..., 10 ticks).

**`RR()`**
Implements the Round Robin scheduler with:
- Circular queue management
- Time quantum enforcement
- First-run time tracking
- Completion detection

**Metrics Calculation**
Computes and displays turnaround and response times for each job.

---

## Experiments to Try

Modify these values to see behavioral changes:

### 1. Change Time Quantum
```cpp
int time_quantum = 5;  // Try: 1, 5, 10, 50
```
Observe how response and turnaround times change.

### 2. Equal-Length Jobs
```cpp
newJob.duration = 50;  // All jobs same size
```
See how fairness improves predictability.

### 3. Staggered Arrivals
```cpp
newJob.arrival_time = i * 10;  // Jobs arrive over time
```
Test how Round Robin handles dynamic arrivals.

### 4. Different Workload Size
```cpp
int num_jobs = 20;  // More jobs
```
Observe scalability characteristics.

---

## Real-World Applications

Round Robin is foundational in:

- **Operating Systems:** Linux CFS, Windows thread scheduling
- **Network Routers:** Fair packet queuing
- **Virtualization:** Hypervisor CPU allocation
- **Interactive Terminals:** Multi-user time-sharing systems

---

## Implementation Details

### Circular Queue Logic
```cpp
x = (x + 1) % tasks.size();  // Wrap around to job 0 after last job
```

### Skip Finished Jobs
```cpp
if (current_job->job_status == FINISHED) {
    x = (x + 1) % tasks.size();
    continue;
}
```

### Track First Run
```cpp
if (current_job->first_run_time == -1)
    current_job->first_run_time = current_time;
```

---

## Limitations

This is a simplified educational implementation:

- **No I/O simulation:** Real jobs block during I/O operations
- **Single priority level:** Real schedulers use multiple queues
- **Fixed quantum:** Modern schedulers dynamically adjust
- **No arrival variance:** Real systems have unpredictable job arrivals

---

## Comparison with Other Schedulers

| Algorithm | Turnaround | Response | Fairness | Preemption |
|-----------|-----------|----------|----------|------------|
| **FIFO** | Medium | Poor | Poor | No |
| **SJF** | Optimal | Poor | Poor | No |
| **STCF** | Optimal | Poor | Poor | Yes |
| **RR** | Poor | Optimal | Excellent | Yes |

Round Robin is the only algorithm that **optimizes for response time**.

---

## Next Steps

Extend this implementation with:

1. **Multi-Level Feedback Queue (MLFQ):** Priority-based scheduling
2. **I/O Operations:** Job blocking and unblocking
3. **Dynamic Quantum:** Adjust based on workload characteristics
4. **Priority Aging:** Prevent starvation in priority systems
5. **Visualization:** Gantt chart generation

---

## Key Takeaway

Round Robin proves that **no single scheduler is best for all workloads**. The choice between turnaround time and response time depends on your system's purpose:

- **Batch systems** (rendering, data processing): Use SJF/STCF
- **Interactive systems** (desktops, terminals): Use Round Robin
- **Production systems** (servers, databases): Use MLFQ hybrids

---

## Reference

**OSTEP Chapter 7:** Scheduling Introduction - Understanding response time vs. turnaround time trade-offs
