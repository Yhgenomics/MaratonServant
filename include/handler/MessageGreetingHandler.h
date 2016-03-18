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
* Description   : Base class for message handler.
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/3/3
* Modifed       : When      | Who       | What
***********************************************************************************/

#ifndef MESSAGEGREETING_HANDLER_H_
#define MESSAGEGREETING_HANDLER_H_

#include "WorkManager.h"
#include "MessageGreeting.pb.h"
#include "MessageRegist.pb.h"
#include "MessageHandler.h"
#include "GeneralSession.h"
#include <functional>
#include <string>
#include <memory>
#include <iostream>

namespace Protocal
{
    class MessageGreetingHandler : public MessageHandler
    {
    public:
        MessageGreetingHandler()
        {
            MessageType("MessageGreeting");
            Method = []( GeneralSession* session , const void* pData , size_t length )
            {
                Logger::Log( "Greeting from master" );

                auto msg = make_uptr( MessageRegist );
                msg->set_id( MRT::UUID::Create() );
                msg->set_state( NS_SERVANT::WorkManager::Instance()->SelfStatus() );
                msg->set_cpu( MRT::SystemInfo::CPUNum() );
                msg->set_memory( ( int )(MRT::SystemInfo::MemoryFreeSize() / MEM_SIZE_FACTOR_MB ) );
                msg->set_type( ServantTypes::kSoftware );
                session->SendOut( move_ptr( msg ) );
                return true;
            };
        }
    };
}

#endif //!MESSAGEGREETING_HANDLER_H_

