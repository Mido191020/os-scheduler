#include <iostream>
#include <queue>
#include <vector>
using namespace std;
typedef enum{
    READY, RUNNING, FINISHED
}status;
typedef struct {
   int Id;
   int arrival_time=0;
   int duration=0;
   int remaining=0;
   int completion_time;
    status job_status;
}jobs;

jobs* get_next_job_FIFO(vector<jobs>&FIFO, int current_time){
    for (int i = 0; i < FIFO.size(); ++i) {
        if (FIFO[i].job_status==READY&&FIFO[i].arrival_time<=current_time){
            return &FIFO[i];
        }
    }
    return NULL;
}
jobs *get_next_job_sjf(vector<jobs>&FIFO,int current_time){
    jobs *selected_job = NULL; // Initialize to NULL
    int min_duration=INT_MAX;

    for (int i = 0; i < FIFO.size(); ++i) {
        if (FIFO[i].job_status==READY&&FIFO[i].arrival_time<=current_time){
            if (FIFO[i].duration<=min_duration){
                min_duration=FIFO[i].duration;
                selected_job=&FIFO[i];
            }
        }
    }
    return selected_job;

}








vector<jobs> generate_workload(){
    vector<jobs> workload;
    int num_jobs = 10;

    for (int i = 0; i < num_jobs; ++i) {
        jobs newJob;
        newJob.Id = i + 1;
        newJob.arrival_time = 0;
        newJob.duration = (num_jobs - i) * 10;

        newJob.remaining = newJob.duration;
        newJob.job_status = READY;
        workload.push_back(newJob);
    }
    return workload;
}
void run_simulation(vector<jobs> workload, jobs* (*policy)(vector<jobs>&, int)) {

    int current_time = 0;
    int completed_jobs = 0;

    // Simulation Loop
    while (completed_jobs < workload.size()) {
        // Ask the injected policy: "Who should run now?"
        jobs* current_job = policy(workload, current_time);

        if (current_job != NULL) {
            // CPU is busy
            // Uncomment next line if you want to see tick-by-tick details
            // cout << "Time " << current_time << ": Running Job " << current_job->Id << endl;

            current_job->remaining--;

            if (current_job->remaining == 0) {
                current_job->job_status = FINISHED;
                current_job->completion_time = current_time + 1;
                completed_jobs++;
                cout << "Time " << current_time + 1 << ": Job " << current_job->Id << " Finished!" << endl;
            }
        } else {
            // CPU is idle
            cout << "Time " << current_time << ": IDLE" << endl;
        }
        current_time++;
    }

    // Metrics Calculation
    cout << "\n--- Final Metrics ---\n";
    double total_turnaround = 0;
    for (int i = 0; i < workload.size(); ++i) {
        int turnaround = workload[i].completion_time - workload[i].arrival_time;
        total_turnaround += turnaround;
        cout << "Job " << workload[i].Id << ": Turnaround = " << turnaround << " ticks\n";
    }

    double avg_turnaround = total_turnaround / workload.size();
    cout << "--------------------------------\n";
    cout << "Average Turnaround Time = " << avg_turnaround << " ticks\n";
    cout << "--------------------------------\n\n";
}

void TEST_FIFO() {
    cout << "========================================\n";
    cout << "TEST 1: FIFO Strategy (Suffers Convoy Effect)\n";
    cout << "========================================\n";

vector<jobs >data=generate_workload();
    run_simulation(data,get_next_job_FIFO);
}
void TEST_SJF() {
    cout << "========================================\n";
    cout << "TEST 2: SJF Strategy (Solves Convoy Effect)\n";
    cout << "========================================\n";

    // 1. Get Fresh Data (Same initial conditions)
    vector<jobs> data = generate_workload();

    // 2. Run Simulation with SJF Policy
    run_simulation(data, get_next_job_sjf);
}
vector<jobs> generate_late_workload() {
    vector<jobs> workload;

    // Job 1: Arrives 0, Duration 100 (The Monster)
    jobs j1; j1.Id=1; j1.arrival_time=0; j1.duration=100; j1.remaining=100; j1.job_status=READY;
    workload.push_back(j1);

    // Job 2: Arrives 10, Duration 10 (The Mouse)
    jobs j2; j2.Id=2; j2.arrival_time=10; j2.duration=10; j2.remaining=10; j2.job_status=READY;
    workload.push_back(j2);

    return workload;
}

void TEST_LATE_ARRIVAL() {
    cout << "========================================\n";
    cout << "TEST 3: Late Arrival (SJF Failure Case)\n";
    cout << "========================================\n";

    vector<jobs> data = generate_late_workload();

    // We use SJF to prove it fails to preempt
    run_simulation(data, get_next_job_sjf);
}
int main() {
TEST_FIFO();
TEST_SJF();
TEST_LATE_ARRIVAL();

}
