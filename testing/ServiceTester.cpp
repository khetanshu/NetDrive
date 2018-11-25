//
//  ServiceTester.cpp
//  NetDrive
//
//

#include "ServiceTester.hpp"

//Testing routing node
void ServiceTester::_unit_test_RoutingNode(){
    RoutingNode routingNode;
    cout<<"***** Testing for STORE_FILE() *****" <<endl<<endl;
    
    printRemainingNodeCapacities(routingNode);
    fileStoreAndPrint(routingNode, "file1", 10);
    printRemainingNodeCapacities(routingNode);
    fileStoreAndPrint(routingNode, "file2", 4);
    printRemainingNodeCapacities(routingNode);
    fileStoreAndPrint(routingNode, "file3", 6);
    printRemainingNodeCapacities(routingNode);
    fileStoreAndPrint(routingNode, "file4", 4);
    printRemainingNodeCapacities(routingNode);
    
    
    cout<<"***** Testing for RETRIEVE_FILE() *****" <<endl<<endl;
    fileSearchAndPrint(routingNode, "file1");
    fileSearchAndPrint(routingNode, "file2");
    fileSearchAndPrint(routingNode, "file3");
    fileSearchAndPrint(routingNode, "file4");
    fileSearchAndPrint(routingNode, "file5");
    
    cout<<endl;
}

void ServiceTester::_unit_test_StorageNode(){
    //TODO
}

void ServiceTester::_unit_test_ClientNode(){
    //TODO
}


void ServiceTester::_unit_test_Communication(){
        //TODO
    Communication comm;
    comm.retreiveFile("scu", "~/test.txt", "~/temp/");
}

//void ServiceTester::_unit_test_StorageNode(){
//    StorageNode storageNode;
//    //transfer a file
//    string filename = "~/test.txt";
//    string storageNodePath ="scu:~/OS_Project/";
//
//    int status = storageNode.sendChunk(filename, storageNodePath);
//    cout<< "Transfer status : "<< (status==0?"success":"failed") <<endl;
//}
//



/*END*/
