#include "MRT.h"
#include "ServantGloable.h"
#include "MasterConnector.h"
#include "MessageHub.h"
#include "Pipe.h"
#include "Pipeline.h"
#include <iostream>
#include <string>

using namespace std;
using namespace MRT;
using namespace NS_SERVANT;

int main( int argc , char* argv[] )
{
    Protocal::MessageHub::Instance()->AddAllHandlers();

    //string ip   = string( argv[ 1 ] );
    //string port = string( argv[ 2 ] );
    
    while(true)
    {       
        cout << "try connect" << endl;
        //Maraton::Instance()->Regist( make_uptr( MasterConnector , ip , port ) );
        Maraton::Instance()->Regist( make_uptr( MasterConnector , "10.0.0.219" , 90 ) );
        Maraton::Instance()->Run();
    }
    return 0;   
}
