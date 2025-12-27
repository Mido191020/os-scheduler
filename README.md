# 🧠 OS-Scheduler (SchedLab)

A C++ discrete-event simulation engine designed to explore CPU scheduling algorithms. This project implements the concepts from **OSTEP Chapter 7**, focusing on the trade-offs between Turnaround Time, Response Time, and Fairness.

## 📂 Project Structure

```text
os-scheduler/
├── M1/                 # Snapshot: Milestone 1 code (FIFO & Basic Metrics)
├── M2_STCF/            # Snapshot: Milestone 2 & 3 code (SJF & Preemption)
├── main.cpp            # Current Source: Contains Engine, All Policies, and Tests
├── CMakeLists.txt      # Build configuration for CLion/CMake
└── README.md           # Project Documentation

```

---

## 🚀 Milestones & Algorithms

### ✅ Milestone 1: FIFO (First-In, First-Out)

* **Logic:** Executes jobs in the order they arrive.
* **Problem:** **The Convoy Effect**. A long job arriving first blocks short jobs, destroying Average Turnaround Time.
* **Status:** Implemented in `M1` and `main.cpp`.

### ✅ Milestone 2: SJF (Shortest Job First)

* **Logic:** Selects the job with the shortest *total duration*.
* **Solution:** Solves the Convoy Effect by moving short jobs to the front.
* **Problem:** **Late Arrival**. If a short job arrives after a long job starts, SJF cannot stop the long job (Non-preemptive).

### ✅ Milestone 3: STCF (Shortest Time-to-Completion First)

* **Logic:** Preemptive version of SJF. Checks the queue *every tick* to see if a new job has less *remaining time* than the current one.
* **Solution:** Solves the Late Arrival problem via **Preemption**.
* **Metrics:** Achieves mathematically optimal Turnaround Time.

---

## 🛠️ Technical Implementation

* **Language:** C++
* **Architecture:** Monolithic architecture in `main.cpp` for ease of learning.
* **Dependency Injection:** Uses Function Pointers to switch between `FIFO`, `SJF`, and `STCF` policies dynamically.
* **Smart Logging:** The engine detects `Context Switches` and logs only when the CPU changes tasks.

---

## 📊 Performance Comparison

Experimental results from the `Trap` scenario (Job A: 100s, Job B: 20s arrives at T=90):

| Algorithm | Decision Logic | Behavior | Avg Turnaround |
| --- | --- | --- | --- |
| **SJF** | Compare `Total Duration` | Kicks Job A out (100 > 20) | **70 ticks** (Poor) |
| **STCF** | Compare `Remaining Time` | Keeps Job A (10 < 20) | **65 ticks** (Optimal) |

---

## ⚡ How to Run

### Option 1: Using G++ (Terminal)

```bash
g++ main.cpp -o main
./main

```

### Option 2: Using CMake (CLion)

1. Reload CMake project.
2. Run the `main` configuration.

---

## 🔮 Roadmap

* [x] **M1:** FIFO & Basic Metrics
* [x] **M2:** SJF & Convoy Effect
* [x] **M3:** STCF & Preemption
* [ ] **M4:** Round Robin (Response Time)
* [ ] **M5:** I/O Overlap Simulation

```

```
