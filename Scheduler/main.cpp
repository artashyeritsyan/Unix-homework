#include "scheduler.hpp"

int main() {
    size_t quantumTime = 5;

    Scheduler scheduler(quantumTime);

    process p1(1, 5);
    process p2(2, 2);
    process p3(3, 8);

    scheduler.addProcess(p1);
    scheduler.addProcess(p2);
    scheduler.addProcess(p3);

    scheduler.startScheduling();

    return 0;
}
