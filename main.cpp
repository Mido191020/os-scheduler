#include <iostream>
#include <queue>
#include <vector>
#include <cstdlib> // for rand()
#include <ctime>   // for time()

using namespace std;

// 1. Define the State
typedef enum { READY, RUNNING, FINISHED } status;

typedef struct {
    int Id;
    int tickets;             // The "share" of the CPU
    int duration;            // Total time needed
    int remaining;           // Time left to run
    int first_run_time = -1; // Stats
    int completion_time = 0; // Stats
} Job;

// 2. Setup the World (Policy)
vector<Job> setup_workload() {
    vector<Job> workload;

    // Example: 3 Jobs with different Ticket counts
    // Job A: Short but high priority (100 tickets)
    workload.push_back({1, 100, 5, 5});

    // Job B: Long and low priority (50 tickets)
    workload.push_back({2, 50, 20, 20});

    // Job C: Medium (10 tickets)
    workload.push_back({3, 10, 10, 10});

    return workload;
}

// 3. The Lottery Mechanism (YOUR TASK)
void run_scheduler(vector<Job>& run_queue) {
    int time_slice = 1; // The "Quantum"
    int current_time = 0;

    srand(time(0)); // Seed random number generator

    // Loop until all jobs are finished (remaining == 0)
    while (true) {

        // CHECK: Are all jobs done? If yes, break.
        bool all_done = true;
        int total_tickets = 0;

        // TODO: Loop to calculate total_tickets of ACTIVE jobs only
        // (Don't count finished jobs!)

        if (total_tickets == 0) break; // Everyone is done

        // TODO: 1. Pick a random number (winner) between 0 and total_tickets-1

        // TODO: 2. Find the winner using the subtraction/accumulation loop

        // TODO: 3. "Run" the winner:
        //      - Print "Time X: Job Y won"
        //      - Decrement winner.remaining by time_slice
        //      - Update first_run_time if it's -1
        //      - Update current_time

        // TODO: 4. Check if winner finished (remaining <= 0)
    }
}
int main() {
    vector<Job> queue = setup_workload();
    run_scheduler(queue);
    return 0;
}
