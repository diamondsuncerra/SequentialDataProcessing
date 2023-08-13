# Sequential Data Processing

This C program demonstrates various data processing algorithms implemented using a doubly linked list data structure.
The primary objective is to correct and enhance received data points. The algorithms address challenges such as 
noise reduction, data completion, and frequency uniformization. The program provides a command-line interface to
apply these algorithms selectively to the data.

The program focuses on improving the quality of received data by applying a series of algorithms. 
The provided data includes timestamps and values, and these algorithms aim to enhance the data points,
eliminate noise, and provide insights through statistical analysis. The implementation adheres to the constraint 
of using doubly linked lists instead of arrays, offering flexibility and efficiency.

## Getting Started

### Compilation

To compile the program, navigate to the project directory and execute the provided Makefile. Open a terminal and run:

```shell
make
```

This will generate an executable named `main`.

### Running the Program

Once compiled, you can run the program with specific algorithm flags. 
For instance, to apply algorithms `--e1`, `--e2`, and `--u`, you can execute:

```shell
./main --e1 --e2 --u
```

Provide the total number of data points followed by each data point's timestamp and value.

## Algorithms

### Exception Elimination Using Statistics

This algorithm focuses on eliminating exceptional data points by leveraging statistical analysis. 
It creates a new list, adjusting data points based on calculated averages and standard deviations 
within predefined windows.

### Noise Elimination Using Median Filter

This algorithm addresses noise reduction by implementing a median filter. It calculates the median value
within a specified window and inserts these medians into a new list.

### Noise Elimination Using Mean-Based Filter

To further reduce noise, this algorithm employs a mean-based filter. It calculates the mean value within
a window and inserts these calculated mean values into a new list.

### Frequency Uniformization

This algorithm aims to harmonize data point frequencies over time. If the interval between consecutive data 
points exceeds a set threshold, the values and timestamps are adjusted using arithmetic averages.

### Data Completion

In cases where data intervals are significantly large, this algorithm offers data completion. By applying
defined formulas, the missing data points are estimated based on neighboring values and timestamps.

### Statistical Analysis

This algorithm performs statistical analysis over intervals of specified lengths. It displays the count 
of data points within each interval starting from the smallest value.

## Usage

After running the program with desired algorithm flags, the resulting modified list is displayed. If the
statistical analysis algorithm `--stN` is used, the program prints interval statistics.
