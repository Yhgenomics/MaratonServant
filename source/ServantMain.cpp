#include "MRT.h"
#include "ServantGloable.h"
#include "MasterConnector.h"
#include "MessageHub.h"
#include "Pipe.h"
#include "Pipeline.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace MRT;
using namespace NS_SERVANT;

int main( int argc , char* argv[] )
{
    Protocal::MessageHub::Instance()->AddAllHandlers();

    //std::string  ip   = string( argv[ 1 ] );
    //std::sstream portStream;
    //portStream << string( argv[2] );
    //int prot;
    //portStream >> prot;

    // check input parameters here

    while(true)
    {
        std::cout << "try connect" << std::endl;

        //Maraton::Instance()->Regist( make_uptr( MasterConnector , ip , port ) );
        Maraton::Instance()->Regist( make_uptr( MasterConnector , "10.0.0.219" , 90 ) );
        Maraton::Instance()->Run();
    }
    return 0;
}
