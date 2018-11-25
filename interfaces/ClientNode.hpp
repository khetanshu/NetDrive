//
//  ClientNode.hpp
//  NetDrive
//
//

#ifndef ClientNode_hpp
#define ClientNode_hpp

#include "iostream"
#include "vector"
#include "stdexcept"
#include "fstream"
#include "string"
#include "vector"
#include "Communication.hpp"
#include "Types.hpp"

using namespace::std;

class ClientNode :public Communication {
    //TO:DO device information to be added later during integration
    vector<chunk> chunks;
    vector<nodeInfo> storageNodesInfo;
    
private:
    void registerStorageNodeSSH(string nodeSSH);
    void registerStorageNode(string hostname, string port);
    
    void splitFile(string filename, vector<chunk>* chunks); // splits the file to given chunk sizes
    bool mergeFile(string filename, vector<chunk>* chunks); // merge chunks of file into file with given filename
    
    bool transferFileToCloud(vector<chunk>& chunks);
    bool transferChunkToStorageNode(chunk chunk);
    
    bool retriveFileFromCloud(vector<chunk> chunks);
    bool retriveChunkFromStorageNode(chunk chunk);
    
public:
    
    ClientNode();
    
    void listener(int argc, const char * argv[]) override;
    
    bool storeFile(string filename);
    bool retriveFile(vector<chunk> chunks);
    
    
    
};

#endif /* ClientNode_hpp */
