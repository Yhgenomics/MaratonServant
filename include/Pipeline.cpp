#include "Pipeline.h"
#include "ExitCodeHandlerSet.h"

NS_SERVANT_BEGIN

void Pipeline::GetNextPipe()
{
   /* if ( test_i < 2 )
    {
        std::cout << "test i is "<< test_i << endl;
        test_i++;
        auto pipe = make_uptr( Pipe );
        pipe->DockerDaemon( "http://10.0.0.11:4243" );
        pipe->DockerImage( "cattest" );
        pipe->AddEnvironment( "t" , "2" );
        pipe->AddEnvironment( "refgen" , "hg19.fa" );
        pipe->AddPathBind( "/data/input/allfiletest/" , "/input/" );
        pipe->AddPathBind( "/data/output/" , "/output/" );
        pipe->AddPathBind( "/data/ref/" , "/ref/" );
        pipe->AddPathBind( "/dev/shm/" , "/dev/shm/" );
        pipe->SetPipeExit( NextPipe );
        AddPipe(std::move(pipe));
    }*/
}

void Pipeline::ParseFromMessage( uptr<MessageTaskDeliver> orignalMessage )
{
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
