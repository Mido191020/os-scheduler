# Proportional-Share CPU Scheduler Simulator

Project Goal: Build a proportional-share CPU scheduler simulator, inspired by Lottery, Stride, and CFS, including weights (nice), vruntime, min granularity, and sleeping/I-O processes.

## Milestone 1: Basic Lottery Scheduler

**Objective**: Understand the simplest proportional-share scheduler.

**Key Components to Implement**:
*   **Processes with tickets**:
    *   Each process has a number of tickets.
    *   Assign tickets randomly or fixed values.
*   **Lottery selection**:
    *   Generate a random number in the range of total tickets.
    *   Select the winning process based on ticket count.
*   **Simulation loop**:
    *   Each time slice, pick a process, run it, update stats.
    *   Track total execution time for fairness study.

**Goals**:
*   Think about data structures: list, array, or something else?
*   How do you track each process’s remaining time?
*   How will you simulate time slices in your program?
*   Record metrics: how fair is the scheduling?

**Questions**:
*   How do I decide the number of tickets for each process?
*   How will I handle multiple processes in one time slice?
*   How to calculate fairness at the end?

## Milestone 2: Stride Scheduler + Weighting (Nice Values)

**Objective**: Make it deterministic and introduce priority via weights.

**Key Components**:
*   **Stride calculation**:
    *   Assign `stride = large_number / tickets`.
    *   Track pass values to decide next process.
*   **Weighting/Nice values**:
    *   Map `nice → weight`.
    *   Adjust time slice and pass/vruntime updates according to weight.
*   **Deterministic scheduling**:
    *   Always pick process with lowest pass value.
    *   Update pass properly after each run.

**Goals**:
*   Decide how to implement pass updates proportional to weight.
*   Think about time slices dynamically based on process weight.
*   Test fairness ratios for processes with different weights.

**Questions**:
*   How will the program calculate `time_slice` dynamically?
*   How will I simulate the weighted fairness over multiple cycles?
*   How to represent weights in a way that scales with many processes?

## Milestone 3: CFS Simulation (Advanced)

**Objective**: Simulate a full CFS-like scheduler with vruntime, min granularity, and sleeping processes.

**Key Components**:
*   **Virtual runtime (vruntime)**:
    *   Accumulate vruntime for each process.
    *   Pick process with lowest vruntime to run next.
*   **Dynamic time slices & min granularity**:
    *   Compute per-process slice using `sched_latency / n`, respect `min_granularity`.
*   **Sleeping processes**:
    *   Adjust vruntime when a process wakes up to avoid CPU monopolization.
*   **Optional**:
    *   Use Red-Black tree or any sorted structure for efficiently picking next process.

**Goals**:
*   Decide how to track vruntime per process.
*   Simulate process sleep/wake cycles.
*   Test weighted fairness over time, including nice values and varying process lengths.

**Questions**:
*   How do I update vruntime when a process wakes up?
*   How do I handle multiple processes efficiently?
*   How will I simulate time and context switching without real OS interrupts?

## General Mentoring Guidelines

*   **Think first, code later**: Always write a plan and pseudo-steps before touching the keyboard.
*   **Start small, test often**: E.g., 3–5 processes, short run times. Verify fairness and correctness.
*   **Keep metrics**: Track completion time, fairness ratios, CPU share. Plot if you can.
*   **Document decisions**: Every design choice—data structure, time slice calculation, sleep handling—write why you chose it.
*   **Iterate and improve**: Start with Lottery → Stride → Full CFS.
