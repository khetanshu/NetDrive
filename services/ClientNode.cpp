//
//  ClientNode.cpp
//  NetDrive
//
//

#include "ClientNode.hpp"

#include <sys/stat.h>

ClientNode::ClientNode(){
    //registering the storage nodes
    registerStorageNodeSSH("scu");//TODO : make it data driven - custom
    registerStorageNodeSSH("jayantScu");//TODO : make it data driven - custom
}

void ClientNode:: registerStorageNode(string hostname, string port){
    nodeInfo storageNode;
    storageNode.hostname = hostname;
    storageNode.port = port;
    storageNodesInfo.push_back(storageNode);
}

void ClientNode::registerStorageNodeSSH(string nodeSSH){
    nodeInfo storageNode;
    storageNode.hostssh = nodeSSH;
    storageNodesInfo.push_back(storageNode);
}

void ClientNode::splitFile(string filename, vector<chunk>* chunks)
{
    
    int peek = 0, i = 0;
    string line;
    string buffer = "";
    filename = "../download/"+filename; 

    //  reading file to buffer
    try
    {
        ifstream i_file(filename);
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
    for(auto &chunk: *chunks)
    {
        try
        {
            string file = "../upload/"+to_string(chunk.chunkID);
            ofstream o_file(file);
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


// merge the file chunks and returns true if merged successfully
bool ClientNode::mergeFile(string filename, vector<chunk>* chunks)
{
    string buffer = "";
    string line;
    filename = "../download/"+filename;
    try
    {
        for(auto &chunk: *chunks)
        {
            string file = "../upload/"+to_string(chunk.chunkID);
            ifstream i_file(file);
            while(!i_file.eof())
            {
                getline(i_file, line);
                buffer+=line;
                buffer+="\n";
            }
            i_file.close();
        }
    }
    catch(exception e)
    {
        cerr << "Error occured while reading file!\n" << e.what() << endl;
        return false;
    }
    
    try
    {
        ofstream o_file(filename);
        o_file << buffer;
        o_file.close();
        cout << endl;
    }
    catch(exception e)
    {
        cerr << "Error occured while reading file!\n" << e.what() << endl;
        return false;
    }
    
    return true;
}


bool ClientNode::transferFileToCloud(vector<chunk> chunks){
    bool status = true;
    for(chunk c : chunks){
        status = status & transferChunkToStorageNode(c);
    }
    return status;
}

bool ClientNode::transferChunkToStorageNode(chunk chunk){
    nodeInfo nodeInfo = storageNodesInfo[chunk.storageNode]; //extracting the registered system information
    std::string chunkFilename = to_string(chunk.chunkID) ; //Currently chunk won't have any extension. TODO make is generic
    std::string storageNodePath = "~/upload/"; //like command = "scp ~/test.txt scu:~/OS_Project/";
    std::string hostssh = nodeInfo.hostssh;
    return sendFile(hostssh,chunkFilename,storageNodePath);
}

bool ClientNode::retriveFileFromCloud(vector<chunk> chunks){
    bool status = true;
    for(chunk cnk : chunks){
        status = status & retriveChunkFromStorageNode(cnk);
    }
    return status;
}

bool ClientNode::retriveChunkFromStorageNode(chunk chunk){
    string hostssh = storageNodesInfo[chunk.storageNode].hostssh;
    string filename = to_string(chunk.chunkID);
    string destPath = "./download/";
    return retreiveFile(hostssh, filename, destPath) == 0 ? true : false;;
}



void ClientNode::listener(int argc, const char * argv[]) {
    
    int port = 8080;
    char ip[] = "127.0.0.1";
    struct sockaddr_in addr;
    int sock = 0, valread;
    struct sockaddr_in server_addr;
    char buffer[256] = {0};
    char send_it[256] = {0};
    
    // 0. parse the arguments and extract filename
    // parse arguments
    if (argc < 3) {
        
        cout << "[ERROR]: bad usage" << endl;
        exit(1);
    }
    
    /**
     * PACKET HEADER
     *
     * packet[0] = 1 - store file
     * packet[0] = 2 - retrieve file
     
     * packet[0] != {1,2} - error, undefined request
     **/

    if (! strcmp( "store", argv[1])) {

        // store file
        send_it[0] = 1;
    }
    else if (! strcmp("retrieve", argv[1])) {

        // search file
        send_it[0] = 2;
    }
    else { cout << "[ERROR]: bad usage" << endl; exit(1); }
    
    struct stat st;
    if (stat(argv[2], &st) < 0) {
        cerr << "[ERROR]: file doesn't exist locally" << endl;
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while ((send_it[3 + i] = argv[2][i]) != '\0') {  i++; }
    
    
    memset(&server_addr, '0', sizeof(server_addr));
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    
    if(inet_pton(AF_INET, ip, &server_addr.sin_addr)<=0) {
        
        cerr << "[ERROR]: invalid address" << endl;
        exit(EXIT_FAILURE);
    }
    
    if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)  {
        
        cerr << "[ERROR]: socket creation error" << endl;
        exit(EXIT_FAILURE);
    }
    
    if (connect(
                sock,
                (struct sockaddr *) &server_addr,
                sizeof(server_addr)
                ) < 0) {
        
        cerr << "[ERROR]: connection refused" << endl;
        exit(EXIT_FAILURE);
    }

    /**
     * PACKET STATUS
     *
     * packet[1] = 1 - expect string
     * packet[1] = 2 - expect int
     * packet[1] = 3 - file exists
     * packet[1] = 4 - not enough storage
     * packet[1] = 5 - expect chunk data
     **/
    
    send_it[1] = 1;
    
    /**
     * PACKET DATA LENGTH
     *
     * packet[2] = n - where in is an int < 253
     **/
    
    send_it[2] = i;
    
    send(sock, send_it, sizeof(send_it), 0);
    
    // 2. check if the file exists
    read(sock, buffer, sizeof(buffer));
    
    
    // handle store code here
    if (send_it[0] == 1) {
        
        if (buffer[1] == 3) {
            cerr << "[ERROR]: file exists on cloud" << endl;
            exit(EXIT_FAILURE);
        }
        
        // 3. send the file size

        // TODO: this should probably be in it's own
        // function for better portability depending on

        send_it[1] = 2;
        send_it[2] = 4;

        // TODO: we currently compress the data size into mb, 
        // that means we have to add a ceiling if there is any
        // remainder from conversion from bytes to MB.

        // in the future, we should make size a long and
        // just send the exact byte amount.

        int file_size = st.st_size / (1024 * 1024);
        file_size += (st.st_size / (1024 * 1024)) ? 1 : 0;

        memcpy(&send_it[3], &file_size, sizeof(int));
        
        send(sock, send_it, sizeof(send_it), 0);
        
        // 4. check if we the file fits in storage
        read(sock, buffer, sizeof(buffer));
        
        if (buffer[1] == 4) {
            cerr << "[ERROR]: cloud full" << endl;
            exit(EXIT_FAILURE);
        }
    }
    else if (send_it[0] == 2) {
        
        if (buffer[1] != 3) {
            cerr << "[ERROR]: file not found" << endl;
            exit(EXIT_FAILURE);
        }
    }
    
    // 4. fize size ok, we're ready for chunk data
    send_it[1] = 5;
    
    send(sock, send_it, sizeof(send_it), 0);
    
    // 5. read and parse chunk data
    read(sock, buffer, sizeof(buffer));
    
    int num_chunks = (int) buffer[3];
    
    vector<chunk> chunks;
    chunks.reserve(num_chunks);

    // cout << "[INFO]: num chunks = " << num_chunks << endl;

    for (int i = 0; i < num_chunks; i++) {
        
        send(sock, send_it, sizeof(send_it), 0);
        read(sock, buffer, sizeof(buffer));
        
        memcpy(&chunks[i], &buffer[3], sizeof(chunk));

        // cout << "chunk " << i << " of " << num_chunks << endl;
        // cout << "  chunkID = " << chunks[i].chunkID << endl;
        // cout << "  storageNode = " << chunks[i].storageNode << endl;
        // cout << "  size = " << chunks[i].size << endl;
        // cout << "  sequenceID = " << chunks[i].sequenceID << endl;
    }

    // cout << "[INFO]: successfully read" << endl;

    // 6. confirm success and close the connection
    send(sock, send_it, sizeof(send_it), 0);
    close(sock);
    

    if (send_it[0] == 1) {

        transferFileToCloud(chunks);
    }
    else if (send_it[0] == 2) {

        retriveFileFromCloud(chunks);
    }

    exit(0);
}


