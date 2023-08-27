#pragma once

#include <fstream>

const int MAX_WORKERS = 20;
const int MAX_TASKS = 20;

// Struct declaration
struct FileDataIn {
    const char* filename;
    std::ifstream stream;
};

struct FileOut {
    const char* filename;
    std::ofstream stream;
};


struct Task {
    int taskId;
    char description[50];  // Assuming max length as 50
    int uncertainty;
    int difficulty;
    int workerList[MAX_WORKERS];
    int workerCount;
};

struct Worker {
    int workerId;
    char name[50];  // Assuming max length as 50
    int variability;
    int ability;
};

void initializeFileIn(FileDataIn &fileData, const char* fname);
void closeFileIn(FileDataIn &fileData);
void initializeFileOut(FileOut &fileOut, const char* fname);
void closeFileOut(FileOut &fileOut);
void readTasks(Task tasks[], int& taskCount);
void readWorkers(Worker workers[], int& workerCount);
double simulatePerformance(const Task& task, const Worker& worker);
void processTasks(const Task tasks[], int taskCount, const Worker workers[], int workerCount);
