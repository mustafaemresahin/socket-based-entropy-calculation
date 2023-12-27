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
// Function to calculate incremental entropy
double calc_incremental_entropy(std::map<char, int> &freq, int &currFreq, double &currH, char selectedTask, int extraFreq, int &NFreq) {
    double H, newTerm, currentTerm;
    // Update the total frequency
    NFreq = currFreq + extraFreq;
    // Calculate the entropy
    if (NFreq == extraFreq) {
        H = 0;
    } 
    else {
        currentTerm = freq[selectedTask] == 0 ? 0 : freq[selectedTask] * log2(freq[selectedTask]);
        newTerm = (freq[selectedTask] + extraFreq) * log2(freq[selectedTask] + extraFreq);
        NFreq = static_cast<double>(NFreq);
        H = log2(NFreq) - ((log2(currFreq) - currH) * (currFreq) - currentTerm + newTerm) / NFreq;
    }
    // Update the current frequency and entropy
    currFreq = NFreq;
    currH = H;
    return H;
};

// Middleman function to calculate entropy
std::string middleman(std::string input) {
    // Initialize variables
    std::string entropies = "";
    std::istringstream iss(input);
    char selectedTask;
    int extraFreq;
    std::map<char, int> freq;
    int currFreq = 0;
    double currH = 0.0;
    int NFreq = 0;
    
}
