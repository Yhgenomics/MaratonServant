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
* Description   : Manage the work on servant.
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/3/7
* Modifed       : When      | Who       | What
***********************************************************************************/

#ifndef WORK_MANAGER_H_
#define WORK_MANAGER_H_

#include "ServantGloable.h"
#include "MessageTaskDeliver.pb.h"
#include "MessageServantUpdate.pb.h"
#include "Pipeline.h"
#include <string>

NS_SERVANT_BEGIN

using std::string;

// @Description : Manage the work status on a servant.            
// @Example     : Used in message handler for task delivering.               
//                {
//                    NS_SERVANT::WorkManager::Instance()->AddPipeline( move_ptr( msg ) );
//                    NS_SERVANT::WorkManager::Instance()->StartWork();
//                }                
class WorkManager :public MRT::Singleton<WorkManager>
{
public:

    // Constructor
    WorkManager();

    // Getter and Setter of Servant status
    ServantStatus::Code SelfStatus()                    { return self_status_ ; }
    void SelfStatus( const ServantStatus::Code& value ) { self_status_ = value; }

    // Getter and Setter of Task status
    TaskStatus::Code WorkSataus()                       { return work_status_;  }
    void WorkStatue( const TaskStatus::Code& value )    { work_status_ = value; }

    // Add one pipeline from a message
    // @message : message from the Maraton Master
    void AddPipeline( uptr<MessageTaskDeliver> message );

    // Start the task
    void StartWork();

    // Finish the task
    void FinishWork();

    // Return Current Task ID
    string MainTaskID() { return main_task_id_; }

    // Return Subtask ID
    string SubtaskID()  { return subtask_id_;   }

    // Return PipelineID
    string PipelineID() { return pipeline_id_;  }

    // Return the Core number of CPUs
    string Core()       { return core_;         }

    // Return the memory Size
    string Memory()     { return memory_;       }

    // Report self status to master
    void ReportSelfStatus();

    // Gather all exsit logs for a main(original) task.
    // Return true and put all logs in JSON string
    // Return false if the task is not running at this servant
    // @maintaskID : ID of the main(original) task.
    bool GatherTaskLog( const string& maintaskID,
                        string& allLogContent );

    // Get a copy of current log file's content
    // Return true and put the content in the third's parameters
    // Return false when the log file doesn't exsit.
    // @maintaskID : ID of the main(original) task
    // @subtaskID  : ID of a subtask
    bool GetSubtaskLog( const string& maintaskID,
                        const string& subtaskID,
                        string& logContent)

private:

    ServantStatus::Code self_status_ = ServantStatus::kUnknown;
    TaskStatus::Code    work_status_ = TaskStatus::kUnknown;
    string              main_task_id_;
    string              subtask_id_;
    string              pipeline_id_;
    string              core_;
    string              memory_;

    friend MRT::Singleton<WorkManager>;

};

NS_SERVANT_END

#endif // !WORK_MANAGER_H_