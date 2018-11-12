//
//  StorageNode.hpp
//  NetDrive
//
//

#ifndef StorageNode_hpp
#define StorageNode_hpp

#include <iostream>
#include <unistd.h>
#include "types.hpp"

using namespace std;

class StorageNode {
    
public:
    int sendChunk(string chunkFilename, string storageNodePath);
    int saveChunk(string chunkFilename);
};

#endif /* StorageNode_hpp */
