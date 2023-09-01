#pragma once

#include <fstream>

const int WORKERS = 20;
const int TASKS = 20;

// struct to hold in file data
struct FileDataIn {
    const char* filename;
    std::ifstream stream;
};

// struct to hold out file data
struct FileOut {
    const char* filename;
    std::ofstream stream;
};

// stuct to hold task attributes
struct Task {
    int taskId;
    char description[50];
    int uncertainty;
    int difficulty;
    int workerList[WORKERS];
    int workerCount;
};

// struct to hold worker attributes
struct Worker {
    int workerId;
    char name[50];
    int variability;
    int ability;
};

// function prototypes
void initialiseFileIn(FileDataIn &fileData, const char* file);
void closeFileIn(FileDataIn &fileData);
void initialiseFileOut(FileOut &fileOut, const char* fname);
void closeFileOut(FileOut &fileOut);
void readTasks(Task tasks[], int& taskCount);
void readWorkers(Worker workers[], int& workerCount);
double forecastedPerformance(Task& task, Worker& worker);
void processTasks(Task tasks[], int taskCount, Worker workers[], int workerCount);