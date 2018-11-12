//
//  main.cpp
//  NetDrive
//

#include <iostream>
#include "routingNode.hpp"
#include "storageNode.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    StorageNode storageNode;
    //transfer a file
    string filename = "~/test.txt";
    string storageNodePath ="scu:~/OS_Project/";
    
    int status = storageNode.sendChunk(filename, storageNodePath);
    cout<< "Transfer status : "<< (status==0?"success":"failed") <<endl;
    //TODO
    //test
    
    return 0;
}
