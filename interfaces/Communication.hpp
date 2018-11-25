//
//  communication.hpp
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

class Communication{

private:

protected:
	packet p;
    
public:
    Communication();
    void server(int port);
    void act(char *buffer, int buffer_len);
    void client(int port, char const *ip);
    void parse(char *buffer, int buffer_len);
    
    virtual void listener(int argc, const char * argv[]);
    int sendFile(string hostssh,string chunkFilename, string storageNodePath);
};


#endif /* Communication_hpp */
