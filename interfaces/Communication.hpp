//
//  communication.hpp
//  NetDrive
//
//

#ifndef Communication_hpp
#define Communication_hpp

#include <stdio.h>
#include "Types.hpp"

class Communication{

private:
	packet p;

protected:
    void send();
    void receive();
    void parse();
    
public:
    Communication();
    void init();
};


#endif /* Communication_hpp */
