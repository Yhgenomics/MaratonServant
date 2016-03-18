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
#include <sstream>
#include <string>

NS_SERVANT_BEGIN

// Constructor
WorkManager::WorkManager()
{
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
    main_task_id_ = message->originalid();
    subtask_id_   = message->id();
    pipeline_id_  = message->pipeline().id();

    Pipeline::Instance()->ParseFromMessage( move_ptr( message ) );
}

// Start the task
void WorkManager::StartWork()
{
    std::cout << "Task ID "    << main_task_id_ << std::endl
              << "Subtask ID " << subtask_id_   << std::endl
              << " start "     << std::endl;
    self_status_ = ServantStatus::kWorking;
    
    ReportSelfStatus();

    Pipeline::Instance()->Run();
}

// Finish the task
void WorkManager::FinishWork()
{
    self_status_ = ServantStatus::kStandby;

    ReportSelfStatus();

    std::cout << "Task ID "    << main_task_id_ << std::endl
              << "Subtask ID " << subtask_id_   << std::endl
              << " finish "    << std::endl;
}

// Report self status to master
inline void WorkManager::ReportSelfStatus()
{
    Protocal::MessageHub::Instance()->SendServantUpdate( self_status_ );
}

NS_SERVANT_END