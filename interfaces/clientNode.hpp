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
    void splitFile(string filename, vector<int>& chunk_sizes); // splits the file to given chunk sizes
//    void mergeFile(string filename);
    
public:
    bool storeFile(string filename);
    bool retriveFile(string filename);
    
};


#endif /* ClientNode_hpp */
