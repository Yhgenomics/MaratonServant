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
    //auto pipe = make_uptr(Pipe);

    //auto t1 = make_uptr(Pipe);
    //
    //t1->DockerDaemon("http://10.0.0.11:4243");
    //t1->DockerImage("cattest");
    //t1->AddEnvironment("t","2");
    //t1->AddEnvironment("refgen","hg19.fa");
    ////t1->AddEnvironment("reads","small");
    //t1->AddPathBind("/data/input/allfiletest/","/input/");
    //t1->AddPathBind("/data/output/","/output/");
    //t1->AddPathBind("/data/ref/","/ref/");
    //t1->AddPathBind("/dev/shm/","/dev/shm/");
    //t1->SetPipeExit([&pp1](const int & exitCode)
    //{     
    //    pp1.RunNext(exitCode)
    //;});

    //pp1.AddPipe(std::move(t1));
   // Pipeline::Instance()->Run();

   /* vector<string> environment;
    vector<string> binds;

    environment.push_back( "t=2" );
    environment.push_back( "refgen=hg19.fa" );
    environment.push_back( "reads=small" );

    binds.push_back( "/data/input/:/input/" );
    binds.push_back( "/data/output/:/output/" );
    binds.push_back( "/data/ref/:/ref/" );
    binds.push_back( "/dev/shm/:/dev/shm/" );

    DockerHelper::Instance()->BindExitCodeHandler( testExitCodeHandler );
    DockerHelper::Instance()->Run( "http://10.0.0.11:4243" , "10.0.0.15:5000/cattest" , binds , environment );*/
    
   /* Maraton::Instance()->Run();
    system("pause");
    return 0;*/
    //string ip   = string( argv[ 1 ] );
    //string port = string( argv[ 2 ] );

    // add pipeline manager here
    

    
    while(true)
    {       
        cout << "try connect" << endl;
        //Maraton::instance()->regist( make_uptr( ExecutorConnector , ip , port ) );
        Maraton::Instance()->Regist( make_uptr( MasterConnector , "10.0.0.219" , 90 ) );
        Maraton::Instance()->Run();
    }
    return 0;   
}
