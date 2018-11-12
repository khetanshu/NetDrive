#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;


void splitFile(const string& file_name, const string& file, vector<int>& sizes);
string readFile_to_buffer(const string& file_name);


int main(int argc, char* argv[])
{
    int temp[] = {12,24,6,6};
    vector<int> sizes(temp, temp+sizeof(temp)/sizeof(int));
    
    if (argc < 2) 
    {
        cerr << "Invalid Arguemnts" << endl;
        exit(EXIT_FAILURE);
    }

    string buffer = read_file_to_buffer(argv[1]); 

    split_file(argv[1], buffer, sizes);
    
    return 0;
}


// 
// Split files into chunks of defined sizes
// 
// Input:
//       file_name (string)     : name of the file
//       file (string)          : buffered content of the file
//       sizes (vector)         : chunk sizes to split file 
//
// Output:
//       Saves file chunks 
//

void splitFile(const string& file_name, const string& file, vector<int>& sizes)
{
    int peek = 0, i = 0;
    
    for(auto &size: sizes) 
    {
        try
        {   
            ofstream o_file(file_name+"-"+to_string(i++));
            o_file << file.substr(peek, size);
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


// Read contents of the file to a buffer
string readFileToBuffer(const string& file_name)
{
    string line;
    string buffer = "";
    
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
    
    return buffer;
}   


