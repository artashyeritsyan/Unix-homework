#include "scheduler.hpp"

Scheduler::Scheduler(size_t quantumTime)
{
    _quantumTime = quantumTime;
}

Scheduler::~Scheduler()
{
    while (!_processQueue.empty()) {
        _processQueue.pop();
    }

}

void Scheduler::addProcess(process p)
{
    _processQueue.push(p);
}

void Scheduler::addProcesses(std::queue<process> processes)
{
    while (!processes.empty()) {
        _processQueue.push(processes.front());
        processes.pop();
    }
}

void Scheduler::addProcesses(std::vector<process> processes)
{
    for (const auto& p : processes) {
        _processQueue.push(p);
    }
}

std::queue<process> Scheduler::getProcesses() const
{
    return _processQueue;
}

void Scheduler::setQuantumTime(size_t quantumTime)
{
    _quantumTime = quantumTime;
}

size_t Scheduler::getQuantumTime() const
{
    return _quantumTime;
}

void Scheduler::startScheduling()
{
    while (!_processQueue.empty()) {
        process currentProcess = _processQueue.front();
        _processQueue.pop();

        std::cout << "Current process: " << currentProcess.pid << std::endl;
        std::cout << "remaining time: " << currentProcess.remaining_time << std::endl;

        if (currentProcess.remaining_time > _quantumTime) {
            currentProcess.remaining_time -= _quantumTime;
            _processQueue.push(currentProcess);
        }
        else {
            std::cout << "Process with PID: " << currentProcess.pid << " finished." << std::endl;
        }
    }
}

