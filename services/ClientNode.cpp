//
//  ClientNode.cpp
//  NetDrive
//
//

#include "clientNode.hpp"
#include "stdexcept"
#include "fstream"
#include "string"
#include "vector"




void clientNode::splitFile(string fileName, vector<int>& sizes)
{
    int peek = 0, i = 0;
    string line;
    string buffer = "";
    
//  reading file to buffer
    try
    {
        ifstream i_file(file_name);
        
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
    for(auto &size: sizes) 
    {
        try
        {   
            ofstream o_file(fileName+"-"+to_string(i++));
            o_file << buffer.substr(peek, size);
            o_file.close();
            peek+=size;
            cout << endl;
        }
        catch (exception const& e)
        {
            cerr << "Error ocurred while writing file!\n" << e.what() << endl; 
        }
    }

} 


bool ClientNode::transferFileToCloud(vector<chunk>& chunks){
    //TODO
     return true;
}

bool ClientNode::transferChunkToStorageNode(chunk chunk){
    //TODO
    return true;
}
