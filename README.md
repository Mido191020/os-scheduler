# 🧠 OS-Scheduler (SchedLab)

A C++ discrete-event simulation engine designed to explore CPU scheduling algorithms. This project implements concepts from **OSTEP Chapter 7**, focusing on the trade-offs between Turnaround Time, Response Time, and Fairness.

---

## 📂 Project Structure

```text
os-scheduler/
├── M1/                 # Snapshot: Milestone 1 (FIFO & Basic Metrics)
├── M2_STCF/            # Snapshot: Milestones 2 & 3 (SJF & STCF)
├── main.cpp            # Current Implementation: Engine, All Policies (FIFO, SJF, STCF, RR), and Tests
├── CMakeLists.txt      # Build configuration for CLion/CMake
└── README.md           # Project Documentation

```

---

## 🚀 Milestones & Algorithms

### ✅ Milestone 1: FIFO (First-In, First-Out)

* **Logic:** Executes jobs in arrival order.
* **Problem:** **Convoy Effect** — A long job blocks short jobs, inflating average turnaround time.
* **Status:** Implemented in `M1/` and `main.cpp`.

### ✅ Milestone 2: SJF (Shortest Job First)

* **Logic:** Selects the job with the shortest total duration.
* **Advantage:** Eliminates the Convoy Effect by prioritizing short jobs.
* **Problem:** **Non-preemptive** — Cannot interrupt a running job if a shorter one arrives.
* **Status:** Implemented in `M2_STCF/` and `main.cpp`.

### ✅ Milestone 3: STCF (Shortest Time-to-Completion First)

* **Logic:** Preemptive version of SJF. Every tick, checks if a new job has less remaining time than the current job.
* **Advantage:** Solves the late arrival problem through preemption.
* **Metrics:** Achieves optimal average turnaround time.
* **Status:** Implemented in `M2_STCF/` and `main.cpp`.

### ✅ Milestone 4: Round Robin (RR)

* **Logic:** Runs each job for a fixed **Time Slice (Quantum)** before switching to the next in a circular queue.
* **Advantage:** Optimizes **Response Time** and Fairness. Ensures no job waits too long to start (vital for interactive systems).
* **Trade-off:** Poor Average Turnaround Time compared to STCF/SJF due to constant context switching.
* **Status:** Implemented in `main.cpp`.

---

## 🛠️ Technical Implementation

* **Language:** C++
* **Architecture:** Monolithic design in `main.cpp` for educational clarity.
* **Policy Switching:** Function pointers enable dynamic selection of `FIFO`, `SJF`, `STCF`, and `RR` policies.
* **Smart Logging:** Tracks context switches and logs only when the CPU changes tasks.
* **Metrics Engine:** Calculates both Turnaround Time () and Response Time ().

---

## 📊 Performance Comparison

### 1. The Trap Scenario (Optimization via STCF)

Job A (100 ticks) is running. Job B (20 ticks) arrives at T=90.

| Algorithm | Decision Logic | Behavior | Avg Turnaround |
| --- | --- | --- | --- |
| **SJF** | Total Duration | Preempts Job A (100 > 20) | 70 ticks |
| **STCF** | Remaining Time | Continues Job A (10 < 20) | 65 ticks ✅ |

### 2. The Interactive Scenario (Optimization via RR)

3 Jobs (5s each) arrive at T=0.

| Algorithm | Avg Response Time | Avg Turnaround Time |
| --- | --- | --- |
| **STCF** | 5.0s (Poor) | **10.0s (Optimal)** |
| **RR** | **2.0s (Optimal)** | 12.0s (Poor) |

---

## ⚡ How to Run

### Option 1: Using G++ (Command Line)

```bash
g++ main.cpp -o main
./main

```

### Option 2: Using CMake (CLion)

1. Open the project in CLion.
2. Reload the CMake project.
3. Run the `main` configuration.

---

## 🔮 Roadmap

* [x] **M1:** FIFO & Basic Metrics
* [x] **M2:** SJF & Convoy Effect Resolution
* [x] **M3:** STCF & Preemptive Scheduling
* [x] **M4:** Round Robin (Optimize Response Time)
* [ ] **M5:** I/O Overlap Simulation
* [ ] **M6:** Multi-Level Feedback Queue (MLFQ)

## 📄 License

This project is educational and open for academic use.

```

```
