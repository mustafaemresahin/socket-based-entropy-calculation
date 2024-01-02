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