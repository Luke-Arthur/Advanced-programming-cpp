#include "header.h"
#include <iostream>
#include <sstream>
#include <random>
#include <string>
#include <iomanip>

void initializeFileIn(FileDataIn &fileData, const char* fname) {
    fileData.filename = fname;
    fileData.stream.open(fname);
    if (!fileData.stream) {
        std::cerr << "Failed to open " << fname << std::endl;
        exit(1);
    }
}

void closeFileIn(FileDataIn &fileData) {
    fileData.stream.close();
}

void initializeFileOut(FileOut &fileOut, const char* fname) {
    fileOut.filename = fname;
    fileOut.stream.open(fname);
    if (!fileOut.stream) {
        std::cerr << "Failed to open " << fname << std::endl;
        exit(1);
    }
}

void closeFileOut(FileOut &fileOut) {
    fileOut.stream.close();
}

void readTasks(Task tasks[], int& taskCount) {
    FileDataIn taskFile;
    initializeFileIn(taskFile, "Tasks.txt");
    taskCount = 0;
    std::string line;
    while (std::getline(taskFile.stream, line)) {
        std::stringstream ss(line);
        ss >> tasks[taskCount].taskId;
        ss.ignore(); // comma
        ss.getline(tasks[taskCount].description, 50, ',');
        ss >> tasks[taskCount].uncertainty;
        ss.ignore(); // comma
        ss >> tasks[taskCount].difficulty;
        ss.ignore(10, ':'); // jump to worker list

        int workerId;
        tasks[taskCount].workerCount = 0;
        while (ss >> workerId) {
            tasks[taskCount].workerList[tasks[taskCount].workerCount++] = workerId;
            ss.ignore(); // comma or end of line
        }

        taskCount++;
    }
    closeFileIn(taskFile);
}

void readWorkers(Worker workers[], int& workerCount) {
    FileDataIn workerFile;
    initializeFileIn(workerFile, "Workers.txt");
    workerCount = 0;
    std::string line;
    while (std::getline(workerFile.stream, line)) {
        std::stringstream ss(line);
        ss >> workers[workerCount].workerId;
        ss.ignore(); // comma
        ss.getline(workers[workerCount].name, 50, ',');
        ss >> workers[workerCount].variability;
        ss.ignore(); // comma
        ss >> workers[workerCount].ability;

        workerCount++;
    }
    closeFileIn(workerFile);
}

double simulatePerformance(const Task& task, const Worker& worker) {
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


void processTasks(const Task tasks[], int taskCount, const Worker workers[], int workerCount) {
    FileOut outFile;
    initializeFileOut(outFile, "Output.txt");

    for (int i = 0; i < taskCount; i++) {
        const Task& task = tasks[i];
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
            outFile.stream << "The average performance is " << std::fixed << std::setprecision(2) << performance << std::endl;
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
