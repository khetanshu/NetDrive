//
//  ServiceTester.cpp
//  NetDrive
//
//  Created by khetanshu on 11/12/18.
//  Copyright © 2018 khetanshu. All rights reserved.
//

#include "ServiceTester.hpp"

/*Unit test cases implementations*/
void ServiceTester::_unit_test_RoutingNode(){
    RoutingNode routingNode;
    _unit_test_fileStoreAndPrint(routingNode, "file1", 10);
    _unit_test_fileStoreAndPrint(routingNode, "file2", 4);
    _unit_test_fileStoreAndPrint(routingNode, "file3", 7);
    _unit_test_fileStoreAndPrint(routingNode, "file4", 4);
    
    cout<<endl;
}

void ServiceTester::_unit_test_fileStoreAndPrint(RoutingNode& routingNode, string filename, int fileSize){
    cout << "Chunks for "+filename<<" of size:"<<fileSize<<endl;
    if(routingNode.canStore(fileSize)){
        vector<chunk> chunks = routingNode.storeFile(filename,fileSize);
        for(chunk ck : chunks){
            _unit_test_printChunk(ck);
        }
    }else{
        cout<<"File cannot be stored!";
    }
    cout<<endl;
}

void ServiceTester::_unit_test_printChunk(chunk& ck){
    cout<<"<S_Node:" << ck.storageNode <<", size :" <<ck.size <<", seqID:"<<ck.sequenceID <<", chunkID:"<<ck.chunkID<<">"<<endl;
}

void ServiceTester::_unit_test_StorageNode(){
    StorageNode storageNode;
    //transfer a file
    string filename = "~/test.txt";
    string storageNodePath ="scu:~/OS_Project/";
    
    int status = storageNode.sendChunk(filename, storageNodePath);
    cout<< "Transfer status : "<< (status==0?"success":"failed") <<endl;
}

/*END*/
