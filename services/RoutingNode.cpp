//
//  RoutingNode.cpp
//  NetDrive
//
//

#include "routingNode.hpp"


bool RoutingNode::canStore(int newFileSize){
    return (newFileSize > totalRemainingStorageCapacity)? false:true;
}


vector<chunk> RoutingNode::generateChunkInfo(string filename, int size){
    vector<chunk> chunks;
    //TO:DO
    
    
    
    
    
    
    
    
    return chunks;
}

vector<chunk> RoutingNode::storeFile(string filename, int size){
    vector<chunk> chunks;
    if(canStore(size)){
        fileIndex[filename] = generateChunkInfo(filename, size);
        return fileIndex[filename];
    }
    return chunks;
}


vector<chunk> RoutingNode::retrieveFilestring (string filename){
    return fileIndex[filename];
}



