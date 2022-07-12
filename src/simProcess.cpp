#include <vector>

/**Process holds len CPU Burst times and len - 1 IO burst times.  It allows easy access to the CPU and IO burst time on "top" at current location
 * 
*/
class process
{
    //member variables
    // "static"
    std::vector<int> cpuTimes;
    std::vector<int> ioTimes;
    size_t len; /** Number of times stored in process.   */

    int cur; //current process tracker (iterator with no iteration)
public:
    //constructors
    process()
    {
        len = 0;
        cur = 0;
    }

    process(std::vector<int> cpuTimes, std::vector<int> ioTimes){
        //probably should ensure cpuTimes.len = ioTimes.len + 1;
        this->cpuTimes = cpuTimes;
        this->ioTimes = ioTimes;
        len = cpuTimes.size();
    }

    /** Returns current CPU burst time.  Returns -1 if cur is out of bounds  */
    int getCurCPU(){
        if (cur >= len) return -1;
        return cpuTimes[cur];
    }

    /** Returns current IO burst time.  Returns -1 if cur is out of bounds  */
    int getCurIO(){
        if (cur >= len - 1) return -1;
        return cpuTimes[cur];
    }

    void nextP(){
        cur++;
    }
};