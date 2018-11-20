//
//  ClientNode.cpp
//  NetDrive
//
//

#include "ClientNode.hpp"


void ClientNode::splitFile(string fileName, vector<chunk>& chunks)
{
    
    int peek = 0, i = 0;
    string line;
    string buffer = "";
    
    //  reading file to buffer
    try
    {
        ifstream i_file(fileName);
        while (!i_file.eof())
        {
            getline(i_file, line);
            buffer+=line;
            buffer+="\n";
        }
        i_file.close();
    }
    catch (exception const& e)
    {
        cerr << "Error occured while reading file!\n" << e.what() << endl;
    }
    
    
    //  splitting file into chunks
    for(auto &chunk: chunks)
    {
        try
        {
            ofstream o_file(to_string(chunk.chunkID));
            o_file << buffer.substr(peek, chunk.size);
            o_file.close();
            peek+=chunk.size;
            cout << endl;
        }
        catch (exception const& e)
        {
            cerr << "Error ocurred while writing file!\n" << e.what() << endl;
        }
     }
} 


bool ClientNode::transferFileToCloud(vector<chunk>& chunks){
    for(chunk c : chunks){
        transferChunkToStorageNode(c);
    }
    return true;
}

bool ClientNode::transferChunkToStorageNode(chunk chunk){
    //TODO;
    
    
    
    
    
    return true;
}


void ClientNode::listener() {
    
}
