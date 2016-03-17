/***********************************************************************************
This file is part of Project for MaratonServant
For the latest info, see  https://github.com/Yhgenomics/MaratonServant.git

Copyright 2016 Yhgenomics

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
***********************************************************************************/

/***********************************************************************************
* Description   : Serial pipes make a pipeline.
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/3/8
* Modifed       : When      | Who       | What
***********************************************************************************/

#include "Pipeline.h"
#include "WorkManager.h"
#include "ExitCodeHandlerSet.h"
#include <fstream>
#include <iostream>
#include <string>

using std::string;

NS_SERVANT_BEGIN


// Add one Pipe to pipeline
// @pipe    : one Pipe need to be added.
void Pipeline::AddPipe( uptr<Pipe> pipe )
{
    pipe_list_.push_back( std::move( pipe ) );
}

// Parse the pipeline informantions from a protobuf Message.
// @orignalMessage : message from the Maraton Master
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

        pipe->AddPathBind( task_path_ , docker_work_ );
        pipe->AddPathBind( data_path_ , docker_data_ );
        
        pipe->SetPipeExit( NextPipe );

        for(auto param : item.parameters())
        {
            pipe->AddEnvironment( param );
        }

        AddPipe( std::move( pipe ) );
    } // end of for ( auto item : orignalMessage->pipeline().pipes() )
}

// Start the pipeline
void Pipeline::Run()
{
    RunNext( 0 );
}


// Run Next based on the exit Code from last pipe
// @lastExitCode : Exit code of the one pipe before current one.
// @note         : exit code is 0 before the first pipe run.
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

// Called when pipeline finish
void Pipeline::OnFinish()
{ 
    vector<string> outputs; 
    GatherOutputInformation( outputs );
    Protocal::MessageHub::Instance()->SendTaskUpdate( TaskStatus::kFinished , outputs );
    std::cout << "pipeline finished" << std::endl;

    WorkManager::Instance()->FinishWork();
}

// Called when exception happens
// @lastExitCode : Exit code of the one pipe before current one.
// @note         : any non-zero exit code is consider as exception
void Pipeline::OnException( const int & lastExitCode )
{
    Protocal::MessageHub::Instance()->SendTaskUpdate( TaskStatus::kTaskError );
    std::cout << "Exception happended code " << lastExitCode << std::endl;
}

// Check if a string contains valid content
// @oneLine : one line from the output file.
inline bool Pipeline::IsOutputLineValid( const string & oneLine )
{
    return (    oneLine != ""
             && oneLine != "\r"
             && oneLine != "\n"
             && oneLine != "\r\n"
             && oneLine != "\n\r" );
}

// Gathering all outputs informantion
// @outputs   : The contianer's outputs files informations.
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
    } //  end of  if ( fin )

    else
    {
        result = false;
    }

    return result;
}

NS_SERVANT_END
