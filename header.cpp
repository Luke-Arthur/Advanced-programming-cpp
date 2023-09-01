#include "header.h"
#include <iostream>
#include <sstream>
#include <random>
#include <string>
#include <iomanip>

//
void initialiseFileIn(FileDataIn &fileData, const char* fName) {
    fileData.filename = fName;
    fileData.stream.open(fName);
    if (!fileData.stream) {
        std::cerr << "Failed to open " << fName << std::endl;
        exit(1);
    }
}

void closeFileIn(FileDataIn &fileData) {
    fileData.stream.close();
}

void initialiseFileOut(FileOut &fileOut, const char* fName) {
    fileOut.filename = fName;
    fileOut.stream.open(fName);
    if (!fileOut.stream) {
        std::cerr << "Failed to open " << fName << std::endl;
        exit(1);
    }
}

void closeFileOut(FileOut &fileOut) {
    fileOut.stream.close();
}

void readTasks(Task tasks[], int& taskCount, FileDataIn &taskFile) {

    initialiseFileIn(taskFile, taskFile.filename);
    taskCount = 0;
    std::string line;
    while (std::getline(taskFile.stream, line)) {
        std::stringstream stgStrm(line);
        stgStrm >> tasks[taskCount].taskId;
        stgStrm.ignore(); // comma
        stgStrm.getline(tasks[taskCount].description, 50, ',');
        stgStrm >> tasks[taskCount].uncertainty;
        stgStrm.ignore(); // comma
        stgStrm >> tasks[taskCount].difficulty;
        stgStrm.ignore(10, ':'); // jump to worker list

        int workerId;
        tasks[taskCount].workerCount = 0;
        while (stgStrm >> workerId) {
            tasks[taskCount].workerList[tasks[taskCount].workerCount++] = workerId;
            stgStrm.ignore(); // comma or end of line
        }

        taskCount++;
    }
    closeFileIn(taskFile);
}

void readWorkers(Worker workers[], int& workerCount, FileDataIn &workerFile) {

    initialiseFileIn(workerFile, workerFile.filename);
    workerCount = 0;
    std::string line;
    while (std::getline(workerFile.stream, line)) {
        std::stringstream stgStrm(line);
        stgStrm >> workers[workerCount].workerId;
        stgStrm.ignore(); // comma
        stgStrm.getline(workers[workerCount].name, 50, ',');
        stgStrm >> workers[workerCount].variability;
        stgStrm.ignore(); // comma
        stgStrm >> workers[workerCount].ability;

        workerCount++;
    }
    closeFileIn(workerFile);
}

double forecastedPerformance(Task& task, Worker& worker) {
    std::random_device seed;
    std::mt19937 gen(seed());
    double mean = worker.ability - task.difficulty;
    double stddev = task.uncertainty + worker.variability;
    std::normal_distribution<double> dist(mean, stddev);

    double total = 0;
    for (int i = 0; i < 5; i++) {
        total += dist(gen);
    }
    //this is the average of the 5 trials
    return total / 5;
}


void processTasks(Task tasks[], int taskCount, Worker workers[], int workerCount, FileOut &outFile) {

    initialiseFileOut(outFile, outFile.filename);

    for (int i = 0; i < taskCount; i++) {
        Task& task = tasks[i];
        printf("\n");
        outFile.stream << "==================================================================" << std::endl;
        outFile.stream << "processing taskId: " << task.taskId << std::endl;
        outFile.stream << "description: " << task.description << std::endl;
        outFile.stream << "uncertainty: " << task.uncertainty << std::endl;
        outFile.stream << "difficulty: " << task.difficulty << std::endl;
        outFile.stream << "workers: ";
        for (int j = 0; j < task.workerCount; j++) {
            outFile.stream << task.workerList[j];
            if (j < task.workerCount - 1) {
                outFile.stream << ",";
            }
        }
        outFile.stream << std::endl;

        for (int j = 0; j < task.workerCount; j++) {
            int workerId = task.workerList[j];
            Worker worker;
            bool found = false;
            for (int k = 0; k < workerCount; k++) {
                if (workers[k].workerId == workerId) {
                    worker = workers[k];
                    found = true;
                    break;
                }
            }
            if (!found) continue;

            double performance = simulatePerformance(task, worker);


            outFile.stream << "------------------------------------------------------------------" << std::endl;
            outFile.stream << "Trial: workers: " << worker.workerId << std::endl;
            outFile.stream << "------------------------------------------------------------------" << std::endl;
            outFile.stream << "The average performance is " << std::fixed << std::setprecision(0) << performance << std::endl;
            if (performance > 50) {
                outFile.stream << "Assignment of Task " << task.taskId << " to worker " << worker.workerId << " succeeds" << std::endl;
                break;
            } else {
                outFile.stream << "Assignment of Task " << task.taskId << " to worker " << worker.workerId << " fails" << std::endl;
            }
        }
    }

    closeFileOut(outFile);

}

