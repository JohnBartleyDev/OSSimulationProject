#include "simProcess.h"

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <charconv>
#include <utility>
#include <bits/stdc++.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

/**
 * Generates an integer random number from an exponential distribution.
 * In context, this is used to generate the number of microseconds a process, such as a CPU burst and IO burst time
 * Xander: This doesn't change the seed that's fed into it to my knowledge, which would make every random integer the same.
 *  
 * @param lambda given by user, effects the random algorithm such that lambda^-1 = average random value generated
 * @param randomSeed the seed used to create a random number.  Re-using the seed will regenerate the same random values.
 * @param floor minimum, should be the initial process arrival time
 * @param cieling maximum, should be the number of cpu bursts for the given process
 * @return integer random number generated by the given parameters
 */
// int next_exp(double lambda, int randomSeed, int floor, int cieling){
//     return 3;
// }
int next_exp(double lambda, int cieling){
    double r = drand48();
    double x = -log(r)/lambda;
    if(x > cieling){
        x =next_exp(lambda, cieling);
    }
    return int(x);
    
    //NON-FUNCTIONAL
    /*To ensure predictability and repeatability, use srand48() with
this given seed before simulating each scheduling algorithm and drand48() to obtain the
next value in the range [0.0, 1.0). For languages that do not have these functions, implement
an equivalent 48-bit linear congruential generator, as described in the man page for these
functions in C.1 */

}
void fcfs(std::vector<Process> &processes, int contexttime); // first come first serve
void sjf(); // shortest job first
void srt(); // shortest remaining time
void rr(); // round robin

int main(int argc, char** argv){
    //INPUT processing
    //sample input: a.out 8 101 0.001 16384 4 0.5 128 > output05-full.txt

    //general
    if (argc != 8){
        std::cerr << "ERROR: Invalid number of inputs. Expected 8 but recieved " << argc << std::endl;
        return 1;
    }

    /**argv[1]: Define n as the number of processes to simulate. Process IDs are assigned in alphabetical order A through Z. Therefore, you will have at most 26 processes to simulate.
    * number of processes to simulate, 0 < n <= 26
    * */
    int n = std::stoi(argv[1]);
    if (n < 0 || n > 26){
        std::cerr << "ERROR: Number of processes to simulate 'n' is of an invalid size: " << argv[2] << std::endl;
        return 1;
    }
    

    //argv[2]: We will use a pseudo-random number generator to determine the interarrival times of CPU bursts. This command-line argument, i.e. seed, serves as the seed for the pseudo random number sequence. To ensure predictability and repeatability, use srand48() withthis given seed before simulating each scheduling algorithm and drand48() to obtain thenext value in the range [0.0, 1.0). For languages that do not have these functions, implementan equivalent 48-bit linear congruential generator, as described in the man page for thesfunctions in C.1
    int inputSeed = std::stoi(argv[2]);
    //TODO: Implement random
   
    //argv[3]: To determine interarrival times, we will use an exponential distribution; therefore,this command-line argument is parameter λ. Remember that 1λ will be the average randomvalue generated, e.g., if λ = 0.01, then the average should be appoximately 100. See theexp-random.c example; and use the formula shown in the code, i.e., -log( r ) / lambda,where log is the natural logarithm.
    double lambda = std::stod(argv[3]); //average of random values can be calculated by 1/lambda

    //argv[4]: For the exponential distribution, this command-line argument represents the upper bound for valid pseudo-random numbers. This threshold is used to avoid values far down thelong tail of the exponential distribution. As an example, if this is set to 3000, all generatedvalues above 3000 should be skipped. For cases in which this value is used in the ceilingfunction (see the next page), be sure the ceiling is still valid according to this upper bound.
    int randomMax = std::stoi(argv[4]); //maximum value of valid random numbers in the distribution
    //Double Check: Int is correct variable for randomMax

    //argv[5]: Define tcs as the time, in milliseconds, that it takes to perform a context switch.Remember that a context switch occurs each time a process leaves the CPU and is replacedby another process. More specifically, the first half of the context switch time (i.e., tcs2) isthe time required to remove the given process from the CPU; the second half of the contextswitch time is the time required to bring the next process in to use the CPU. Therefore,expect tcs to be a positive even integer.
    int csTime = std::stoi(argv[5]); //milliseconds to perfrom a context switch

    //argv[6]: For the SJF and SRT algorithms, since we cannot know the actual CPU bursttimes beforehand, we will rely on estimates determined via exponential averaging. As such,this command-line argument is the constant α. Note that the initial guess for each processis τ0 =1λ. When calculating τ values, use the “ceiling” function for all calculations.
    double alpha = std::stod(argv[6]); //parameter for SRT and SJF CPU burst times

    //argv[7]: For the RR algorithm, define the time slice value, tslice, measured in milliseconds.
    int timeSlice = std::stoi(argv[7]); //time slice value for RR algorithm

    //TODO: #1 Data structure to store CPU and I/O burst times.  Store them in pairs?  the last cpu burst has no I/O burst

    //generate process times, which will be used for each simulation
    //reseed(inputSeed);
     srand48(inputSeed);
    std::vector<Process> processes;
    for (int p = 0; p < n; p++) // p represents process.  P = 0 --> A
    {
        int arrTime = floor(next_exp(lambda, randomMax));
        
        int bCount =  1+drand48()*100;//next_uni(1, 100); //number of CPU bursts, a random integer between 1 and 100
        ;//next_uni(1, 200);; //arrival time in milliseconds.  UNIMPLEMENTED.
        int tau = 100; //time in milliseconds.  UNIMPLEMENTED. XANDER: I don't know where this variable comes from, suspect Tcs
        processes.push_back(Process(arrTime, tau, bCount, char(p+65)));
        std::cout << "Process " << p + 'A' << ": arrival time " << arrTime << "ms; tau "
            << tau << "ms; " << bCount << " CPU bursts:" << std::endl;
        //loop through bCount-1 bursts, doing last burst outside loop
        for (int i = 0; i < bCount-1; i++){
            int cpuTime = ceil(1+next_exp(lambda, randomMax));
           
            int ioTime =   10*ceil(1+next_exp(lambda, randomMax));
            processes.back().addTimes(cpuTime, ioTime);
            std::cout << "--> CPU burst " << cpuTime << "ms --> I/O burst " << ioTime << "ms" << std::endl;
        }
        int cpuTime = ceil(1+next_exp(lambda, randomMax));
        processes.back().addTime(cpuTime);
            std::cout << "--> CPU burst " << cpuTime << "ms "<< std::endl;

        
    }

    //loop through each algorithm
    //0 = FCFS, 1 = SJF, 2 = SRT, 3 = RR
    for (int alg = 0; alg < 4; alg++) //TODO: #2 Ienumerator for algorithm?
    {
        //reseed(inputSeed);
        int time = 0;
        std::string algorithm;
        switch (alg)
        {
        case 0:
            algorithm = "FCFS";
            fcfs(processes, csTime);
            break;
        case 1:
            algorithm = "SJF";
            break;
        case 2:
            algorithm = "SRT";
            break;
        case 3:
            algorithm = "RR";
            break;
        }
        //do algorithm
        std::cout << "time " << time << "ms: Simulator started for " << algorithm << " [Q: empty]" << std::endl;
        //while still jobs to do
            //pick next job
        std::cout << "time " << time << "ms: Simulator ended for " << algorithm << " [Q: empty]" << std::endl;
    }
    


    //OUTPUT
    // Format: Process <A>: arrival time <76>ms; tau <1000>ms; <9001> CPU bursts:
    // Format: --> CPU burst <387>ms --> I/O burst <1190>ms

    // Format: time <t>ms: <event-details> [Q <queue-contents>]
    // Example: time 51476ms: Process B (tau 26ms) started using the CPU for 3ms burst [Q: empty]

}

void reseed(int seed){
    std::srand(seed);
}

int next_uni(int floor, int cieling){
    int random = std::rand();
    int boundedRandom = random%(cieling-floor) + floor; //generate integer between cieling and floor from random
    return boundedRandom;
}



//comparator function for using find_if
bool compareProcess(Process &p1, char x)
{
    return (p1.getID() == x);
}

//sort function for the processes, where it is sorted by lowest time first
bool compareArrival(std::pair<int, char> p1, std::pair<int, char> p2){
    return (p1.first < p2.first);
}

// sort function based on burst time
bool compareBurst(Process &p1, Process &p2) {
    return (p1.getCurCPU() < p2.getCurCPU());
}

//adds an event to the event log and resorts it with newest events first
void addevent(std::vector<int>&events, int event){
    //maybe write own sorting function
    events.insert(events.end(), event);
    std::sort(events.begin(),events.end(), std::greater<int>());
}

//switches processes between the different vectors
void switchVector(std::vector<Process>& v1, std::vector<Process>& v2, char name)
{
  std::vector<Process>::iterator it =std::find_if(v1.begin(), v1.end(), std::bind(compareProcess, std::placeholders::_1, name));
  v2.push_back(*it);
  v1.erase(it);
}

//formats the readyqueue for output
std::string printQueue(std::vector<Process>& v1)
{
    std::string out = "";
    if (v1.size()== 0){
        out = out.append(" empty");
    }
    else{
        for(int i= 0; i<v1.size(); i++){
            out = out.append(" ");
            out +=v1[i].getID();
        }
    }
    out = out.append("]");
    return out;
}

// first come first serve
// adding basic set up for individual algorithms
// add variables as needed
void fcfs(std::vector<Process>& processes, int contexttime) {
    std::cout << "beginning of FCFS process " << std::endl;
    //variable declarations
    int currtime = 0;
    bool inprocess = true; //turns false when there are no processes in the ready, running, or waiting state 
    bool inuse =false;
    int n = processes.size(); //the amount of processes
    
    std::pair<int, char> wait[n];
    std::vector<Process> ioState; //process objects in ioState
    std::vector<Process> readyState; // Process objects in readyState do not reference the same objects as those in the processes argument, it is just a copy
    std::vector<Process> runState;//vector container for holding only one process to keep the same modification methods
    std::vector<Process>::iterator readyit;
    std::vector<Process>::iterator ioit;
    std::vector<int> eventlog;
    //sorts and creates order for initial ready queue for processes
    std::pair<int, char> arrivalarr[n];
    
    
    for(int i = 0; i< n; i++){
        arrivalarr[i].first=processes[i].getArrival();
        arrivalarr[i].second=processes[i].getID();
    }
    std::sort(arrivalarr, arrivalarr+n, compareArrival);
    addevent(eventlog, arrivalarr[0].first);
    //uses sorted arrival time to begin ready state
    int startsreached =0;
     std::cout << "beginning of FCFS process " << std::endl;
        while(inprocess){
            if(startsreached < n){
                if(currtime >= arrivalarr[startsreached].first){
                    ioit =std::find_if(processes.begin(), processes.end(), std::bind(compareProcess, std::placeholders::_1, arrivalarr[startsreached].second));
                    readyState.push_back(*ioit);
                    startsreached +=1;
                    
                    std::cout<<"time "<<currtime<<"ms: Process "<<readyState[0].getID()<<" arrived; added to ready queue [Q:"<<printQueue(readyState)<<std::endl;
                    
                     
                     continue;

                }
            }
           
           if (inuse == false){
                if(readyState.size()!=0){
                    
                    currtime += contexttime/2;
                    std::cout<<"time "<<currtime<<"ms: Process "<<readyState[0].getID()<<" started using the CPU for "<<readyState[0].getCurCPU()<<"ms burst [Q:"<<printQueue(readyState)<<std::endl;
                    switchVector(readyState, runState, readyState[0].getID());
                    
                
                    
                    
                    
                    inuse= true;
                    
                   
                    runState[0].addIOevent(runState[0].getCurCPU()+currtime);
                    continue;
                }
            }
            
            if(inuse == true) {
                if(currtime >= runState[0].getNextIO()){
                    
                    
                    if(runState[0].getLen()-runState[0].getCur() <=1){
                        std::cout<<"time "<<currtime<<"ms: Process "<<runState[0].getID()<<" Terminated [Q:"<<printQueue(readyState)<<std::endl;
                        runState.erase(runState.begin());
                        inuse = false;
                        currtime +=contexttime/2;
                        continue;
                    }
                    std::cout<<"time "<<currtime<<"ms: Process "<<runState[0].getID()<<" completed a CPU burst; "<<runState[0].getLen()-runState[0].getCur()-1 <<"bursts to go "<<runState[0].getCurCPU()<<"ms burst [Q:"<<printQueue(readyState)<<std::endl;
                    currtime += contexttime/2;
                    
                    runState[0].addIOevent(runState[0].getCurIO()+currtime);
                    
                    runState[0].nextP();
                    switchVector(runState, ioState, runState[0].getID());
                    
                    
                    inuse = false;
                    
                    continue;
                }
            }
            if(ioState.size()!= 0){
                for (int i = 0; i< ioState.size(); i++){
                    if(currtime >= ioState[i].getNextIO()){
                        switchVector(ioState, readyState, ioState[i].getID());
                        std::cout<<"time "<<currtime<<"ms: Process "<<readyState[readyState.size()-1].getID()<<" completed I/O; added to ready queue [Q:"<<printQueue(readyState)<<std::endl;
                       
                        goto cnt;
                    }
                }
                
            }
            
            if(ioState.size()==0 && readyState.size()==0 && runState.size()==0 &&startsreached ==n){
                 std::cout << "currtime is  "<<currtime<<" at end of progrma" << std::endl;
                inprocess =false;
                continue;
            }
          
            
            currtime+=1;
            cnt:;
    }
    /*
    Basic Algorithm:
    Step 1 : Input the number of processes required to be scheduled using FCFS, burst time for each process and its arrival time.
    Step 2 : Using enhanced bubble sort technique, sort the all given processes in ascending order according to arrival time in a ready queue.
    Step 3 : Calculate the Finish Time, Turn Around Time and Waiting Time for each process which in turn help to calculate Average Waiting Time and Average Turn Around Time required by CPU to schedule given set of process using FCFS.
        Step 3.1 : for i = 0, Finish Time T 0 = Arrival Time T 0 + Burst Time T 0
        Step 3.2 : for i >= 1, Finish Time T i = Burst Time T i + Finish Time T i - 1
        Step 3.3 : for i = 0, Turn Around Time T 0 = Finish Time T 0 - Arrival Time T 0
        Step 3.4 : for i >= 1, Turn Around Time T i = Finish Time T i - Arrival Time T i
        Step 3.5 : for i = 0, Waiting Time T 0 = Turn Around Time T 0 - Burst Time T 0
        Step 3.6 : for i >= 1, Waiting Time T i = Turn Around Time T i - Burst Time T i - 1
    Step 4 : Process with less arrival time comes first and gets scheduled first by the CPU.
    Step 5 : Calculate the Average Waiting Time and Average Turn Around Time.
    Step 6 : Stop.
    https://iq.opengenus.org/first-come-first-serve-cpu-scheduling/#:~:text=First%20Come%20First%20Serve%20(FCFS,executed%20fully%20by%20the%20CPU.
    */
}

// shortest job first
// adding basic set up for individual algorithms
// add variables as needed
void sjf() {
    /*
    Step 1 : Sort all the processes according to the arrival time. 
    Step 2 : Then select that process that has minimum arrival time and minimum Burst time. 
    Step 3 : After completion of the process make a pool of processes that arrives afterward till the completion 
    of the previous process and select that process among the pool which is having minimum Burst time. 
        Completion Time = Start Time + Burst Time
        Turn Around Time = Completion Time – Arrival Time
        Waiting Time = Turn Around Time – Burst Time
    https://www.geeksforgeeks.org/program-for-shortest-job-first-or-sjf-cpu-scheduling-set-1-non-preemptive/
    */
}

// shortest remaining time
// adding basic set up for individual algorithms
// add variables as needed
void srt() {
    /*
    Step 1 : Traverse until all process gets completely executed.
        Step 1.1 : Find process with minimum remaining time at every single time lap.
        Step 1.2 : Reduce its time by 1.
        Step 1.3 : Check if its remaining time becomes 0 
        Step 1.4 : Increment the counter of process completion.
        Step 1.5 : Completion time of current process = current_time + 1;
        Step 1.6 : Calculate waiting time for each completed process.
            Step 1.61 : wt[i]= Completion time – arrival_time-burst_time
        Step 1.7 : Increment time lap by one.
    Step 2 : Find turnaround time (waiting_time + burst_time).
    https://www.geeksforgeeks.org/shortest-remaining-time-first-preemptive-sjf-scheduling-algorithm/
    */
}

// round robin
// adding basic set up for individual algorithms
// add variables as needed
void rr() {
    /*


    Completion Time: Time at which process completes its execution.
    Turn Around Time: Time Difference between completion time and arrival time. Turn Around Time = Completion Time – Arrival Time
    Waiting Time(W.T): Time Difference between turn around time and burst time. 
    Waiting Time = Turn Around Time – Burst Time
    https://www.geeksforgeeks.org/program-round-robin-scheduling-set-1/
    */
}