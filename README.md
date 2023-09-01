# CSCI251 Assignment 1:    Crowdsourcing System Simulation

## About this project

My program simulates the process of a crowdsourcing system. It assigns tasks to workers based on a set of criteria and evaluates the workers' performance using a probabilistic model. The results are then written to an `Output.txt` file.

## Requirements

- G++ (version 17 or newer)
- Input files: `Tasks.txt` and `Workers.txt`

## Structure

1. **Header Files**:
   - `crowdsourcing.h`: Contains declarations of constants, structs, and functions that are implemented in `crowdsourcing.cpp`.

2. **Implementation File**:
   - `crowdsourcing.cpp`: Contains the logic and implementations of the functions declared in `crowdsourcing.h`.

3. **Driver File**:
   - `driver.cpp`: The main driver of the program. When executed, it reads from `Tasks.txt` and `Workers.txt`, processes the tasks, and writes the results to `Output.txt`.

## How to Run

1. **Compile the Source Code**:
   
   Navigate to the project directory and run the following command:
   ```bash
   g++ -std=c++17 driver.cpp crowdsourcing.cpp -o crowdsourcing
   ```

2. **Run the Program**:
   
   After compilation, run the program using:
   ```bash
   ./crowdsourcing
   ```

3. **Check the Results**:
   
   After execution, the results will be written to `Output.txt`. You can view the file using any text editor or via the command line with:
   ```bash
   cat Output.txt
   ```

## Program Overview

- **Tasks.txt**: Contains information about each task, including a description, uncertainty, difficulty, and a list of potential worker IDs to be assigned the task.

- **Workers.txt**: Contains information about each worker, including their name, variability, and ability.

- **Performance Evaluation**: The program assesses whether a worker can complete a task based on the worker's performance score. This score is determined by drawing from a normal distribution. The success criterion is an average performance score greater than 50 over five attempts.

- **Assignment Logic**: The system will try to assign a task to each worker in the list in order. If a worker is successful, the next task is processed. If not, the next worker in line attempts the task. The results are then saved in `Output.txt`.

## Notes

- Ensure that the `Tasks.txt` and `Workers.txt` files are present in the same directory as the executable. 
- Adjust the `MAX_WORKERS` and `MAX_TASKS` constants in `crowdsourcing.h` if you expect a larger number of entries.

## Support & Contribution

If you encounter any issues or would like to contribute to the improvement of this simulator, please raise an issue or submit a pull request.


    