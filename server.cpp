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
    // Loop through the input string to parse each task and its frequency
    while (iss >> selectedTask >> extraFreq) {
        // Initialize frequency for a new task to 0
        if (freq.find(selectedTask) == freq.end()) {
          freq[selectedTask] = 0;
        }
        // Calculate the entropy for the current task using the incremental entropy algorithm
        double ent = calc_incremental_entropy(freq, currFreq, currH, selectedTask, extraFreq, NFreq);
        // Update the frequency for the current task
        freq[selectedTask] += extraFreq;
        // Convert the calculated entropy from double to string
        std::ostringstream oss;
        oss << ent;
        std::string ent_str = oss.str();
        // Append the calculated entropy to the output string
        if (entropies == "") {
            entropies += ent_str + " ";
        } 
        else {
            entropies += " " + ent_str;
        }
    }
    // Return the string containing all calculated entropies
    return entropies;
}

int main(int argc, char *argv[]) {
    // Declare variables for socket programming
    int sockfd, newsockfd, portno, clilen;
    struct sockaddr_in serv_addr, cli_addr;
     
    return 0;
}
