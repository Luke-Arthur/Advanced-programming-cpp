#include "header.h"
#include <iostream>


int main(int argc, char* argv[]) {
    // args: Tasks.txt Workers.txt Output.txt
    // ensure correct CL args are input at run time or program will exit
    // remember that the args at index 0 is the program name
    // for example: ./run Tasks.txt Workers.txt Output.txt
    if (argc != 4) {
        std::cerr << "invalid usage of Args for: " << argv[0] << ", ensure to input the correct CL args at run time." << std::endl;
        return 1;
    }

    // Initialise file data
    FileDataIn taskFile;
    initialiseFileIn(taskFile, argv[1]);
    FileDataIn workerFile;
    initialiseFileIn(workerFile, argv[2]);
    FileOut outFile;
    initialiseFileOut(outFile, argv[3]);


    Task tasks[TASKS];
    int taskCount;

    Worker workers[WORKERS];
    int workerCount;

    readTasks(tasks, taskCount);
    readWorkers(workers, workerCount);
    processTasks(tasks, taskCount, workers, workerCount);

    std::cout << "Processing completed. Check Output.txt for results." << std::endl;

    return 0;
}
