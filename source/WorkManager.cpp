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

// Add one pipeline from a message
// @message : message from the Maraton Master
void WorkManager::AddPipeline( uptr<MessageTaskDeliver> message )
{
    main_task_id_ = message->originalid();
    subtask_id_   = message->id();
    pipeline_id_  = message->pipeline().id();
    
    std::stringstream strStream;

    strStream << MRT::SystemInfo::CPUNum();
    strStream >> core_;
    strStream.clear();

    strStream << MRT::SystemInfo::MemoryFreeSize();
    strStream >> memory_;

    Pipeline::Instance()->ParseFromMessage( move_ptr( message ) );
}

// Start the task
void WorkManager::StartWork()
{
    std::cout << "Task ID "    << main_task_id_ << std::endl
              << "Subtask ID " << subtask_id_   << std::endl
              << " start "     << std::endl;

    Protocal::MessageHub::Instance()->SendServantUpdate( ServantStatus::kWorking );

    Pipeline::Instance()->Run();
}

// Finish the task
void WorkManager::FinishWork()
{
    Protocal::MessageHub::Instance()->SendServantUpdate( ServantStatus::kStandby );

    std::cout << "Task ID "    << main_task_id_ << std::endl
              << "Subtask ID " << subtask_id_   << std::endl
              << " finish "    << std::endl;
}

NS_SERVANT_END