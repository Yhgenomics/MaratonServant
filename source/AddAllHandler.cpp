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
* Description   : Do all Handler management.
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/2/25
* Modifed       : When      | Who       | What
***********************************************************************************/

#include "MessageHub.h"
#include "handler/MessageGreetingHandler.h"
#include "handler/MessageRegistHandler.h"
#include "handler/MessageTaskDeliverHandler.h"
#include "handler/MessageTaskDeliverReplyHandler.h"
#include "MRT.h"
#include <memory>

namespace Protocal
{
    bool MessageHub::AddAllHandlers()
    {
        AddHandler( std::move( make_uptr( Protocal::MessageGreetingHandler         ) ) );
        AddHandler( std::move( make_uptr( Protocal::MessageRegistHandler           ) ) );
        AddHandler( std::move( make_uptr( Protocal::MessageTaskDeliverHandler      ) ) );
        AddHandler( std::move( make_uptr( Protocal::MessageTaskDeliverReplyHandler ) ) );

        return true;
    }
}