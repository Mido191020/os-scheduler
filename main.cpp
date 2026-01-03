#include <iostream>
#include <queue>
#include <vector>
#include <climits>

using namespace std;

typedef enum{
    READY, RUNNING, FINISHED
}status;
//RR
//time slice between process
//
typedef struct {
    int Id;
    int arrival_time=0;
    int duration=0;
    int remaining=0;
    int completion_time=0;
    int first_run_time = -1; // -1 means "Never touched the CPU"
    status job_status;
}jobs;
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
void RR(){
    vector<jobs >tasks=generate_workload();
    int current_time=0;
    int completed_jobs=0;
    int time_quantum = 2;
    int x=0;
    while (completed_jobs<tasks.size()){
        //how I can swap between them
        //the idea is -> we will do the smae each time condation ?
        jobs *current_job=&tasks[x];
        if (current_job->job_status==FINISHED){
            x=(x+1)%tasks.size();
            continue;
        }
        int min_time= min(time_quantum,current_job->remaining);
        for (int i = 0; i < min_time; ++i) {

            if (current_job->first_run_time==-1)current_job->first_run_time=current_time;

            current_job->remaining--;
            current_time++;

            cout << "Time " << current_time << " : Job " << current_job->Id
                 << " running. Remaining: " << current_job->remaining << endl;

            if (current_job->remaining==0){
                current_job->completion_time=current_job->completion_time+current_time;
                current_job->job_status=FINISHED;
                completed_jobs++;
                break;
            }
            

        }
        x = (x + 1) % tasks.size();
    }
    cout<<"done RR\n";

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
    cout << "Avg Turnaround = " << total_turnaround / tasks.size() << " ticks\n";
    cout << "Avg Response   = " << total_response / tasks.size() << " ticks (This should be low!)\n";
    cout << "--------------------------------\n";
}
int main() {
    RR();
}
