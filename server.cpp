// Code template was provided by Professor Rincon
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/wait.h>
#include <map>
#include <cmath>
#include <sstream>
#include <string>
// Fireman function to handle zombie processes
void fireman(int) {
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

