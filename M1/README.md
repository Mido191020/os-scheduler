# M1 Folder: FIFO & SJF Schedulers

Two foundational CPU scheduling implementations from OSTEP Chapter 7.

---

## What's Inside

### FIFO_ALGORITHM.cpp
**First-In, First-Out (FCFS) scheduling** - processes execute in arrival order.

- **The Problem:** Long jobs block short ones (Convoy Effect)
- **Example:** Jobs A(30s), B(20s), C(10s) → Avg Turnaround = 46.67 ticks
- **Non-preemptive:** Once started, a job runs to completion

### SJF_Scheduler_ALGORITHM.cpp
**Shortest Job First scheduling** - always picks the job with shortest total duration.

- **The Solution:** Eliminates Convoy Effect by prioritizing short jobs
- **Example:** Jobs C(10s), B(20s), A(30s) → Avg Turnaround = 33.33 ticks (~50% improvement)
- **Non-preemptive:** Cannot interrupt running jobs for shorter arrivals

---

## Build & Run

```bash
# FIFO Scheduler
g++ FIFO_ALGORITHM.cpp -o fifo
./fifo

# SJF Scheduler
g++ SJF_Scheduler_ALGORITHM.cpp -o sjf
./sjf
```

---

## Key Insight

SJF proves that execution order matters. By running shortest jobs first, we cut average turnaround time in half compared to FIFO. However, both algorithms share a critical limitation: they cannot preempt running jobs when better options arrive later.

**Next Step:** M2_STCF folder implements preemption to handle late arrivals efficiently.
