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
        nodeCapacityIndex[i]= capacity;//defaultCa`pacity; //In MB/GB as per the assumption , TODO :: TBD
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


void RoutingNode::listener() {

    int port = 8080;
    struct sockaddr_in addr; 
    int server, client, addr_len = sizeof(addr); 
    char buffer[256] = {0}; 
    char send_it[256] = {0};
       
    if ((server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == 0) { 
        cerr << "[ERROR]: socket creation failed" << endl; 
        exit(EXIT_FAILURE); 
    } 
       
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

        cout << "[INFO]: listening..." << endl;
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

        // 2. for now the header is unimportant, we must search
        int length = (int) buffer[3];

        // I guess checking if file exists is not ready, so 
        // for now always return true
        send_it[1] = 5;

        send(client, send_it, sizeof(send_it), 0);

        // 3. get the file size
        read(client, buffer, 256);

        // lots of hacking, we know what the int size will be
        // so don't bother looking at buffer[2]
        int file_size = 0;
        memcpy(&file_size, &buffer[3], sizeof(int));

        // dbg
        cout << "[INFO]: file size from client = " << file_size << endl;

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
        read(client, buffer, 256);
        
        vector<chunk> *chunks = generateChunkInfo((long) file_size);

        send_it[3] = (char) chunks->size();
        send(client, send_it, sizeof(send_it), 0);

        cout << "[INFO]: chunks made = " << chunks->size() << endl;
        // 6. pass the chunks to the client
        for (int i = 0; i < chunks->size(); i++) {

            cout << "[INFO]: sent chunk " << i << endl;
            memcpy(&send_it[3], &chunks->at(i), sizeof(chunk));

            // again, skipping the data size parameter, 
            // the more I write this the less it feels 
            // necessary

            read(client, buffer, 256);
            send(client, send_it, sizeof(send_it), 0);
        }

        // 7. all done, close client and free mem
        read(client, buffer, 256);

        cout << "[INFO]: cleaning up" << endl << endl;
        delete chunks;
        close(client); 
    }
}