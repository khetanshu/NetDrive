//
//  RoutingNodeTester.cpp
//  NetDrive
//
//

#include "RoutingNodeTester.hpp"

void RoutingNodeTester::fileStoreAndPrint(RoutingNode& routingNode, string filename, int fileSize){
    cout << "Chunks for "+filename<<" of size = "<<fileSize<<endl;
    if(routingNode.canStore(fileSize)){
        vector<chunk> chunks = routingNode.storeFile(filename,fileSize);
        for(chunk ck : chunks){
            printChunks(ck);
        }
    }else{
        cout<<"File cannot be stored!";
    }
    cout<<endl;
}

void RoutingNodeTester::printChunks(chunk& ck){
    cout<<"<S_Node:" << ck.storageNode <<", size :" <<ck.size <<", seqID:"<<ck.sequenceID <<", chunkID:"<<ck.chunkID<<">"<<endl;
}

void RoutingNodeTester::printRemainingNodeCapacities(RoutingNode routingNode){
    unordered_map<int,long> remainingNodesCap =routingNode.getRemainingNodesCapacities();
    int n = routingNode.getTotalStorageNodes();
    cout<<"--> Remaining Node's Capacities : { " ;
    for(int i=0;i<n;i++){
        cout<<remainingNodesCap[i] <<" ";
    }
    cout << "} = Total:"<<routingNode.getTotalRemainingStorageCapacity() <<endl<<endl;
}


void RoutingNodeTester::fileSearchAndPrint(RoutingNode& routingNode, string filename){
    cout << "Searching for :"+filename<<endl;
    vector<chunk> chunks = routingNode.retrieveFile(filename);
    if(chunks.size()>0){
        for(chunk ck : chunks){
            printChunks(ck);
        }
    }else{
        cout<<"File not found!"<<endl;
    }
    cout<<endl;
    
}

int main(int argc, const char * argv[]) {

   RoutingNode node;
   node.listener(argc, argv);

   return 0;
}
