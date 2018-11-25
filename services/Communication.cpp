//
//  Communication.cpp
//  NetDrive
//
//

#include "Communication.hpp"


void Communication::listener(int argc, const char * argv[]) {
    cerr << "[ERROR] no inheritance" << endl;
}

Communication::Communication() {
    
    return;
}

int Communication::sendFile(string hostssh, string filename, string destPath){
    //Format of :: command = "scp ~/test.txt scu:~/OS_Project/";
    string command = "scp " + filename + " " + hostssh + ":" + destPath;
    return system(command.c_str());
}

int Communication::retreiveFile(string hostssh, string filename, string destPath){
    //Format of :: command = "scp ~/test.txt scu:~/OS_Project/";
    string command = "scp " + hostssh + ":"+ filename  + " " + destPath;
    cout<<command;
    return system(command.c_str());
}

