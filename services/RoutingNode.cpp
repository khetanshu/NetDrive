//
//  RoutingNode.cpp
//  NetDrive
//
//

#include "routingNode.hpp"

vector<chunk> RoutingNode::generateChunkInfo(string filename, int size){
    vector<chunk> chunks;
    //TO:DO
    
    return chunks;
}

bool RoutingNode::canStore(int newFileSize){
    return (newFileSize > totalRemainingStorageCapacity)? false:true;
}

vector<chunk> RoutingNode::storeFile(string filename, int size){
    vector<chunk> chunks;
    if(canStore(size)){
        fileToChunksIndex[filename] = generateChunkInfo(filename, size);
        return fileToChunksIndex[filename];
    }
    return chunks;
}

vector<chunk> RoutingNode::retrieveFilestring (string filename){
    return fileToChunksIndex[filename];
}



