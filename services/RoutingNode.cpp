//
//  RoutingNode.cpp
//  NetDrive
//
//

#include "RoutingNode.hpp"

RoutingNode::RoutingNode(){
    totalStorageNodes = 3;//TODO : Need to make it data driven
    totalStorageNodesNotEmpty = totalStorageNodes;
    lastestChunkID = 0;
    minStorageCapacity = INT_MAX;
    registerDevices();
    
}

void RoutingNode::registerDevices(){
    cout<<"**** Device Registration ****"<<endl;
    int defaultCapacity=5; //TODO to be made more generic
    for (int i=0; i<totalStorageNodes; i++) {
        int capacity =defaultCapacity+(i%totalStorageNodes)+1;
        nodeCapacityIndex[i]= capacity;//defaultCa`pacity; //In MB/GB as per the assumption , TODO :: make data driven
        cout<<"Node["<<i<<"] default capacity:"<<nodeCapacityIndex[i]<<endl;
        totalRemainingStorageCapacity += capacity;
    }
    cout<<endl;
}

bool RoutingNode::canStore(long newFileSize){
    return (newFileSize <= totalRemainingStorageCapacity)? true:false;
}

//The module assumes that a file of the given size can be store in the storage cloud;
//i.e. it has been validated before using this module
vector<chunk>* RoutingNode::generateChunkInfo(long fileSize){
    unordered_map<int, long> newReservation;
    while(fileSize>0){
        long r = fileSize/totalStorageNodesNotEmpty;
        long blockSize = min(minStorageCapacity,(r==0?fileSize:r));
        for (int i=0; i<totalStorageNodes; i++) {
            if(nodeCapacityIndex[i] >= blockSize){
                newReservation[i] +=blockSize;
                nodeCapacityIndex[i] -=blockSize;
                totalRemainingStorageCapacity -=blockSize;
                fileSize -=blockSize;
                //if the remaining capacity of the node become 0 then totalStorageNodesNotEmpty would be reduced by 1
                if(nodeCapacityIndex[i] ==0 ){
                    totalStorageNodesNotEmpty--;
                }
            }
            //updating new minimum storage capacity
            if(nodeCapacityIndex[i] < minStorageCapacity && nodeCapacityIndex[i] >0){
                minStorageCapacity = nodeCapacityIndex[i];
            }
            if(fileSize ==0) break;
        }
    }
    
    //creating a list of chunks with the reserved capacities
    vector<chunk>* chunks = new vector<chunk>();
    for (int i=0; i<totalStorageNodes; i++) {
        if(newReservation[i]==0) continue;
        chunk *chnk = new chunk;
        if(!chnk){
            cout << "Memory allocation failed!!" <<endl;
            return nullptr;
        }
        chnk->storageNode = i;
        chnk->size = newReservation[i];
        chnk->sequenceID = i;
        chnk->chunkID = ++lastestChunkID;
        //adding the chunk to the list of chunks
        chunks->push_back(*chnk);
    }
    return chunks;
}

vector<chunk> RoutingNode::storeFile(string filename, long size){
    vector<chunk> chunks;
    if(canStore(size)){
        fileIndex[filename] = *generateChunkInfo(size);
        chunks= fileIndex[filename];
    }
    return chunks;
}

vector<chunk> RoutingNode::retrieveFile (string filename){
    return fileIndex[filename];
}

//TODO : Currently descoped : To be implement in future
bool RoutingNode::deleteFile(string filename){
    //TODO code here
    
    return true;
}


//getters

unordered_map<int,long> RoutingNode::getRemainingNodesCapacities(){
    return nodeCapacityIndex;
}

int RoutingNode::getTotalStorageNodes(){
    return totalStorageNodes;
}


long RoutingNode::getTotalRemainingStorageCapacity(){
    return totalRemainingStorageCapacity;
}


void RoutingNode::listener(int argc, const char * argv[]) {

    int port = 8080;
    struct sockaddr_in addr; 
    int server, client, addr_len = sizeof(addr); 
    char buffer[256] = {0}; 
    char send_it[256] = {0};
    vector<chunk> chunks; 
       
    if ((server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == 0) { 
        cerr << "[ERROR]: socket creation failed" << endl; 
        exit(EXIT_FAILURE); 
    } 
    
    int o = 1;
    setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &o, sizeof(o)); 

    addr.sin_family = AF_INET; 
    addr.sin_addr.s_addr = INADDR_ANY; 
    addr.sin_port = htons(port); 
       
    if (::bind(
            server, 
            (struct sockaddr *) &addr,
            sizeof(addr)
        ) < 0) { 

        cerr << "[ERROR]: failed binding to port" << endl;
        exit(EXIT_FAILURE); 
    } 
    if (listen(server, 3) < 0) {

        cerr << "[ERROR]: socket can't listen" << endl;
        exit(EXIT_FAILURE); 
    } 

    // set up listener
    for(;;) {

        cout << "[INFO]: listening..." << endl << endl;
        if ((client = accept(
                server, 
                (struct sockaddr *) &addr,  
                (socklen_t *) &addr_len
            )) < 0) { 
           
            cerr << "[ERROR]: client not accepted" << endl;
            exit(EXIT_FAILURE); 
        } 

        // 1. get client request for file storage
        read(client, buffer, 256);

        send_it[0] = buffer[0];

        int file_len = (int) buffer[2];
        char *file = (char *) malloc(sizeof(char) * (file_len + 1));

        memcpy(file, &buffer[3], file_len);
        file[file_len] = '\0';

        cout << "[INFO]: file name = " << file << endl;
        cout << "[INFO]: filename len = " << file_len << endl;

        // 2.0 check if the file exists or not
        int length = (int) buffer[3];
        bool file_exists = (fileIndex.find(file) != fileIndex.end());

       
        // 2.1 let client know file exists
        send_it[1] = file_exists ? 3 : 5;
        send(client, send_it, sizeof(send_it), 0);

        if(send_it[0] == 1) {

            /**
             * STORE FILE FUNCTIONALITY
             *
             * for now, we'll just keep the 2 fncts in an if stmt,
             * the next step would be to make the sockets member vars
             * and call a send() and retrieve() function outside of 
             * the listener
             **/

            // 2.2 exit if file exists and it's a store
            if (file_exists) continue;

            // 3.0 get the file size
            read(client, buffer, 256);

            // 3.1 lots of hacking, we know what the int size will be
            // so don't bother looking at buffer[2]

            int file_size = 0;
            memcpy(&file_size, &buffer[3], sizeof(int));

            // dbg
            cout << "[INFO]: file size from client = " << file_size << endl;
            cout << "[INFO]: remaining storage = " << totalRemainingStorageCapacity << endl;

            for (int i=0; i<totalStorageNodes; i++) {
                cout <<"[INFO]: node " << i << " capacity = " <<  nodeCapacityIndex[i] << endl;
            }

            // 4. check if we can hold the file;
            if (! canStore((long) file_size)) {

                send_it[1] = 4;
                cerr << "[ERROR]: storage nodes full" << endl;
                close(client); 
                continue;
            }

            send_it[1] = 5;
            send(client, send_it, sizeof(send_it), 0);

            // 5. client ready, send num chunks
            chunks = storeFile(file, (long) file_size);
            send_it[3] = (char) chunks.size();
        }
        else if (send_it[0] == 2) {
            
            /**
             * RETRIEVE FILE FUNCTIONALITY
             * 
             * Again, this should be in its own file sometime
             * in the future, however issues with scope make moving
             * this to a clearer implementation is difficult 
             * right now
             **/

            // retry if file doesn't exist
            cout << "[INFO]: file not found on search" << endl;
            if (! file_exists) continue;

            chunks = fileIndex[file];
            send_it[3] = (char) chunks.size();
        }
       
        /**
         * COMBINED FUNCTIONALITY
         * 
         * In the end, both send and store just send chunks back 
         * to the client, so we'll reuse the code for both of 
         * these cases.
         **/

        read(client, buffer, 256);
        send(client, send_it, sizeof(send_it), 0);

        cout << "[INFO]: chunks made = " << chunks.size() << endl;
        // 6. pass the chunks to the client
        for (int i = 0; i < chunks.size(); i++) {

            cout << "[INFO]: sent chunk " << i << endl;
            memcpy(&send_it[3], &chunks.at(i), sizeof(chunk));

            // again, skipping the data size parameter, 
            // the more I write this the less it feels 
            // necessary

            read(client, buffer, 256);
            send(client, send_it, sizeof(send_it), 0);
        }

        // 7. all done, close client and free mem
        read(client, buffer, 256);
        
        cout << "[INFO]: cleaning up" << endl << endl;
        close(client); 
    }
}
