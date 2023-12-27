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
    
    return 0;
};
