# Multithreaded Multiplication

## Overview
This program compares two approaches for multiplying large numbers:
1. **Multithreaded Naive Multiplication**: A basic digit-by-digit multiplication approach, parallelized using multiple threads.
2. **Single-Threaded Karatsuba Multiplication**: An efficient divide-and-conquer algorithm that reduces the complexity of multiplying large numbers.

The program performs both types of multiplication and provides a comparison of their performance, showcasing the advantages of multithreading for naive multiplication and the algorithmic efficiency of Karatsuba's method.

## Features

- **Multithreaded Naive Multiplication**:
    - Uses a coordinator-worker system to divide multiplication tasks across multiple threads.
    - Each thread handles multiplying a large number by a single digit and combining partial results.
    - Utilizes synchronization mechanisms (mutexes, condition variables) to manage task queues and ensure thread-safe operations.

- **Karatsuba Multiplication**:
    - A recursive, single-threaded algorithm that reduces the number of multiplicative operations needed.
    - Does not use multithreading, demonstrating efficiency through its algorithmic design rather than parallelism.

- **Performance Comparison**:
    - After performing both types of multiplication, the program compares the results in terms of time taken and accuracy.

## Usage

1. **Input Large Numbers**: You will be prompted to enter two large numbers to multiply.
2**View Performance**: After the operations, the program will display the start time, end time, and total duration for the multiplication. You can compare the results for both methods.

## Build and Run

### Prerequisites

- C++17 or higher.
- Clion or a compiler


