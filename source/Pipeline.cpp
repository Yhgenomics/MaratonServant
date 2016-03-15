#include "Pipeline.h"
#include "ExitCodeHandlerSet.h"
#include <fstream>
#include <iostream>
#include <string>

using std::string;

NS_SERVANT_BEGIN

void Pipeline::ParseFromMessage( uptr<MessageTaskDeliver> orignalMessage )
{
    task_id_ = orignalMessage->originalid();

    system( (mkdir_ + task_root_ + task_id_).c_str() );
    std::ofstream fout( task_root_ + task_id_ + input_file_ );

    for ( auto file : orignalMessage->input() )
    {
        std::cout << file << std::endl;
        fout << file << std::endl;
    }
    fout.close();

    for ( auto item : orignalMessage->pipeline().pipes() )
    {
        auto pipe = make_uptr( Pipe );
        pipe->DockerDaemon( "http://10.0.0.70:4243" );
        pipe->DockerImage( item.executor() );
        //pipe->AddEnvironment( "t" , "2" );
        //pipe->AddEnvironment( "refgen" , "hg19.fa" );
        for(auto param : item.parameters())
        {
            pipe->AddEnvironment( param );
        }
        pipe->AddPathBind( task_root_+task_id_+"/" , "/work/" );
        //pipe->AddPathBind( "/data/output/" , "/output/" );
        pipe->AddPathBind( data_root_ , "/data/" );
        //pipe->AddPathBind( "/dev/shm/" , "/dev/shm/" );
        pipe->SetPipeExit( NextPipe );
        AddPipe(std::move(pipe));
    }
    //for( auto item: orignalMessage->)
    //pipe_list_[0]->AddEnvironment()
}

void Pipeline::OnFinish()
{ 
    auto msg    = make_uptr( MessageTaskUpdate );
    msg->set_status( scast<int>( TaskStatus::kFinished ) );
    std::ifstream fin;
    fin.open( task_root_ + task_id_ + output_file_ );

    std::cout << "[DEBUG ONLY]print output.mrt" << std::endl;
    if ( fin )
    {
        while ( !fin.eof() )
        {
            std::string oneLine;
            fin >> oneLine;
            if(   oneLine != ""
               && oneLine != "\r"
               && oneLine != "\n"
               && oneLine != "\r\n"
               && oneLine != "\n\r" )
            msg->add_output( oneLine );
        }
        fin.close();
    }

    auto master = Protocal::MessageHub::Instance()->Master();
    master->SendOut( move_ptr( msg ) );
    std::cout << "pipeline finished" << endl;

    auto msg2    = make_uptr( MessageServantUpdate );
    msg2->set_status( 3 );
    master->SendOut( move_ptr( msg2 ) );
    std::cout << "stand by" << endl;
}


NS_SERVANT_END
