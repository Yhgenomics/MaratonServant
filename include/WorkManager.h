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
* Description   : Manager the work on servant.
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/3/7
* Modifed       : When      | Who       | What
***********************************************************************************/

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

    // Task status
    enum TaskStatus
    {
        kTaskUnknow = 0 ,
        kPending,
        kRunning,
        kFinished,
        kStopped,
        kTaskError
    };

    // Servant status
    enum ServantStatus
    {
        kUnknow              = 0 ,
        kBooting             = 1 ,
        kSelfTesting         = 2 ,
        kStandby             = 3 ,
        kError               = 4 ,
        kWorking             = 5 ,
        kException           = 20
    };
    
    // Getter and Setter of Servant status
    ServantStatus SelfStatus()             { return self_status_ ; }
    void SelfStatus( ServantStatus value ) { self_status_ = value; }

    // Getter and Setter of Task status
    TaskStatus WorkSataus()                { return work_status_;  }
    void WorkStatue( TaskStatus value )    { work_status_ = value; }

    // Add one pipeline from a message
    void AddPipeline( uptr<MessageTaskDeliver> message );

    // Start the task
    void StartWork();

    // Finish the task
    void FinishWork();

    // Return Current Task ID
    string TaskID()     { return task_id_;     }

    // Return PipelineID
    string PipelineID() { return pipeline_id_; }

    // Return the Core number of CPUs
    string Core()       { return core_;        }

    // Return the memory Size
    string Memory()     { return memory_;      }

private:

    ServantStatus self_status_ = ServantStatus::kUnknow;
    TaskStatus    work_status_ = TaskStatus::kTaskUnknow;
    string        task_id_;
    string        pipeline_id_;
    string        core_;
    string        memory_;
    friend MRT::Singleton<WorkManager>;

};

NS_SERVANT_END