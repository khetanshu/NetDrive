//
//  ClientNode.cpp
//  NetDrive
//
//

#include "ClientNode.hpp"

vector<chunk> ClientNode::splitFile(string fileName, vector<chunk>& chunks)
{
    
    vector<chunk> ck;//TODOD
    
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
    
    
    // //  splitting file into chunks
    // for(auto &size: sizes)
    // {
    //     try
    //     {
    //         ofstream o_file(fileName+"-"+to_string(i++));
    //         o_file << buffer.substr(peek, size);
    //         o_file.close();
    //         peek+=size;
    //         cout << endl;
    //     }
    //     catch (exception const& e)
    //     {
    //         cerr << "Error ocurred while writing file!\n" << e.what() << endl;
    //     }
    // }
    //TODO
    return chunks;
    
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
    
    int port = 8080;
    char ip[] = "127.0.0.1";
    struct sockaddr_in addr; 
    int sock = 0, valread; 
    struct sockaddr_in server_addr; 
    char buffer[256] = {0};
    char send_it[256] = {0};

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
     * PACKET HEADER
     *
     * packet[0] = 1 - store file
     * packet[0] = 2 - retrieve file

     * packet[0] != {1,2} - error, undefined request
     **/

    send_it[0] = 1;
    
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

     send_it[2] = 0;

    // 1. send request to server with filename
    send(sock, send_it, sizeof(send_it), 0);
    
    // 2. check if the file exists
    read(sock, buffer, 256);

    if (buffer[1] == 3) {
        cerr << "[ERROR]: file exists" << endl;
        exit(EXIT_FAILURE);
    }

    // 3. send the file size
    send_it[1] = 2;
    send_it[2] = 4;

    // TODO: get data size dynamically
    int data_size = 4;
    memcpy(&send_it[3], &data_size, sizeof(int));

    send(sock, send_it, sizeof(send_it), 0);

    // 4. check if we the file fits in storage
    read(sock, buffer, 256);

    if (buffer[1] == 4) {
        cerr << "[ERROR]: cloud full" << endl;
        exit(EXIT_FAILURE);
    }

    // 4. fize size ok, we're ready for chunk data
    send_it[1] = 5;
    
    send(sock, send_it, sizeof(send_it), 0);

    // 5. read and parse chunk data
    read(sock, buffer, 256);

    int num_chunks = (int) buffer[3];

    vector<chunk> chunks;
    chunks.reserve(num_chunks);

    cout << "[INFO]: num chunks = " << num_chunks << endl;

    for (int i = 0; i < num_chunks; i++) {

        send(sock, send_it, sizeof(send_it), 0);
        read(sock, buffer, 256);

        memcpy(&chunks[i], &buffer[3], sizeof(chunk));

        cout << "chunk " << i << " of " << num_chunks << endl;
        cout << "  chunkID = " << chunks[i].chunkID << endl;
        cout << "  storageNode = " << chunks[i].storageNode << endl;
        cout << "  size = " << chunks[i].size << endl;
        cout << "  sequenceID = " << chunks[i].sequenceID << endl;
    }

    cout << "[INFO]: successfully read" << endl;

    // 6. confirm success and close the connection
    send(sock, send_it, sizeof(send_it), 0);
    close(sock);
}
