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

#include "WorkManager.h"
#include "MRT.h"
#include "json.hpp"
#include <sstream>
#include <string>

NS_SERVANT_BEGIN

// Constructor
WorkManager::WorkManager()
{
    log_sender_  = nullptr;
    self_status_ = ServantStatus::kStandby;

    std::stringstream strStream;

    strStream << MRT::SystemInfo::CPUNum();
    strStream >> core_;
    strStream.clear();

    strStream << (MRT::SystemInfo::MemoryFreeSize() / MEM_SIZE_FACTOR_MB );
    strStream >> memory_;
}

// Add one pipeline from a message
// @message : message from the Maraton Master
void WorkManager::AddPipeline( uptr<MessageTaskDeliver> message )
{
    main_task_id_.clear();
    subtask_id_.clear();
    pipeline_id_.clear();

    main_task_id_ = GetCopiedString(message->originalid());
    subtask_id_   = GetCopiedString(message->id());
    pipeline_id_  = GetCopiedString(message->pipeline().id());

    Pipeline::Instance()->ParseFromMessage( move_ptr( message ) );
}

// Start the task
void WorkManager::StartWork()
{
    Logger::Log( "Task ID [ % ] Subtask ID [ % ] Start." , main_task_id_ , subtask_id_ );
    self_status_ = ServantStatus::kWorking;

    Logger::Log("Create Log Sender! begin");
    log_sender_  = MRT::SyncWorker::Create( LOG_PERIOD ,
                             [ this ] ( MRT::SyncWorker* te )
                             {
                                 Logger::Log( "Enter loop log sender" );
                                 SendLogUpdate();
                                 return false;
                             } ,
                             nullptr ,
                             nullptr );

    Logger::Log( "Create Log Sender! end"    );

    Logger::Log( "Report Self Status! begin" );
    ReportSelfStatus();
    Logger::Log( "Report Self Status! end"   );

    Pipeline::Instance()->Run();
}

// Finish the task
void WorkManager::FinishWork()
{
    self_status_ = ServantStatus::kStandby;

    ReportSelfStatus();
    MRT::SyncWorker::Stop( log_sender_ );

    // one more round of sending can ensure the whole log has been send out
    SendLogUpdate();

    Logger::Log( "Task ID [ % ] Subtask ID [ % ] Finished." , main_task_id_ , subtask_id_ );
}

// Report self status to master
void WorkManager::ReportSelfStatus()
{
    Protocal::MessageHub::Instance()->SendServantUpdate( self_status_ );
}

// update the log of current running subtask
void WorkManager::SendLogUpdate()
{
    Protocal::MessageHub::Instance()->SendLogUpdate( main_task_id_ , subtask_id_ );
}

NS_SERVANT_END