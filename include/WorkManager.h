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

class WorkManager :public MRT::Singleton<WorkManager>
{
public:
    //Task Status.
    enum TaskStatus
    {
        kTaskUnknow = 0 ,
        kPending,
        kRunning,
        kFinished,
        kStopped,
        kTaskError
    };

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
    
    ServantStatus SelfStatus()             { return self_status_ ; }
    void SelfStatus( ServantStatus value ) { self_status_ = value; }

    TaskStatus WorkSataus()                { return work_status_;  }
    void WorkStatue( TaskStatus value )    { work_status_ = value; }

    void AddPipeline(uptr<MessageTaskDeliver> message)
    {
       // for(auto onePipe : msg )
        task_id_     = message->originalid();
        pipeline_id_ = message->pipeline().id();
        core_        = "8";
        memory_      = "32000";
        Pipeline::Instance()->ParseFromMessage( move_ptr( message ) );
    }

    void StartWork()
    {
        cout << "Task ID " << task_id_ << " start "<< endl;

        auto master = Protocal::MessageHub::Instance()->Master();
        auto msg    = make_uptr( MessageServantUpdate );
        msg->set_status( ServantStatus::kWorking );
        master->SendOut( move_ptr( msg ) );
        Pipeline::Instance()->Run();
    }

    void FinishWork()
    {
        auto master = Protocal::MessageHub::Instance()->Master();
        auto msg    = make_uptr( MessageServantUpdate );
        msg->set_status( ServantStatus::kStandby );
        master->SendOut( move_ptr( msg ) );
    }

    string TaskID()     { return task_id_;     }
    string PipelineID() { return pipeline_id_; }
    string Core()       { return core_;        }
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