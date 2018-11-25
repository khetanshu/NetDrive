//
//  main.cpp
//  NetDrive
//

#include <iostream>
#include "ServiceTester.hpp"


using namespace std;

int main(int argc, const char * argv[]) {
//    ServiceTester serviceTester;
//    serviceTester._unit_test_Communication();
////    serviceTester._unit_test_RoutingNode();
    
    ClientNode node;
    node.listener(argc, argv);
    
    return 0;
}



