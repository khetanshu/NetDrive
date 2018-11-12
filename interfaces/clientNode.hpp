//
//  ClientNode.hpp
//  NetDrive
//
//

#ifndef ClientNode_hpp
#define ClientNode_hpp

#include "iostream"
#include "types.hpp"

using namespace::std;

class Client{
//    splitFile(string filename);
//    mergeFile(string filename);
    
public:
    bool storeFile(string filename);
    bool retriveFile(string filename);
    
};


#endif /* ClientNode_hpp */
