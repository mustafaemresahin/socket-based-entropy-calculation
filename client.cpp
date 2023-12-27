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
