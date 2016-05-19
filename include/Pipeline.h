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

#ifndef PIPELINE_H_
#define PIPELINE_H_

#include "ServantGloable.h"
#include "Pipe.h"
#include "MessageTaskDeliver.pb.h"
#include "MessageTaskUpdate.pb.h"
#include "MessageServantUpdate.pb.h"
#include "MessageHub.h"
#include <vector>
#include <string>
#include <memory>

NS_SERVANT_BEGIN

// @Description : Pipeline is given by a subtask from master, it contains multi number of
//                pipes. All pipes in one pipeline should be run one after another. 
// @Example     : Use ParseFromMessage to create a pipeline.
//                Use Run to start it. 
class Pipeline :public Singleton<Pipeline>
{
public:

    // Add one Pipe to pipeline
    // @pipe    : one Pipe need to be added.
    void AddPipe( uptr<Pipe> pipe );

    // Parse the pipeline informantion from a protobuf Message.
    // @orignalMessage : message from the Maraton Master
    void ParseFromMessage( uptr<MessageTaskDeliver> orignalMessage );

    // Start the pipeline
    void Run();

    // Run Next based on the exit Code from last pipe
    // @lastExitCode : Exit code of the one pipe before current one.
    // @note         : exit code is 0 before the first pipe run.
    void RunNext( const int& lastExitCode );

    // Called when pipeline finish
    void OnFinish();

    // Called when exception happens
    // @lastExitCode : Exit code of the one pipe before current one.
    // @note         : any non-zero exit code is consider as exception
    void OnException( const int& lastExitCode );

    // Getter for task root
    string TaskRoot()                  { return task_root_;   }

    // Getter for Main log name
    // Main log is the record for all subtasklist associated to a main task
    string MainLogName()               { return main_log_;    }

    // Getter for runtime log
    // runtime log is the log in one subtask
    string RuntimeLogName()            { return runtime_Log_; }

    // Getter and Setter for abort mark
    // @note : the abort mark in Docker Helper is independent and need to be set the same
    bool NeedAbort()                   { return abort_mark_ ; }
    void NeedAbort( const bool& value ) { abort_mark_ = value; DockerHelper::Instance()->NeedAbort( value ); }
 
    // Setter for docker daemon
    // @daemon  : The docker daemon in form http://127.0.0.1:1234
    void DockerDaemon( const string& daemon )
    { docker_daemon = daemon; }

protected:
    // Constructor
    Pipeline();

    // Desctrucotr
    ~Pipeline() {};

    // Initialization
    void Init();

    // Abort task
    void Abort();

private:

    // Check if a string contains valid content
    // @oneLine : one line from the output file.
    bool IsOutputLineValid( const string& oneLine );

    // Gathering all outputs informantion
    // @outputs   : The contianer's outputs files informations.
    bool GatherOutputInformation( vector<string>& outputs );

    string mkdir_        ;
    string task_root_    ;
    string data_path_    ;
    string task_id_      ;
    string original_id_  ;
    string task_path_    ;
    string input_file_   ;
    string output_file_  ;
    string subtask_list_ ;
    string docker_work_  ;
    string docker_data_  ;
    string docker_daemon ;
    string main_log_     ;
    string runtime_Log_  ;
    string main_path_    ;
    bool   abort_mark_   ; // use the Setter to set, no direct set to this value.
    uptr<Pipe> current_pipe_;

    vector<uptr<Pipe>>  pipe_list_;

    friend Singleton<Pipeline>;

};

NS_SERVANT_END

#endif // £¡PIPELINE_H_