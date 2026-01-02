#include <iostream>
#include <vector>
#include <algorithm> // For std::min

using namespace std;

typedef enum{
    READY, RUNNING, FINISHED
} status;

typedef struct {
    int Id;
    int arrival_time = 0;
    int duration = 0;
    int remaining = 0;
    int completion_time = 0;
    int first_run_time = -1; // -1 means "Never ran before"
    status job_status;
} jobs;

// Helper: Generate Workload
vector<jobs> generate_workload() {
    vector<jobs> workload;
    int num_jobs = 5; // Reduced to 5 for easier reading

    for (int i = 0; i < num_jobs; ++i) {
        jobs newJob;
        newJob.Id = i + 1;
        newJob.arrival_time = 0;
        newJob.duration = (num_jobs - i) * 10; // 50, 40, 30, 20, 10
        newJob.remaining = newJob.duration;
        newJob.job_status = READY;
        newJob.first_run_time = -1; // Important init
        workload.push_back(newJob);
    }
    return workload;
}

void RR() {
    cout << "========================================\n";
    cout << "TEST: Round Robin (Time Slice = 2)\n";
    cout << "========================================\n";

    vector<jobs> tasks = generate_workload();
    int current_time = 0;
    int completed_jobs = 0;
    int time_quantum = 2; // Strict time limit (Slice)
    int idx = 0; // The Circular Index

    while (completed_jobs < tasks.size()) {
        // 1. Get pointer to current job
        jobs* job = &tasks[idx];

        // 2. CHECK: Is this job already done?
        if (job->job_status == FINISHED) {
            // Skip it and move to next
            idx = (idx + 1) % tasks.size();
            continue;
        }

        // 3. Logic: First Run Check (Response Time)
        if (job->first_run_time == -1) {
            job->first_run_time = current_time;
            cout << ">>> Time " << current_time << ": Job " << job->Id << " started (First Run)\n";
        }

        // 4. Logic: How long do we run?
        // We run for the Quantum OR the Remaining Time, whichever is SMALLER.
        // If remaining is 1 and quantum is 2, we only run for 1.
        int run_time = min(time_quantum, job->remaining);

        // Execute
        job->remaining -= run_time;
        current_time += run_time;

        // 5. Check Completion
        if (job->remaining == 0) {
            job->job_status = FINISHED;
            job->completion_time = current_time;
            completed_jobs++;
            cout << ">>> Time " << current_time << ": Job " << job->Id << " Finished!\n";
        }

        // 6. Move to next job (Round Robin style)
        idx = (idx + 1) % tasks.size();
    }

    // --- Metrics ---
    cout << "\n--- Final Metrics ---\n";
    double total_turnaround = 0;
    double total_response = 0;

    for (int i = 0; i < tasks.size(); ++i) {
        int turnaround = tasks[i].completion_time - tasks[i].arrival_time;
        int response = tasks[i].first_run_time - tasks[i].arrival_time;

        total_turnaround += turnaround;
        total_response += response;

        cout << "Job " << tasks[i].Id
             << ": Turnaround = " << turnaround
             << ", Response = " << response << " ticks\n";
    }

    cout << "--------------------------------\n";
    cout << "Avg Turnaround = " << total_turnaround / tasks.size() << " ticks (Likely Bad)\n";
    cout << "Avg Response   = " << total_response / tasks.size() << " ticks (Should be Good!)\n";
    cout << "--------------------------------\n";
}

int main() {
    RR();
    return 0;
}