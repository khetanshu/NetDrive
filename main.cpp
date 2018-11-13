//
//  main.cpp
//  NetDrive
//

#include <iostream>
#include "interfaces/ServiceTester.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    ServiceTester serviceTester;
    serviceTester._unit_test_RoutingNode();
    
    return 0;
}



