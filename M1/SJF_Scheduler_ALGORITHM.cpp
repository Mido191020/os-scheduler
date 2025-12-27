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
   int remaining;
   int completion_time;
    status job_status;
}jobs;

jobs* get_next_job(vector<jobs>&FIFO, int current_time){
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
void TEST1(){
    vector<jobs>job;

    for (int i = 3; i > 0; --i) {
        jobs newJob;
        newJob.Id = i + 1;
        newJob.arrival_time = 0;
        newJob.duration = (i) * 10;
        newJob.remaining = newJob.duration;
        newJob.job_status = READY;

        job.push_back(newJob);
    }

    cout<<"\t TEST1 \n";

    int completed_jobs=0;
    int current_time=0;
    while (completed_jobs < 3){
        jobs *x= get_next_job_sjf(job,current_time);
        if (x != NULL) {
            cout << "Time " << current_time << ": Running Job " << x->Id << endl;

            x->remaining--;

            if (x->remaining == 0) {
                x->job_status = FINISHED;
                x->completion_time = current_time + 1;
                cout << "Job " << x->Id << " Finished!" << endl;
                completed_jobs++;
            }
        }


        else{
            cout<<"Time X IDEL";
        }
        current_time++;
    }
    cout << "\n--- Final Metrics ---\n";

    double total_turnaround = 0;

    for (int i = 0; i < job.size(); ++i) {
        int turnaround = job[i].completion_time - job[i].arrival_time;
        total_turnaround += turnaround;

        cout << "Job " << job[i].Id
             << ": Turnaround Time = " << turnaround
             << " ticks (Finish: " << job[i].completion_time
             << " - Arrival: " << job[i].arrival_time << ")\n";
    }

    double average_turnaround = total_turnaround / job.size();
    cout << "--------------------------------\n";
    cout << "Average Turnaround Time = " << average_turnaround << " ticks\n";
    cout << "--------------------------------\n";


}
void TEST2(){
    vector<jobs>job;
   // vector<jobs>job2;
    for (int i = 0; i <3; ++i) {
        jobs newJob;
        newJob.Id = i + 1;
        newJob.arrival_time = 0;
        newJob.duration = (i + 1) * 10;
        newJob.remaining = newJob.duration;
        newJob.job_status = READY;

        job.push_back(newJob);
    }

    cout<<"\t TEST2 \n";
    int completed_jobs=0;
    int current_time=0;
    while (completed_jobs < 3){
        jobs *x= get_next_job_sjf(job,current_time);
        if (x != NULL) {
            cout << "Time " << current_time << ": Running Job " << x->Id << endl;

            x->remaining--;

            if (x->remaining == 0) {
                x->job_status = FINISHED;
                x->completion_time = current_time + 1;
                cout << "Job " << x->Id << " Finished!" << endl;
                completed_jobs++;
            }
        }


        else{
            cout<<"Time X IDEL";
        }
        current_time++;
    }
    cout << "\n--- Final Metrics ---\n";

    double total_turnaround = 0;

    for (int i = 0; i < job.size(); ++i) {
        int turnaround = job[i].completion_time - job[i].arrival_time;
        total_turnaround += turnaround;

        cout << "Job " << job[i].Id
             << ": Turnaround Time = " << turnaround
             << " ticks (Finish: " << job[i].completion_time
             << " - Arrival: " << job[i].arrival_time << ")\n";
    }

    double average_turnaround = total_turnaround / job.size();
    cout << "--------------------------------\n";
    cout << "Average Turnaround Time = " << average_turnaround << " ticks\n";
    cout << "--------------------------------\n";


}

int main() {
TEST1();
TEST2();

}
