# 🧠 SchedLab — CPU Scheduling Simulator (OSTEP Chapter 7)

## Overview

**SchedLab** is a discrete-event CPU scheduling simulator built to deeply understand the ideas in **Chapter 7: Scheduling – Introduction** from *Operating Systems: Three Easy Pieces (OSTEP)*. This project is **not an OS kernel**. It is a **research-style simulation framework**, similar to what OS designers and researchers use to reason about scheduling policies, workload assumptions, and performance trade-offs.

The goal is not just to "implement algorithms", but to **experiment, measure, and explain** why different schedulers behave the way they do.

---

## Motivation

Reading OSTEP explains *what* schedulers do. **SchedLab exists to answer:**

* *Why do schedulers behave this way?*
* *Under which assumptions do they succeed or fail?*
* *How do metrics like turnaround, response time, and fairness conflict?*

Every design decision in this project maps directly to a conceptual step in Chapter 7.

---

## Core Ideas Explored

This project is built around the following **core OS concepts**:

* **Mechanism vs Policy**
* **Workload assumptions**
* **Non-preemptive vs preemptive scheduling**
* **Turnaround time vs response time**
* **Fairness vs throughput**
* **CPU-bound vs I/O-bound behavior**

---

## Project Structure

```
schedlab/
│
├── core/
│   ├── job.py              # Job / process abstraction
│   ├── cpu.py              # CPU state and execution
│   ├── event.py            # Arrival, completion, I/O events
│   └── simulator.py        # Discrete-event simulation engine
│
├── schedulers/
│   ├── base.py             # Scheduler interface
│   ├── fifo.py             # First-In First-Out
│   ├── sjf.py              # Shortest Job First
│   ├── stcf.py             # Shortest Time-to-Completion First
│   └── round_robin.py      # Round Robin
│
├── workload/
│   ├── generators.py       # Synthetic workloads
│   └── assumptions.py      # Explicit workload assumptions
│
├── metrics/
│   ├── turnaround.py       # Turnaround time
│   ├── response.py         # Response time
│   └── fairness.py         # Fairness metrics
│
├── experiments/
│   ├── exp_fifo_vs_sjf.py
│   ├── exp_response_time.py
│   └── exp_io_overlap.py
│
├── visualization/
│   ├── timeline.py         # Gantt-style timelines
│   └── charts.py           # Metric plots
│
├── report.md               # Experimental results & conclusions
└── README.md
```

---

## Scheduling Policies Implemented

SchedLab implements classic schedulers exactly as introduced in OSTEP:

* **FIFO** — First-In First-Out
* **SJF** — Shortest Job First
* **STCF** — Shortest Time-to-Completion First (preemptive SJF)
* **Round Robin (RR)** — Time-sliced fairness-oriented scheduling

Each scheduler is **pluggable** and operates over the same simulation engine.

---

## Metrics Collected

The simulator measures and compares:

* **Turnaround Time**
  > Completion time − Arrival time

* **Response Time**
  > First run − Arrival time

* **Fairness**
  > Distribution of CPU time across jobs

These metrics are intentionally analyzed **together**, not in isolation.

---

## Experiments Conducted

The project is driven by experiments, not demos. Required experiments include:

1. **FIFO Convoy Effect**
   Demonstrates worst-case turnaround behavior

2. **FIFO vs SJF**
   Shows why job length matters

3. **STCF with Late Arrivals**
   Demonstrates the power of preemption

4. **Round Robin Time-Slice Sensitivity**
   Explores fairness vs performance trade-offs

5. **CPU + I/O Overlap**
   Shows utilization improvements with blocking jobs

All experiment results are documented in `report.md`.

---

## Design Philosophy

* **Assumptions are explicit**, not hidden
* **Policies are isolated** from mechanisms
* **Visualization is mandatory**, not optional
* **Experiments drive conclusions**, not intuition

If a result cannot be visualized or measured, it is not trusted.

---

## What This Project Teaches (Explicitly)

By completing this project, you will understand:

* Why FIFO is simple but dangerous
* Why SJF is optimal *only under perfect knowledge*
* Why preemption changes everything
* Why fairness and performance are in tension
* Why real schedulers are compromises, not ideals

This is **systems thinking**, not just algorithm implementation.

---

## Background Reading

* *Operating Systems: Three Easy Pieces*
  * Chapter 7 — Scheduling: Introduction
  * Chapter 8 — Multi-Level Feedback Queue (future extension)

---

## Future Extensions

Planned or optional extensions:

* Runtime estimation (no oracle)
* Priority aging
* Jain's Fairness Index
* Multi-core CPU simulation
* MLFQ scheduler (Chapter 8)
* Comparison with Linux CFS (conceptual)

---

## Status

🚧 **In Progress**

Currently implementing milestones sequentially, following the structure of OSTEP Chapter 7.

---

## Why This Project Matters

This project demonstrates:

* Strong **computer systems fundamentals**
* Ability to translate theory into experiments
* Research-style thinking
* Clean separation of concerns
* Deep understanding of OS design trade-offs

It is designed to be discussed in **technical interviews**, not just shown.

---

## Getting Started

```bash
# Clone the repository
git clone https://github.com/yourusername/schedlab.git
cd schedlab

# Install dependencies (if any)
pip install -r requirements.txt

# Run an experiment
python experiments/exp_fifo_vs_sjf.py

# Generate visualizations
python visualization/timeline.py
```

---

## License

MIT License - See LICENSE file for details

---

## Contact

For questions or discussion about this project, please open an issue or reach out directly.

---

*Built with a focus on understanding, not just implementation.*
