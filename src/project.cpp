#include <iostream>
#include <cstdlib>

int main(int argc, int argv[]){
    //INPUT processing
    //sample input: a.out 8 101 0.001 16384 4 0.5 128 > output05-full.txt

    //general
    if (argc != 8){
        std::cerr << "ERROR: Invalid number of inputs. Expected 8 but recieved " << argc << std::endl;
        return 1;
    }

    //argv[1]: Define n as the number of processes to simulate. Process IDs are assigned in alphabetical order A through Z. Therefore, you will have at most 26 processes to simulate.
    //number of processes to simulate, 0 < n <= 26
    int n = argv[1];
    if (n < 0 || n > 26){
        std::cerr << "ERROR: Number of processes to simulate 'n' is of an invalid size: " << argc << std::endl;
        return 1;
    }
    

    //argv[2]: We will use a pseudo-random number generator to determine the interarrival times of CPU bursts. This command-line argument, i.e. seed, serves as the seed for the pseudo random number sequence. To ensure predictability and repeatability, use srand48() withthis given seed before simulating each scheduling algorithm and drand48() to obtain thenext value in the range [0.0, 1.0). For languages that do not have these functions, implementan equivalent 48-bit linear congruential generator, as described in the man page for thesfunctions in C.1
    int randomSeed = argv[2];
    //TODO: Implement random

    //argv[3]: To determine interarrival times, we will use an exponential distribution; therefore,this command-line argument is parameter λ. Remember that 1λ will be the average randomvalue generated, e.g., if λ = 0.01, then the average should be appoximately 100. See theexp-random.c example; and use the formula shown in the code, i.e., -log( r ) / lambda,where log is the natural logarithm.
    double lambda = argv[3]; //average of random values can be calculated by 1/lambda

    //argv[4]: For the exponential distribution, this command-line argument represents the upper bound for valid pseudo-random numbers. This threshold is used to avoid values far down thelong tail of the exponential distribution. As an example, if this is set to 3000, all generatedvalues above 3000 should be skipped. For cases in which this value is used in the ceilingfunction (see the next page), be sure the ceiling is still valid according to this upper bound.
    double randomMax = argv[4]; //maximum value of valid random numbers in the distribution
    //TODO: make sure randomMax is the same variable type as random numbers

    //argv[5]: Define tcs as the time, in milliseconds, that it takes to perform a context switch.Remember that a context switch occurs each time a process leaves the CPU and is replacedby another process. More specifically, the first half of the context switch time (i.e., tcs2) isthe time required to remove the given process from the CPU; the second half of the contextswitch time is the time required to bring the next process in to use the CPU. Therefore,expect tcs to be a positive even integer.
    int csTime = argv[5]; //milliseconds to perfrom a context switch

    //argv[6]: For the SJF and SRT algorithms, since we cannot know the actual CPU bursttimes beforehand, we will rely on estimates determined via exponential averaging. As such,this command-line argument is the constant α. Note that the initial guess for each processis τ0 =1λ. When calculating τ values, use the “ceiling” function for all calculations.
    double alpha = argv[6]; //parameter for SRT and SJF CPU burst times

    //argv[7]: For the RR algorithm, define the time slice value, tslice, measured in milliseconds.
    int timeSlice = argv[7]; //time slice value for RR algorithm

    //DATA

    //TODO: Random numbers????


    //OUTPUT
    // Format: Process <A>: arrival time <76>ms; tau <1000>ms; <9001> CPU bursts:
    // Format: --> CPU burst <387>ms --> I/O burst <1190>ms

    // Format: time <t>ms: <event-details> [Q <queue-contents>]
    // Example: time 51476ms: Process B (tau 26ms) started using the CPU for 3ms burst [Q: empty]

}