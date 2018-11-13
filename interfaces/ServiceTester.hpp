//
//  ServiceTester.hpp
//  NetDrive
//
//  Created by khetanshu on 11/12/18.
//  Copyright © 2018 khetanshu. All rights reserved.
//

#ifndef ServiceTester_hpp
#define ServiceTester_hpp

#include "iostream"
#include "routingNode.hpp"
#include "storageNode.hpp"

using namespace std;

class ServiceTester{
private:
    //Used for Routing Module
    void _unit_test_fileStoreAndPrint(RoutingNode& routingNode, string filename, int fileSize);
    void _unit_test_printChunk(chunk& ck);
    
public:
    //For Routing module
    void _unit_test_RoutingNode();
    
    //For Storage Module
    void _unit_test_StorageNode();
};

#endif /* ServiceTester_hpp */
