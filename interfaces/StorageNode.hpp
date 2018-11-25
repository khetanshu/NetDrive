//
//  StorageNode.hpp
//  NetDrive
//
//

#ifndef StorageNode_hpp
#define StorageNode_hpp

#include <iostream>
#include <unistd.h>
#include "Types.hpp"
#include "Communication.hpp"
#include "unordered_map"
#include "vector"
using namespace std;

class StorageNode : Communication{
    unordered_map<int,string> chunkIndex; //Keeps track of chunk ID and its filepath
    vector<nodeInfo> clientNodesInfo;
private:
    string getChunkPath(int chunkID);
    void registerClientNodeSSH(string nodeSSH);
    void registerClientNode(string hostname, string port);
public:
    StorageNode();
    int saveChunk(string chunkFilename);
    void listener(int argc, const char * argv[]) override;
};

#endif /* StorageNode_hpp */
