#include <iostream>
#include <cstdlib>
#include <vector>
#include <random> // may not need this

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
int next_exp(double lambda, int randomSeed, int floor, int cieling);

int main(int argc, int argv[]){
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
    int n = argv[1];
    if (n < 0 || n > 26){
        std::cerr << "ERROR: Number of processes to simulate 'n' is of an invalid size: " << argc << std::endl;
        return 1;
    }
    

    //argv[2]: We will use a pseudo-random number generator to determine the interarrival times of CPU bursts. This command-line argument, i.e. seed, serves as the seed for the pseudo random number sequence. To ensure predictability and repeatability, use srand48() withthis given seed before simulating each scheduling algorithm and drand48() to obtain thenext value in the range [0.0, 1.0). For languages that do not have these functions, implementan equivalent 48-bit linear congruential generator, as described in the man page for thesfunctions in C.1
    int inputSeed = argv[2];
    //TODO: Implement random

    //argv[3]: To determine interarrival times, we will use an exponential distribution; therefore,this command-line argument is parameter λ. Remember that 1λ will be the average randomvalue generated, e.g., if λ = 0.01, then the average should be appoximately 100. See theexp-random.c example; and use the formula shown in the code, i.e., -log( r ) / lambda,where log is the natural logarithm.
    double lambda = argv[3]; //average of random values can be calculated by 1/lambda

    //argv[4]: For the exponential distribution, this command-line argument represents the upper bound for valid pseudo-random numbers. This threshold is used to avoid values far down thelong tail of the exponential distribution. As an example, if this is set to 3000, all generatedvalues above 3000 should be skipped. For cases in which this value is used in the ceilingfunction (see the next page), be sure the ceiling is still valid according to this upper bound.
    int randomMax = argv[4]; //maximum value of valid random numbers in the distribution
    //Double Check: Int is correct variable for randomMax

    //argv[5]: Define tcs as the time, in milliseconds, that it takes to perform a context switch.Remember that a context switch occurs each time a process leaves the CPU and is replacedby another process. More specifically, the first half of the context switch time (i.e., tcs2) isthe time required to remove the given process from the CPU; the second half of the contextswitch time is the time required to bring the next process in to use the CPU. Therefore,expect tcs to be a positive even integer.
    int csTime = argv[5]; //milliseconds to perfrom a context switch

    //argv[6]: For the SJF and SRT algorithms, since we cannot know the actual CPU bursttimes beforehand, we will rely on estimates determined via exponential averaging. As such,this command-line argument is the constant α. Note that the initial guess for each processis τ0 =1λ. When calculating τ values, use the “ceiling” function for all calculations.
    double alpha = argv[6]; //parameter for SRT and SJF CPU burst times

    //argv[7]: For the RR algorithm, define the time slice value, tslice, measured in milliseconds.
    int timeSlice = argv[7]; //time slice value for RR algorithm

    //TODO: #1 Data structure to store CPU and I/O burst times.  Store them in pairs?  the last cpu burst has no I/O burst

    //generate process times, which will be used for each simulation
    for (int p = 0; p < n; i++) // p represents process.  P = 0 --> A
    {
        int bCount = next_exp(lambda, inputSeed, 1, 100); //number of CPU bursts, a random integer between 1 and 100
        int arrTime = 0; //arrival time in milliseconds.  UNIMPLEMENTED.
        int tau = 0; //time in milliseconds.  UNIMPLEMENTED. XANDER: I don't know where this variable comes from, suspect Tcs
        std::cout << "Process " << p + 'A' << ": arrival time " << arrTime << "ms; tau "
            << tau << "ms; " << bCount << " CPU bursts:" << std::endl;
        //loop through bCount-1 bursts, doing last burst outside loop
        for (int i = 0; i < bCount; i++){
            int cpuTime = next_exp(lambda, inputSeed, 1, 100);
            int ioTime = next_exp(lambda, inputSeed, 1, 100);
            std::cout << "--> CPU burst " << cpuTime << "ms --> I/O burst " << ioTime << "ms" << std::endl;
        }
    }

    //loop through each algorithm
    //0 = FCFS, 1 = SJF, 2 = SRT, 3 = RR
    for (int alg = 0, alg < 4; alg++) //TODO: #2 Ienumerator for algorithm?
    {
        int time = 0;
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

int next_exp(double lambda, int randomSeed, int floor, int cieling){
    //NON-FUNCTIONAL

    //generate uniform distribution
    //project pdf identifies c function drand48
}

// adding basic set up for individual algorithms
void fcfs() {
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