#ifndef PROCESS_H
#define PROCESS_H
/**Process holds len CPU Burst times and len - 1 IO burst times.  It allows easy access to the CPU and IO burst time on "top" at current location
*/
class Process
{
private:
    // member variables
    //  "static"
    std::vector<int> cpuTimes;
    std::vector<int> ioTimes;
    size_t len; /** Number of times stored in process.   */
    int arrivalTime;
    int tau;
    //dynamic
    int cur; // current process tracker (iterator with no iteration)
public:
    // constructors
    Process();
    Process(int arrivalTime, int tau, int burstCount);
    Process(std::vector<int> cpuTimes, std::vector<int> ioTimes);
    
    int getCPU(int index);
    int getIO(int index);
    int getCurCPU();
    int getCurIO();

    void nextP();

    void addTimes(int CPUBurstTime, int IOBurstTime);

    void addTime(int CPUBurstTime);
};

#endif