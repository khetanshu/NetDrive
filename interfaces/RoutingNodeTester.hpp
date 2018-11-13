//
//  RoutingNodeTester.hpp
//  NetDrive
//
//

#ifndef RoutingNodeTester_hpp
#define RoutingNodeTester_hpp

#include "iostream"
#include "RoutingNode.hpp"

class RoutingNodeTester{
  
protected:
    //Used for Routing Module
    void fileStoreAndPrint(RoutingNode& routingNode, string filename, int fileSize);
    void printChunks(chunk& ck);
    void printRemainingNodeCapacities(RoutingNode routingNode);
    void fileSearchAndPrint(RoutingNode& routingNode, string filename);
    
};


#endif /* RoutingNodeTester_hpp */
