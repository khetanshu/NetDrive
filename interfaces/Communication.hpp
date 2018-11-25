//
//  Communication.hpp
//  NetDrive
//
//

#ifndef Communication_hpp
#define Communication_hpp

#include <unistd.h> 
#include <iostream> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <arpa/inet.h>

#include "Types.hpp"

using namespace std;

class Communication{

private:

protected:
	packet p;
    
public:
    Communication();
    virtual void listener(int argc, const char * argv[]);
    int sendFile(string hostssh, string filename, string destPath);
    int retreiveFile(string hostssh, string filename, string destPath);
};


#endif /* Communication_hpp */
