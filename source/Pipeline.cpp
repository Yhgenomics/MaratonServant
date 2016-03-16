#include "Pipeline.h"
#include "WorkManager.h"
#include "ExitCodeHandlerSet.h"
#include <fstream>
#include <iostream>
#include <string>

using std::string;

NS_SERVANT_BEGIN

void Pipeline::ParseFromMessage( uptr<MessageTaskDeliver> orignalMessage )
{
    task_id_   = orignalMessage->id();
    task_path_ = task_root_ + task_id_ + "/";

    system( (mkdir_ + task_path_).c_str() );
    std::ofstream fout( task_path_ + input_file_ );

    for ( auto file : orignalMessage->input() )
    {
        std::cout << file << std::endl;
        fout << file << std::endl;
    }
    fout.close();

    for ( auto item : orignalMessage->pipeline().pipes() )
    {
        auto pipe = make_uptr( Pipe );
        pipe->DockerDaemon( docker_daemon );
        pipe->DockerImage( item.executor() );

        for(auto param : item.parameters())
        {
            pipe->AddEnvironment( param );
        }

        pipe->AddPathBind( task_path_ , docker_work_ );

        pipe->AddPathBind( data_path_ , docker_data_ );

        pipe->SetPipeExit( NextPipe );
        AddPipe( std::move( pipe ) );
    }

}

// Start the pipeline
void Pipeline::Run()
{
    RunNext( 0 );
}


// Run Next based on the exit Code from last pipe
// @note    : exit code is 0 before the first pipe run.
void Pipeline::RunNext( const int & lastExitCode )
{
    if ( lastExitCode != 0 )
        OnException( lastExitCode );

    if ( pipe_list_.size() == 0 )
        OnFinish();
    else
    {
        auto currentPipe = std::move( pipe_list_[ 0 ] );
        pipe_list_.erase( pipe_list_.begin() );
        currentPipe->Run();
    }
}

void Pipeline::OnFinish()
{ 
    vector<string> outputs; 
    GatherOutputInformation( outputs );
    Protocal::MessageHub::Instance()->SendTaskUpdate( TaskStatus::kFinished , outputs );
    std::cout << "pipeline finished" << std::endl;

    WorkManager::Instance()->FinishWork();
}

void Pipeline::OnException( const int & lastExitCode )
{
    Protocal::MessageHub::Instance()->SendTaskUpdate( TaskStatus::kTaskError );
    std::cout << "Exception happended code " << lastExitCode << std::endl;
}

// Check if a string contains valid content
inline bool Pipeline::IsOutputLineValid( const string & oneLine )
{
    return (    oneLine != ""
             && oneLine != "\r"
             && oneLine != "\n"
             && oneLine != "\r\n"
             && oneLine != "\n\r" );
}

// Gathering all outputs informantion
// @param   : outputs is the contianer gathering outputs informations.
bool Pipeline::GatherOutputInformation( vector<string>& outputs )
{
    bool result = false;
    std::ifstream fin;
    fin.open( task_path_ + output_file_ );

    if ( fin )
    {
        while ( !fin.eof() )
        {
            std::string oneLine;
            fin >> oneLine;
            if ( IsOutputLineValid( oneLine ) )
            {
                outputs.push_back( oneLine );
            }
        }
        fin.close();
        result = true;
    }
    else
    {
        result = false;
    }
    return result;
}

NS_SERVANT_END
