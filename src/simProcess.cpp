
#include "simProcess.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <math.h>

// constructors
Process::Process()
{
    len = 0;
    cur = 0;
    arrivalTime =0;
    tau =0;
}

Process::Process(int arrivalTime, int tau, int burstCount, char ident, double alpha){
    this->arrivalTime = arrivalTime;
    this->tau = tau;
    this->ident = ident;
    this-> alpha = alpha;
    cur = 0;
    totalburst = 0;
    len = burstCount;
    nextio =0;
    waits = 1;
    waittime = arrivalTime; 
}

Process::Process(std::vector<int> cpuTimes, std::vector<int> ioTimes)
{
    // probably should ensure cpuTimes.len = ioTimes.len + 1;
    this->cpuTimes = cpuTimes;
    this->ioTimes = ioTimes;
    len = cpuTimes.size();
}

/** Returns CPU burst time at index.  Returns -1 if index is out of bounds  */
int Process::getCPU(int index)
{
    if (index >= int(len))
        return -1;
    return cpuTimes[index];
}

/** Returns IO burst time at index.  Returns -1 if index is out of bounds  */
int Process::getIO(int index)
{
    if (index >= int(len) - 1)
        return -1;
    return cpuTimes[index];
}

/**Returns processes arrival time */
int Process::getArrival(){
    return arrivalTime;
}
// process can be used like a stack using these functions
/** Returns current CPU burst time.  Returns -1 if cur is out of bounds  */
int Process::getCurCPU()
{
    if (cur >= int(len))
        return -2;
    return cpuTimes[cur];
}

/** Returns current IO burst time.  Returns -1 if cur is out of bounds  */
int Process::getCurIO()
{
    if (cur >= int(len) - 1)
        return -1;
    return ioTimes[cur];
}

//returns len
int Process::getLen()
{
    return len;
}

/** Returns process identifier */
char Process::getID()
{
    return ident;
}

//Returns end time of most recent I/O block
int Process::getNextIO()
{
    return nextio;
}

//Returns current tau value
int Process::getTau()
{
    return tau;
}


int Process::getCur()
{
    return cur;
}

double Process::getAvgBurst()
{
    return totalburst;
}

int Process::getWait()
{
    return waittime;
}

int Process::getWaits()
{
    return waits;
}
/** move current to the next set of bursts down the line in the process */
void Process::nextP()
{
    totalburst+=cpuTimes[cur];
    cur++;
}

void Process::setWait(int currtime)
{
    waittime = currtime;
    waits+=1;
}
//pushes next tau value for srt and sjf
void Process::nextTau()
{
    tau = ceil((cpuTimes[cur]*alpha) +(tau*(1-alpha)));
}
void Process::addTimes(int CPUBurstTime, int IOBurstTime)
{
    cpuTimes.push_back(CPUBurstTime);
    ioTimes.push_back(IOBurstTime);
}

void Process::addTime(int CPUBurstTime)
{
    cpuTimes.push_back(CPUBurstTime);
}

void Process::addIOevent(int eventtime){
    nextio = eventtime;
}
