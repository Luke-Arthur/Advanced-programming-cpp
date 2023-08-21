#include "header.h"
#include <iostream>

int main() {
    Task tasks[MAX_TASKS];
    int taskCount;

    Worker workers[MAX_WORKERS];
    int workerCount;

    readTasks(tasks, taskCount);
    readWorkers(workers, workerCount);
    processTasks(tasks, taskCount, workers, workerCount);

    std::cout << "Processing completed. Check Output.txt for results." << std::endl;

    return 0;
}
