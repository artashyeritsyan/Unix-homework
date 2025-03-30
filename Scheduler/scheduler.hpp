#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <iostream>
#include <queue>

struct process {
    size_t burst_time;
    int remaining_time;
    pid_t pid;

    process(pid_t id, size_t bt) :  pid(id), burst_time(bt) {
        remaining_time = bt;
    }
};

class Scheduler {
public:
    Scheduler(size_t quantumTime);
    ~Scheduler();

    void startScheduling();

    void addProcess(process p);
    void addProcesses(std::queue<process> processes);
    void addProcesses(std::vector<process> processes);
    std::queue<process> getProcesses() const;

    void setQuantumTime(size_t quantumTime);
    size_t getQuantumTime() const;

private:
    size_t _quantumTime;
    std::queue<process> _processQueue;

};


#endif // SCHEDULER_HPP