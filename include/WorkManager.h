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

    // Getter and Setter of Servant status
    ServantStatus::Code SelfStatus()                    { return self_status_ ; }
    void SelfStatus( const ServantStatus::Code& value ) { self_status_ = value; }

    // Getter and Setter of Task status
    TaskStatus::Code WorkSataus()                       { return work_status_;  }
    void WorkStatue( const TaskStatus::Code& value )    { work_status_ = value; }

    // Getter and Setter of Servant ID
    string ServantID()                                  { return servant_id_;   }
    void ServantID( string id )                         { servant_id_ = id;     }

    // Add one pipeline from a message
    // @message : message from the Maraton Master
    void AddPipeline( uptr<MessageTaskDeliver> message );

    // Start the task
    void StartWork();

    // Finish the task
    void FinishWork();

    // Abort the task
    void AbortWork();

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

    // update the log of current running subtask
    void SendLogUpdate();

protected:

    // Constructor
    WorkManager();

    // Desctructor
    ~WorkManager();

    // initialization
    void Init();

private:

    ServantStatus::Code self_status_ = ServantStatus::kUnknown;
    TaskStatus::Code    work_status_ = TaskStatus::kUnknown;
    string              servant_id_;
    string              main_task_id_;
    string              subtask_id_;
    string              pipeline_id_;
    string              core_;
    string              memory_;

    // Pointer to a SyncWorker should be created when work is starting
    // and be stopped when the work is finishing.
    // @note : No delete on this pointer is allowed after the constrains from the Maraton Framework.
    MRT::SyncWorker*    log_sender_;

    friend MRT::Singleton<WorkManager>;

};

NS_SERVANT_END

#endif // !WORK_MANAGER_H_