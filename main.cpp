#include <iostream>
#include <queue>
#include <vector>
#include <climits>

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
    jobs *selected_job = NULL;
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

jobs *get_next_job_STCF(vector<jobs>&FIFO,int current_time){
    jobs *selected_job = NULL;
    int min_remaining=INT_MAX;

    for (int i = 0; i < FIFO.size(); ++i) {
        if (FIFO[i].job_status==READY&&FIFO[i].arrival_time<=current_time){
            if (FIFO[i].remaining <= min_remaining){
                min_remaining=FIFO[i].remaining ;
                selected_job=&FIFO[i];
            }
        }
    }
    return selected_job;
}

void run_simulation(vector<jobs> workload, jobs* (*policy)(vector<jobs>&, int)) {
    int current_time = 0;
    int completed_jobs = 0;
    int last_running_job_id = -1;

    while (completed_jobs < workload.size()) {
        jobs* current_job = policy(workload, current_time);

        if (current_job != NULL) {
            if (current_job->Id != last_running_job_id) {
                if (last_running_job_id != -1) {
                    cout << ">>> Time " << current_time << ": Context Switch! (Job "
                         << last_running_job_id << " stopped -> Job " << current_job->Id << " started)\n";
                } else {
                    cout << ">>> Time " << current_time << ": Job " << current_job->Id << " started.\n";
                }
                last_running_job_id = current_job->Id;
            }

            current_job->remaining--;

            if (current_job->remaining == 0) {
                current_job->job_status = FINISHED;
                current_job->completion_time = current_time + 1;
                completed_jobs++;
                cout << ">>> Time " << current_time + 1 << ": Job " << current_job->Id << " Finished!\n";
                last_running_job_id = -1;
            }
        } else {
            if (last_running_job_id != -1) cout << ">>> Time " << current_time << ": CPU Idle.\n";
            last_running_job_id = -1;
        }
        current_time++;
    }

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

vector<jobs> generate_late_workload() {
    vector<jobs> workload;
    jobs j1; j1.Id=1; j1.arrival_time=0; j1.duration=100; j1.remaining=100; j1.job_status=READY;
    workload.push_back(j1);
    jobs j2; j2.Id=2; j2.arrival_time=10; j2.duration=10; j2.remaining=10; j2.job_status=READY;
    workload.push_back(j2);
    return workload;
}

vector<jobs> generate_trap_workload() {
    vector<jobs> workload;
    jobs j1; j1.Id=1; j1.arrival_time=0; j1.duration=100; j1.remaining=100; j1.job_status=READY;
    workload.push_back(j1);
    jobs j2; j2.Id=2; j2.arrival_time=90; j2.duration=20; j2.remaining=20; j2.job_status=READY;
    workload.push_back(j2);
    return workload;
}

void TEST_FIFO() {
    cout << "========================================\n";
    cout << "TEST 1: FIFO Strategy\n";
    cout << "========================================\n";
    vector<jobs >data=generate_workload();
    run_simulation(data,get_next_job_FIFO);
}

void TEST_SJF() {
    cout << "========================================\n";
    cout << "TEST 2: SJF Strategy\n";
    cout << "========================================\n";
    vector<jobs> data = generate_workload();
    run_simulation(data, get_next_job_sjf);
}

void TEST_STCF() {
    cout << "========================================\n";
    cout << "TEST 3: STCF Strategy\n";
    cout << "========================================\n";
    vector<jobs> data = generate_workload();
    run_simulation(data, get_next_job_STCF);
}

void TEST_LATE_ARRIVAL() {
    cout << "========================================\n";
    cout << "TEST 3: Late Arrival (SJF Failure Case)\n";
    cout << "========================================\n";
    vector<jobs> data = generate_late_workload();
    run_simulation(data, get_next_job_sjf);
}

void TEST_LATE_ARRIVAL2() {
    cout << "========================================\n";
    cout << "TEST 4: Late Arrival (STCF Failure Case)\n";
    cout << "========================================\n";
    vector<jobs> data = generate_late_workload();
    run_simulation(data, get_next_job_STCF);
}

void TEST_TRAP_SJF() {
    cout << "========================================\n";
    cout << "TEST 5: Trap Scenario (Running with SJF)\n";
    cout << "EXPECTATION: Bad behavior (Preempts Job 1 near the end)\n";
    cout << "========================================\n";
    vector<jobs> data = generate_trap_workload();
    run_simulation(data, get_next_job_sjf);
}

void TEST_TRAP_STCF() {
    cout << "========================================\n";
    cout << "TEST 6: Trap Scenario (Running with STCF)\n";
    cout << "EXPECTATION: Good behavior (Finishes Job 1 first)\n";
    cout << "========================================\n";
    vector<jobs> data = generate_trap_workload();
    run_simulation(data, get_next_job_STCF);
}

int main() {
    TEST_TRAP_SJF();
    TEST_TRAP_STCF();
    return 0;
}