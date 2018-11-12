//
//  StorageNode.cpp
//  NetDrive
//

#include "StorageNode.hpp"


string StorageNode::getChunkPath(int chunkID){
    return chunkIndex[chunkID];
}

int StorageNode::sendChunk(string chunkName, string storageNodePath){
    string command = "scp " + chunkName + " " + storageNodePath; //like command = "scp ~/test.txt scu:~/OS_Project/";
    return system(command.c_str());
}

