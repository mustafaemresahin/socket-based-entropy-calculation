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
    // Check for correct number of command-line arguments
    if (argc != 2) {
        std::cerr << "Port not provided" << std::endl;
        exit(0);
    }
    // Create a new socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error opening socket" << std::endl;
        exit(0);
    }
    // Initialize server address structure
    bzero((char *)&serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    // Bind the socket to the server address
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Error binding" << std::endl;
        exit(0);
    }
    // Listen for incoming connections
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    // Handle zombie processes
    signal(SIGCHLD, fireman);
    // Main loop to accept new connections
    while (true) {
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t *)&clilen);
        if (newsockfd < 0) {
            std::cerr << "Error accepting new connections" << std::endl;
            exit(0);
        }
        // Create a new process to handle the client request
        if (fork() == 0) {
            int n, msgSize = 0;
            // Read the message size from the client
            n = read(newsockfd, &msgSize, sizeof(int));
            if (n < 0) {
                std::cerr << "Error reading from socket" << std::endl;
                exit(0);
            }
            // Read the actual message from the client
            char *tempBuffer = new char[msgSize + 1];
            bzero(tempBuffer, msgSize + 1);
            n = read(newsockfd, tempBuffer, msgSize);
            if (n < 0) {
                std::cerr << "Error reading from socket" << std::endl;
                exit(0);
            }
            // Process the client's message
            std::string buffer = tempBuffer;
            delete[] tempBuffer;
            buffer = middleman(buffer);
            
        }
    }
    
    return 0;
}
