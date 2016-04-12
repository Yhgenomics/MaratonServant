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
* Description   : Connect to Master.
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/3/7
* Modifed       : When      | Who       | What
***********************************************************************************/

#include "MasterConnector.h"
#include "MasterSession.h"
#include "MessageHub.h"
#include "ServantGloable.h"
#include <iostream>

using MRT::SyncWorker;

// Callback when the business session is connected.
Session * MasterConnector::CreateSession()
{
    Logger::Log( "MasterSession Create" );
    return new MasterSession();
}

// Callback when the business session opening.
// @session : The pointer to the session and can be cast to 
//            the pointer to MasterSession by static cast.
void MasterConnector::OnSessionOpen( Session * session )
{
    Logger::Log( "MasterSession Open" );
    Protocal::MessageHub::Instance()->Master( scast<MasterSession*>( session ) );
        SyncWorker::Create( HERATBEAT_PERIOD ,
                            [](SyncWorker* te)
                            {
                                return Protocal::MessageHub::Instance()->SendHeartBeat();
                            } ,
                            nullptr,
                            nullptr );
}

// Callback when the business session closing.
// @session : The pointer to the session and can be cast to 
//            the pointer to MasterSession by static cast. 
void MasterConnector::OnSessionClose( Session * session )
{
    Logger::Log( "MasterSession Close" );
    Protocal::MessageHub::Instance()->Master( nullptr );
    SAFE_DELETE( session );
}
