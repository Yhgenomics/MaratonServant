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
//void Pipeline::AddPipe( uptr<Pipe> pipe )
void Pipeline::AddPipe( sptr<Pipe> pipe )
{
    pipe_list_.push_back( move_ptr( pipe ) );
}

// Parse the pipeline informantion from a protobuf Message.
// @orignalMessage : message from the Maraton Master
void Pipeline::ParseFromMessage( uptr<MessageTaskDeliver> orignalMessage )
{
    current_pipe_ = nullptr;
    NeedAbort( false );// this will set the DockerHelper's abort mark
    pipe_list_.clear();

    // Refresh task info
    task_id_.clear();
    original_id_.clear();
    main_path_.clear();
    task_path_.clear();

    task_id_     = orignalMessage->id();
    original_id_ = orignalMessage->originalid();
    main_path_   = task_root_ + original_id_ + "/";
    task_path_   = task_root_ + original_id_ + "/" + task_id_ + "/";

    // Make the main task path and the subtask path
    system( ( mkdir_ + main_path_ ).c_str() );
    system( ( mkdir_ + task_path_ ).c_str() );

    // Append to subtask list
    std::ofstream subtaskFout( main_path_ + subtask_list_ , std::ios::app );

    subtaskFout << task_id_ <<  std::endl;
    subtaskFout.close();

    // Make Input File
    std::ofstream fout( task_path_ + input_file_ );

    for ( auto file : orignalMessage->input() )
    {
        fout << file << std::endl;
    }

    fout.close();

    // Add others info to pipeline
    for ( auto item : orignalMessage->pipeline().pipes() )
    {
        //auto pipe = make_uptr( Pipe );
        auto pipe = make_sptr( Pipe );

        pipe->DockerDaemon( docker_daemon );
        //Logger::Log( "Rececived image is [%]" , item.executor() );
        pipe->DockerImage( item.executor() );
        //Logger::Log( "Store image is [%]" , pipe->DockerImage() );

        pipe->AddPathBind( task_path_ , docker_work_ );
        pipe->AddPathBind( data_path_ , docker_data_ );

        pipe->SetPipeExit( NextPipe );

        for(auto param : item.parameters())
        {
            pipe->AddEnvironment( param );
        }
        Logger::Log("one pipe parsing from the msg");
        pipe->ShowAll();
        AddPipe( move_ptr( pipe ) );
    } // end of for ( auto item : orignalMessage->pipeline().pipes() )
}

// Start the pipeline
void Pipeline::Run()
{
    Logger::Log("Pipeline Run start");
    RunNext( 0 );
}

// Run Next based on the exit Code from last pipe
// @lastExitCode : Exit code of the one pipe before current one.
// @note         : exit code is 0 before the first pipe run.
void Pipeline::RunNext( const int & lastExitCode )
{
    // clean last pipe first
    if ( nullptr != current_pipe_ )
    {
        auto itr = pipe_list_.begin();

        while ( itr != pipe_list_.end() )
        {
            if ( ( *itr ).get() == current_pipe_.get() )
            {
                itr = pipe_list_.erase( itr );
                Logger::Log( "Remove last pipe " );
                break;
            }
            else
            {
                itr++;
            }
        }
    }

    Logger::Log( "Try run Next Pipe" );

    // Abort is prior than any exception
    // abort will cause exit 137
    if ( abort_mark_ )
        Abort();

    else  if ( lastExitCode != 0 )
        OnException( lastExitCode );

    else if ( pipe_list_.size() == 0 )
        OnFinish();

    else
    {
        current_pipe_ = *(pipe_list_.begin());
        //current_pipe_ = std::move( pipe_list_[ 0 ] );
        //pipe_list_.erase( pipe_list_.begin() );
        current_pipe_->Run();
    }
}

// Called when pipeline finish
void Pipeline::OnFinish()
{
    vector<string> outputs;
    GatherOutputInformation( outputs );
    Protocal::MessageHub::Instance()->SendTaskUpdate( TaskStatus::kFinished , outputs );
    Logger::Log( "Pipeline Finished " );

    WorkManager::Instance()->FinishWork();
}

// Called when exception happens
// @lastExitCode : Exit code of the one pipe before current one.
// @note         : any non-zero exit code is consider as exception
void Pipeline::OnException( const int & lastExitCode )
{
    Protocal::MessageHub::Instance()->SendTaskUpdate( TaskStatus::kError );

    Logger::Error("Exception happended code : %",lastExitCode);
    WorkManager::Instance()->FinishWork();
}

// Abort task
void Pipeline::Abort()
{
    Protocal::MessageHub::Instance()->SendTaskUpdate( TaskStatus::kStopped );
    Logger::Log( "Pipeline Aborted " );

    WorkManager::Instance()->FinishWork();
}

// Constructor
Pipeline::Pipeline()
{
    Init();
}

// Initialization
void Pipeline::Init()
{
    mkdir_        = "mkdir ";
    task_root_    = "/data/mrttask/";
    data_path_    = "/data/ref/";
    task_id_      = "";
    original_id_  = "";
    task_path_    = "";
    input_file_   = "input.mrt";
    output_file_  = "output.mrt";
    subtask_list_ = "subtasklist.log";
    docker_work_  = "/work/";
    docker_data_  = "/data/";
    docker_daemon = "http://127.0.0.1:4243";
    main_log_     = "subtasklist.log";
    runtime_Log_  = "runtime.log";
    main_path_    = "";
    abort_mark_   = false;
    pipe_list_.clear();
    current_pipe_ = nullptr;
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
