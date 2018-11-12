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
#include "Communication.hpp"
#include "Types.hpp"

using namespace std;

class RoutingNode : Communication{
    //Data structures
    int totalStorageNodes; //Keeps track of total storage nodes
    long totalRemainingStorageCapacity; //Keeps track of total remaining storage capacity in the system {as a whole}
    unordered_map<int,int> nodeCapacityIndex; //Keeps track of the the remaining storage capacity of each storage node
    int lastestChunkID; //Keeps track of the latest ID assigned to the file's chunks. This is a unique ID assigned to each chunks in the system
    unordered_map<string,vector<chunk>> fileIndex;//Keeps the chunks information of each files within the system
    
private:
    //
    vector<chunk> generateChunkInfo(string filename, int size);
    
public:
    //Returns true if totalRemainingStorageCapacity <= newFileSize otherwise false
    bool canStore(int newFileSize);
    
    //If the size of the input file is less than then total available system's storage capacity
    //then module would return the information of the chunks; Client would need to divide the the file into
    //chunks as stated in the passed infomration and trasnfer those to the storage nodes
    vector<chunk> storeFile(string filename, int size);
    
    //Returns the chunks information of the input file
    vector<chunk> retrieveFilestring (string filename);
};


#endif /* RoutingNode_hpp */
