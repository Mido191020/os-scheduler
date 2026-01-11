#include <iostream>
#include <vector>
#include <cstdlib> // for rand()
#include <ctime>   // for time()
#include <algorithm> // for min

using namespace std;

// 1. Define the State
typedef enum { READY, RUNNING, FINISHED } status;

typedef struct {
    int Id;
    int tickets;             // The "share" of the CPU
    int duration;            // Total time needed
    int remaining;           // Time left to run
    int first_run_time = -1; // Stats: when it first got the CPU
    int completion_time = 0; // Stats: when it finished
    int arrival_time = 0;    // Stats: when it arrived (0 for now)
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

// 3. The Lottery Mechanism
void run_scheduler(vector<Job>& run_queue) {
    int time_slice = 1; // The "Quantum"
    int current_time = 0;
    int completed_jobs = 0;

    srand(time(0)); // Seed random number generator

    // Loop until all jobs are finished
    while (completed_jobs < (int)run_queue.size()) {
        
        int total_tickets = 0;
        // 0. Calculate total_tickets of ACTIVE jobs only
        for (const auto& job : run_queue) {
            if (job.remaining > 0) {
                total_tickets += job.tickets;
            }
        }
        
        if (total_tickets == 0) {
            break; 
        }

        // 1. Pick a random number (winner) between 0 and total_tickets-1
        int winning_ticket = rand() % total_tickets;
        
        // 2. Find the winner using the subtraction/accumulation loop
        int counter = 0;
        Job* winner = nullptr;
        
        for (auto& job : run_queue) {
            if (job.remaining > 0) {
                counter += job.tickets;
                if (counter > winning_ticket) {
                    winner = &job;
                    break;
                }
            }
        }
        
        if (winner) {
            // 3. "Run" the winner:
            if (winner->first_run_time == -1) {
                winner->first_run_time = current_time;
            }
            
            // For lottery scheduling, each win usually runs for 1 quantum (time_slice)
            int run_duration = min(time_slice, winner->remaining);
            winner->remaining -= run_duration;
            current_time += run_duration;

            cout << "Time " << current_time << ": Job " << winner->Id << " won (Ticket " << winning_ticket << ")" << endl;

            // 4. Check if winner finished
            if (winner->remaining <= 0) {
                winner->completion_time = current_time;
                completed_jobs++;
            }
        }
    }

    // --- Final Reporting ---
    double total_turnaround = 0;
    double total_response = 0;

    cout << "\n--- Final Statistics ---\n";
    for (const auto& job : run_queue) {
        int turnaround = job.completion_time - job.arrival_time;
        int response = job.first_run_time - job.arrival_time;
        total_turnaround += turnaround;
        total_response += response;

        cout << "Job " << job.Id << ": Turnaround = " << turnaround 
             << ", Response = " << response << endl;
    }

    cout << "--------------------------------\n";
    cout << "Avg Turnaround = " << total_turnaround / run_queue.size() << " ticks\n";
    cout << "Avg Response   = " << total_response / run_queue.size() << " ticks\n";
    cout << "--------------------------------\n";
}

int main() {
    vector<Job> queue = setup_workload();
    run_scheduler(queue);
    return 0;
}
