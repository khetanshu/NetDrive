//
//  StorageNode.cpp
//  NetDrive
//

#include "StorageNode.hpp"

StorageNode::StorageNode(){
    //registering the client nodes
    registerClientNodeSSH("clientNode1");//TODO : make it data driven - custom
    registerClientNodeSSH("clientNode2");
}

void StorageNode:: registerClientNode(string hostname, string port){
    nodeInfo clientNode;
    clientNode.hostname = hostname;
    clientNode.port = port;
    clientNodesInfo.push_back(clientNode);
}

void StorageNode::registerClientNodeSSH(string nodeSSH){
    nodeInfo clientNode;
    clientNode.hostssh = nodeSSH;
    clientNodesInfo.push_back(clientNode);
}

string StorageNode::getChunkPath(int chunkID){
    return chunkIndex[chunkID];
}

void StorageNode::listener(int argc, const char * argv[]){
    
}

