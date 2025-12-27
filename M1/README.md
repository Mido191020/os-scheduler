## 🚀 Current Status: Milestone 1 (FIFO) 

The project currently implements a basic **First-In, First-Out (FIFO)** scheduler to demonstrate the fundamental trade-offs in batch processing systems. 

 

### Features 

* **Tick-based Simulation Engine:** Simulates CPU cycles and state transitions. 

* **Job Abstraction:** Tracks Process ID, Arrival Time, Duration, and Remaining Time. 

* **FIFO Policy:** Implements non-preemptive scheduling based on arrival order. 

* **Metrics:** Calculates **Turnaround Time** and system average. 

* **Convoy Effect Demo:** Demonstrates how long jobs blocking short jobs degrades system performance (Average Turnaround doubled from ~33 to ~66 ticks). 

 

## 🛠️ How to Build & Run 

 

**Prerequisites:** 

* C++ Compiler (GCC/Clang/MSVC) 

* Make or CMake (Optional, currently single file) 

 

**Build:** 

```bash 

g++ main.cpp -o scheduler 

 

``` 

 

**Run:** 

 

```bash 

./scheduler 

 

``` 

 

## 📊 Example Output 

 

```text 

Time 0: Running Job 1 

... 

Job 1 Finished at time 10 

... 

Job 3 Finished at time 60 

 

--- Final Metrics --- 

Job 1: Turnaround Time = 10 ticks 

Job 2: Turnaround Time = 30 ticks 

Job 3: Turnaround Time = 60 ticks 

-------------------------------- 

Average Turnaround Time = 33.3333 ticks 

-------------------------------- 

 

``` 

 

## 📚 Roadmap 

 

* [x] **M1: FIFO & Turnaround Time** 

* [ ] M2: Shortest Job First (SJF) 

* [ ] M3: Preemption & STCF 

* [ ] M4: Round Robin & Response Time 

* [ ] M5: I/O Overlap 

 

```
