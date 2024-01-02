# Socket-Based Incremental Entropy Calculator (PA2)

## Overview
This repository contains the implementation of a distributed version of the multithreaded incremental entropy algorithm, incorporating interprocess communication using sockets in UNIX. It's an extension of the first programming assignment, now allowing communication between a client and server program. This project was developed as part of my Operating Systems course at the University of Houston.

## Objective
The goal is to demonstrate the use of sockets for interprocess communication in a UNIX environment. This involves a client program sending task scheduling information to a server program, which calculates the entropy using the incremental entropy algorithm and returns the results.

## Features
- **Client-Server Architecture**: Utilizes socket programming for communication between client and server.
- **Multithreading and Multiprocessing**: Employs POSIX threads in the client and multiple processes (fork) in the server for handling concurrent requests.
- **Incremental Entropy Calculation**: Implements the algorithm for entropy calculation in a distributed environment.


## How to Run

### Server Program
1. Compile the server program:

```bash
g++ -o server server.cpp
```

2. Run the server specifying a port number:

```bash
./server [port_no]
```


### Client Program
1. Compile the client program:

```bash
g++ -pthread -o client client.cpp
```

2. Run the client with the server's hostname and port number:

```bash
./client [hostname] [port_no] < input_filename
```

## Input Format
The client program expects input through a file, redirected as standard input. Each line represents the scheduling information of a CPU.


Example:

```bash
A 2 B 4 C 3 A 7
B 3 A 3 C 3 A 1 B 1 C 1
```


## Output
Both client and server programs perform their tasks silently without STDOUT output. The client program, after processing, displays the entropy values for each CPU.

Example Output:

```bash
CPU 1
Task scheduling information: A(2), B(4), C(3), A(7)
Entropy for CPU 1
0.00 0.92 1.53 1.42

CPU 2
Task scheduling information: B(3), A(3), C(3), A(1), B(1), C(1)
Entropy for CPU 2
0.00 1.00 1.58 1.57 1.57 1.58
```

## Dependencies
- g++ compiler with support for C++11 or later.
- UNIX environment for sockets and POSIX threads.


## Acknowledgments
Special thanks to Dr. Rincon for the foundational algorithm and for their guidance and support.
