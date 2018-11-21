//
//  Communication.cpp
//  NetDrive
//
//

#include "Communication.hpp"
#include "Types.hpp"

using namespace std;

void Communication::listener() {
    cerr << "" << endl;
}

Communication::Communication() {

	return;
}

void Communication::server(int port) {

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

    // HTTP-esque: open and close connection 
    // on each request
    for(;;) {

    	if ((client = accept(
	    		server, 
	    		(struct sockaddr *) &addr,  
	            (socklen_t *) &addr_len
	        )) < 0) { 
	       
	        cerr << "[ERROR]: client not accepted" << endl;
	        exit(EXIT_FAILURE); 
	    } 

    	read(client, buffer, 256);
    	
    	// TODO make more clear parsing function
    	int len = 1;
    	char *p = &send_it[3];
		chunk *chunks = new chunk[len];

    	switch(buffer[0]) {
    		case 1:
    			len = (int) buffer[2];
    			 
    			for (int i = 0; i < len; i++) {
    				
    				// I doubt there will be > 256 storage nodes
    				// in the near future. so we'll just take 1 char
    				chunks[i].storageNode = (int) *(p++);

    				// serialize int from byte array.
    				chunks[i].chunkID = 2;

    					
    			}
		    	break;
		    case 2:
		    	send_it[0] = '2';
		    	send_it[1] = '2';
		    	send_it[2] = '0';
		    	break;
    	}
        send(client, send_it, sizeof(send_it), 0);
    	close(client); 
    }
}

void Communication::client(int port, char const *ip) {


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

    // TODO send proper data
    send_it[0] = 1;
    send_it[1] = 1;
    send_it[2] = 0;
    send(sock, send_it, sizeof(send_it), 0);
    read(sock, buffer, 256);
    cout << buffer << endl; 

    close(sock);
}