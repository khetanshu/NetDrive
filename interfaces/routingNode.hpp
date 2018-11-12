//
//  RoutingNode.hpp
//  NetDrive
//
//

#ifndef RoutingNode_hpp
#define RoutingNode_hpp

#include "iostream"
#include "unordered_map"
#include "vector"
#include "types.hpp"

using namespace std;

class RoutingNode {
    //Data structures
    int totalStorageNodes; //Keeps track of total storage nodes
    long totalRemainingStorageCapacity; //Keeps track of total remaining storage capacity in the system {as a whole}
    unordered_map<int,int> nodeRemainingStorageCapacity; //Keeps track of the the remaining storage capacity of each storage node
    int lastestChunkID; //Keeps track of the latest ID assigned to the file's chunks. This is a unique ID assigned to each chunks in the system
    unordered_map<string,vector<chunk>> fileToChunksIndex;//Keeps the chunks information of each files within the system
    
private:
    vector<chunk> generateChunkInfo(string filename, int size);
    
public:
    bool canStore(int newFileSize);
    vector<chunk> storeFile(string filename, int size);
    vector<chunk> retrieveFilestring (string filename);
};


#endif /* RoutingNode_hpp */
