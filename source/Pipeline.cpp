#include "Pipeline.h"
#include "ExitCodeHandlerSet.h"
#include <fstream>
#include <iostream>

NS_SERVANT_BEGIN

void Pipeline::ParseFromMessage( uptr<MessageTaskDeliver> orignalMessage )
{
    std::ofstream fout("/data/input/allfiletest/input.mrt");

    for ( auto file : orignalMessage->input() )
    {
        std::cout << file << std::endl;
        fout << file << std::endl;
    }
    fout.close();

    for ( auto item : orignalMessage->pipeline().pipes() )
    {
        auto pipe = make_uptr( Pipe );
        pipe->DockerDaemon( "http://10.0.0.11:4243" );
        pipe->DockerImage( item.executor() );
        //pipe->AddEnvironment( "t" , "2" );
        //pipe->AddEnvironment( "refgen" , "hg19.fa" );
        for(auto param : item.parameters())
        {
            pipe->AddEnvironment( param );
        }
        pipe->AddPathBind( "/data/input/allfiletest/" , "/work/" );
        //pipe->AddPathBind( "/data/output/" , "/output/" );
        pipe->AddPathBind( "/data/ref/" , "/data/" );
        //pipe->AddPathBind( "/dev/shm/" , "/dev/shm/" );
        pipe->SetPipeExit( NextPipe );
        AddPipe(std::move(pipe));
    }
    //for( auto item: orignalMessage->)
    //pipe_list_[0]->AddEnvironment()
}


NS_SERVANT_END
