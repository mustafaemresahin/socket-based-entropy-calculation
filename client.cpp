#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#include <sstream>
#include <string>
#include <iomanip>

// Structure to hold input data, output data, port number and server info
struct InputData {
    std::string input;
    std::vector<double> output;
    int port;
    const char *host;
};

// Thread function to handle communication with the server
void *f(void *arg) {
    // Cast the argument to the correct type
    InputData *data = (InputData *)arg;
    // Initialize variables for socket communication
    int sockfd, portno, n;
    std::string buffer;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    // Create a socket
    portno = data->port;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "ERROR opening socket" << std::endl;
        exit(0);
    }
    // Get the server details
    server = gethostbyname(data->host);
    if (server == NULL) {
        std::cerr << "ERROR, no such host" << std::endl;
        exit(0);
    }
    // Set up the server address structure
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    // Connect to the server
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "ERROR connecting" << std::endl;
        exit(0);
    }
    // Send the input data to the server
    buffer = data->input;
    int msgSize = buffer.size();
    n = write(sockfd, &msgSize, sizeof(int));
    if (n < 0) {
        std::cerr << "ERROR writing to socket" << std::endl;
        exit(0);
    }
    // Send the actual message
    n = write(sockfd, buffer.c_str(), msgSize);
    if (n < 0) {
        std::cerr << "ERROR writing to socket" << std::endl;
        exit(0);
    }
    // Read the size of the incoming message
    n = read(sockfd, &msgSize, sizeof(int));
    if (n < 0) {
        std::cerr << "ERROR reading from socket" << std::endl;
        exit(0);
    }
    // Read the incoming message
    char *tempBuffer = new char[msgSize + 1];
    bzero(tempBuffer, msgSize + 1);
    n = read(sockfd, tempBuffer, msgSize);
    if (n < 0) {
        std::cerr << "ERROR reading from socket" << std::endl;
        exit(0);
    }
    buffer = tempBuffer;
    delete[] tempBuffer;
    // Convert the string input to a vector of doubles
    std::vector<double> result;
    std::istringstream iss(buffer);
    double num;
    while (iss >> num) {
        result.push_back(num);
    }
    // Store the vector inside the output vector inside the structure
    data->output = result;
    // CLose the socket
    close(sockfd);
    return 0;
};

// Function to print the results
void printResults(std::vector<InputData> data){
    // Loop through ach CPU's data
    for(int i = 0; i < data.size(); i++){
        // Print CPU number
        std::cout << "CPU " << i+1 << std::endl;
        std::cout << "Task scheduling information: ";
        // Parse the input string to get each task and its frequency
        std::istringstream iss(data[i].input);
        std::string task;
        std::string value;
        while (iss >> task >> value) {
            // Print each task and its frequency
            std::cout << task << "(" << value << ")";
            if (iss.peek() != EOF) std::cout << ", ";
        }
        // Print the calculated entropy values for the CPU
        std::cout << std::endl << "Entropy for CPU " << i+1 << std::endl;
        for(double a : data[i].output){
            // Print each entropy value with 2 decimal places
            std::cout << std::fixed << std::setprecision(2) << a << " ";
        }
        std::cout << std::endl << std::endl;
    }
}

int main(int argc, char *argv[]) {
    // Check for correct number of arguments
    if (argc != 3) {
        std::cerr << "usage " << argv[0] << " hostname port" << std::endl;
        exit(0);
    }
    std::vector<std::string> inputs;
    std::string line;
    // Read lines from standard input to get task scheduling information
    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            break; // Exit the loop if an empty line is encountered
        }
        // Store each line in the vector
        inputs.push_back(line);
    }
    // Extract hostname and port number from command-line arguments
    const char *host = argv[1];
    int port = atoi(argv[2]);
    // Initialize data structures to store input data and thread IDs
    std::vector<InputData> data(inputs.size());
    std::vector<pthread_t> tid(inputs.size());
    // Create threads to handle each input line
    for (int i = 0; i < inputs.size(); i++) {
        data[i].input = inputs[i];
        data[i].host = host;
        data[i].port = port;
        data[i].output = std::vector<double> ((data[i].input.size()-3)/4+1, 1.2);
        pthread_create(&tid[i], NULL, f, &data[i]);
    }
    // Wait for all threads to complete
    for (int i = 0; i < inputs.size(); i++) {
        pthread_join(tid[i], NULL);
    }
    
    return 0;
}
