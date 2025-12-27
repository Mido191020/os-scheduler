# 🧠 OS-Scheduler (SchedLab)

A C++ discrete-event simulation engine designed to explore CPU scheduling algorithms. This project implements concepts from **OSTEP Chapter 7**, focusing on the trade-offs between Turnaround Time, Response Time, and Fairness.

---

## 📂 Project Structure

```text
os-scheduler/
├── M1/                 # Milestone 1: FIFO & Basic Metrics
├── M2_STCF/            # Milestones 2 & 3: SJF & STCF (Preemption)
├── main.cpp            # Current Implementation: Engine, Policies, and Tests
├── CMakeLists.txt      # Build configuration for CLion/CMake
└── README.md           # Project Documentation
```

---

## 🚀 Milestones & Algorithms

### ✅ Milestone 1: FIFO (First-In, First-Out)
- **Logic:** Executes jobs in arrival order.
- **Problem:** **Convoy Effect** — A long job blocks short jobs, inflating average turnaround time.
- **Status:** Implemented in `M1/` and `main.cpp`.

### ✅ Milestone 2: SJF (Shortest Job First)
- **Logic:** Selects the job with the shortest total duration.
- **Advantage:** Eliminates the Convoy Effect by prioritizing short jobs.
- **Problem:** **Non-preemptive** — Cannot interrupt a running job if a shorter one arrives.
- **Status:** Implemented in `M2_STCF/` and `main.cpp`.

### ✅ Milestone 3: STCF (Shortest Time-to-Completion First)
- **Logic:** Preemptive version of SJF. Every tick, checks if a new job has less remaining time than the current job.
- **Advantage:** Solves the late arrival problem through preemption.
- **Metrics:** Achieves optimal average turnaround time.
- **Status:** Implemented in `M2_STCF/` and `main.cpp`.

---

## 🛠️ Technical Implementation

- **Language:** C++
- **Architecture:** Monolithic design in `main.cpp` for educational clarity.
- **Policy Switching:** Function pointers enable dynamic selection of `FIFO`, `SJF`, and `STCF` policies.
- **Smart Logging:** Tracks context switches and logs only when the CPU changes tasks.

---

## 📊 Performance Comparison

Results from the **Trap Scenario** (Job A: 100 ticks, Job B: 20 ticks arrives at T=90):

| Algorithm | Decision Logic       | Behavior                  | Avg Turnaround |
|-----------|----------------------|---------------------------|----------------|
| **SJF**   | Total Duration       | Preempts Job A (100 > 20) | 70 ticks       |
| **STCF**  | Remaining Time       | Continues Job A (10 < 20) | 65 ticks ✅    |

**Key Insight:** STCF's remaining-time logic prevents unnecessary preemption, achieving optimal turnaround.

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

- [x] **M1:** FIFO & Basic Metrics
- [x] **M2:** SJF & Convoy Effect Resolution
- [x] **M3:** STCF & Preemptive Scheduling
- [ ] **M4:** Round Robin (Optimize Response Time)
- [ ] **M5:** I/O Overlap Simulation
- [ ] **M6:** Multi-Level Feedback Queue (MLFQ)

## 📄 License

This project is educational and open for academic use.
