//
//  StorageNode.hpp
//  NetDrive
//
//

#ifndef StorageNode_hpp
#define StorageNode_hpp

#include <iostream>
#include <unistd.h>
#include "types.hpp"
#include "communication.hpp"
#include "unordered_map"

using namespace std;

class StorageNode : Communication{
    unordered_map<int,string> chunkIndex; //Keeps track of chunk ID and its filepath
    
private:
    string getChunkPath(int chunkID);
    
public:
    int sendChunk(string chunkFilename, string storageNodePath);
    int saveChunk(string chunkFilename);
};

#endif /* StorageNode_hpp */
