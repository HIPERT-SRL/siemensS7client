#include <iostream>
#include <thread>
#include <chrono>

#include "snap7.h"

int Error;
unsigned char DB1[512];  // Our DB1
unsigned char DB2[128];  // Our DB2
unsigned char DB3[1024]; // Our DB3
unsigned char MB[2048];  

int main() {
    TS7Server *Server;
    Server = new TS7Server;

    Error=Server->Start();

    if (Error==0)
    {
       // Now the server is running ... wait a key to terminate
        getchar();
    }
    else
        printf("%s\n",SrvErrorText(Error).c_str());

    Server->RegisterArea(srvAreaDB,     // We are registering a DB
                         1,             // Its number is 1 (DB1)
                         &DB1,          // Its address
                         sizeof(DB1));  // Its size

    // Do the same for DB2 and DB3

    Server->RegisterArea(srvAreaDB, 2, &DB2, sizeof(DB2));
    Server->RegisterArea(srvAreaDB, 3, &DB3, sizeof(DB3));

    // Let’s share all Merkers from M0.0 to M2047.7

    Server->RegisterArea(srvAreaMK, 0, &MB, sizeof(MB));

 

}