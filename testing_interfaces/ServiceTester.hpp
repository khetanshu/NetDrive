//
//  ServiceTester.hpp
//  NetDrive
//
//

#ifndef ServiceTester_hpp
#define ServiceTester_hpp

#include "iostream"
#include "RoutingNodeTester.hpp"
#include "StorageNodeTester.hpp"
#include "ClientNodeTester.hpp"
#include "CommunicationTester.hpp"

using namespace std;

class ServiceTester : RoutingNodeTester, ClientNodeTester,StorageNodeTester,CommunicationTester {

public:
    //For Routing module
    void _unit_test_RoutingNode();
    //For Storage Module
    void _unit_test_StorageNode();
    //For Client Module
    void _unit_test_ClientNode();
    //For Communication Module
    void _unit_test_Communication();
};


#endif /* ServiceTester_hpp */
