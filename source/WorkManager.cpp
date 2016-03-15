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

#include "WorkManager.h"

NS_SERVANT_BEGIN

// Add one pipeline from a message

void WorkManager::AddPipeline( uptr<MessageTaskDeliver> message )
{
    // for(auto onePipe : msg )
    task_id_     = message->originalid();
    pipeline_id_ = message->pipeline().id();
    core_        = "8";
    memory_      = "32000";
    Pipeline::Instance()->ParseFromMessage( move_ptr( message ) );
}

void WorkManager::StartWork()
{
    std::cout << "Task ID " << task_id_ << " start " << std::endl;

    auto master = Protocal::MessageHub::Instance()->Master();
    auto msg    = make_uptr( MessageServantUpdate );
    msg->set_status( ServantStatus::kWorking );
    master->SendOut( move_ptr( msg ) );
    Pipeline::Instance()->Run();
}

void WorkManager::FinishWork()
{
    auto master = Protocal::MessageHub::Instance()->Master();
    auto msg    = make_uptr( MessageServantUpdate );
    msg->set_status( ServantStatus::kStandby );
    master->SendOut( move_ptr( msg ) );
}

NS_SERVANT_END