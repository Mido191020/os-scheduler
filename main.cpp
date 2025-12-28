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
    int intial_value=0;
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
    int x=0;
    while (completed_jobs<10){
        //how I can swap between them
        //the idea is -> we will do the smae each time condation ?
        jobs current_job=tasks[x++];
        for (int i = 0; i < 10&&current_job.job_status!=FINISHED; ++i) {
            if (current_job.duration==0){
                current_job.completion_time=current_job.completion_time+current_time;
                current_job.job_status=FINISHED;
                completed_jobs++;
            }
        }
        if (x>=10)
            x=0;
    }
    cout<<"done RR\n";
}
int main() {
RR();
}