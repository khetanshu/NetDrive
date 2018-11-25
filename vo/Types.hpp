//
//  Types.h
//  NetDrive
//
//

#ifndef Types_hpp
#define Types_hpp

//Types definations
typedef struct chunk{
    int storageNode;
    long size;
    int sequenceID;
    int chunkID;
} chunk;

typedef struct packet {
    char header;
    char params;
    int data_size;
    char* data;
} packet;

typedef struct nodeInfo {
    std::string hostname;
    std::string port;
    //or
    std::string hostssh;
}nodeInfo;


#endif /* Types_h */
