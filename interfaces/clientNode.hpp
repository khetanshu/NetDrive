//
//  ClientNode.hpp
//  NetDrive
//
//

#ifndef ClientNode_hpp
#define ClientNode_hpp

#include "iostream"
#include "vector"
#include "types.hpp"

using namespace::std;

class ClientNode{
    //TO:DO device information to be added later during integration

private:
   
    void splitFile(string filename, vector<int>& chunk_sizes); // splits the file to given chunk sizes//    bool mergeFile(string filename);
    
    bool transferFileToCloud(vector<chunk>& chunks);
    bool transferChunkToStorageNode(chunk chunk);
    
    
public:
    bool storeFile(string filename);
    bool retriveFile(string filename);
    
};

#endif /* ClientNode_hpp */
