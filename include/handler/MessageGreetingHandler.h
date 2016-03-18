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
                std::cout<<"Greeting from master"<<std::endl;
                auto msg = make_uptr( MessageRegist );
                msg->set_id( MRT::UUID::Create() );
                msg->set_state(3);
                msg->set_cpu(8);
                msg->set_memory(32000);
                msg->set_type(0);
                session->SendOut( move_ptr( msg ) );
                return true;
            };
        }
    };
}

#endif //!MESSAGEGREETING_HANDLER_H_

