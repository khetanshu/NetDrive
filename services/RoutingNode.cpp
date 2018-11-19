//
//  RoutingNode.cpp
//  NetDrive
//
//

#include "RoutingNode.hpp"

RoutingNode::RoutingNode(){
    totalStorageNodes = 3;//TODO : Need to make it data driven
    totalStorageNodesNotEmpty = totalStorageNodes;
    lastestChunkID = 0;
    minStorageCapacity = INT_MAX;
    registerDevices();
    
}

void RoutingNode::registerDevices(){
    cout<<"**** Device Registration ****"<<endl;
    int defaultCapacity=5; //TODO to be made more generic
    for (int i=0; i<totalStorageNodes; i++) {
        int capacity =defaultCapacity+(i%totalStorageNodes)+1;
        nodeCapacityIndex[i]= capacity;//defaultCa`pacity; //In MB/GB as per the assumption , TODO :: TBD
        cout<<"Node["<<i<<"] default capacity:"<<nodeCapacityIndex[i]<<endl;
        totalRemainingStorageCapacity += capacity;
    }
    cout<<endl;
}

bool RoutingNode::canStore(long newFileSize){
    return (newFileSize <= totalRemainingStorageCapacity)? true:false;
}

//The module assumes that a file of the given size can be store in the storage cloud;
//i.e. it has been validated before using this module
vector<chunk>* RoutingNode::generateChunkInfo(long fileSize){
    unordered_map<int, long> newReservation;
    while(fileSize>0){
        long r = fileSize/totalStorageNodesNotEmpty;
        long blockSize = min(minStorageCapacity,(r==0?fileSize:r));
        for (int i=0; i<totalStorageNodes; i++) {
            if(nodeCapacityIndex[i] >= blockSize){
                newReservation[i] +=blockSize;
                nodeCapacityIndex[i] -=blockSize;
                totalRemainingStorageCapacity -=blockSize;
                fileSize -=blockSize;
                //if the remaining capacity of the node become 0 then totalStorageNodesNotEmpty would be reduced by 1
                if(nodeCapacityIndex[i] ==0 ){
                    totalStorageNodesNotEmpty--;
                }
            }
            //updating new minimum storage capacity
            if(nodeCapacityIndex[i] < minStorageCapacity && nodeCapacityIndex[i] >0){
                minStorageCapacity = nodeCapacityIndex[i];
            }
            if(fileSize ==0) break;
        }
    }
    
    //creating a list of chunks with the reserved capacities
    vector<chunk>* chunks = new vector<chunk>();
    for (int i=0; i<totalStorageNodes; i++) {
        if(newReservation[i]==0) continue;
        chunk *chnk = new chunk;
        if(!chnk){
            cout << "Memory allocation failed!!" <<endl;
            return nullptr;
        }
        chnk->storageNode = i;
        chnk->size = newReservation[i];
        chnk->sequenceID = i;
        chnk->chunkID = ++lastestChunkID;
        //adding the chunk to the list of chunks
        chunks->push_back(*chnk);
    }
    return chunks;
}

vector<chunk> RoutingNode::storeFile(string filename, long size){
    vector<chunk> chunks;
    if(canStore(size)){
        fileIndex[filename] = *generateChunkInfo(size);
        chunks= fileIndex[filename];
    }
    return chunks;
}

vector<chunk> RoutingNode::retrieveFile (string filename){
    return fileIndex[filename];
}

//TODO : Currently descoped : To be implement in future
bool RoutingNode::deleteFile(string filename){
    //TODO code here
    
    return true;
}


//getters

unordered_map<int,long> RoutingNode::getRemainingNodesCapacities(){
    return nodeCapacityIndex;
}

int RoutingNode::getTotalStorageNodes(){
    return totalStorageNodes;
}


long RoutingNode::getTotalRemainingStorageCapacity(){
    return totalRemainingStorageCapacity;
}


