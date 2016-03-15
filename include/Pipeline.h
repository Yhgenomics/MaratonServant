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

    // Task Status.
    enum TaskStatus
    {
        kUnknow = 0 ,
        kPending,
        kRunning,
        kFinished,
        kStopped,
        kError
    };

    // Add one Pipe to pipeline
    void  AddPipe( uptr<Pipe> pipe )
    {
        pipe_list_.push_back( std::move( pipe ) );
    }

    // Parse the pipeline informantions from a protobuf Message.
    void ParseFromMessage( uptr<MessageTaskDeliver> orignalMessage );

    // Start the pipeline
    void Run();

    // Run Next based on the exit Code from last pipe
    // @note    : exit code is 0 before the first pipe run.
    void RunNext( const int& lastExitCode );

    // Called when pipeline finish
    void OnFinish();

    // Called when exception happens
    // @note    : any non-zero exit code is consider as exception
    void OnException( const int& lastExitCode );

private:

    string mkdir_       = "mkdir ";
    string task_root_   = "/data/mrttask/";   
    string data_path_   = "/data/ref/";
    string task_id_     = "";
    string task_path_   = "";
    string input_file_  = "input.mrt";
    string output_file_ = "output.mrt";
    vector<uptr<Pipe>>  pipe_list_;
    friend Singleton<Pipeline>;
};


NS_SERVANT_END

#endif // £¡PIPELINE_H_