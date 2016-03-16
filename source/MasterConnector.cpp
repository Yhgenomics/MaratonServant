#include "MasterConnector.h"
#include "MasterSession.h"
#include "MessageHub.h"
#include <iostream>

using MRT::SyncWorker;

Session * MasterConnector::CreateSession()
{
    return new MasterSession();
}

void MasterConnector::OnSessionOpen( Session * session )
{
    std::cout << "MasterSession Open" << std::endl;
    Protocal::MessageHub::Instance()->Master( scast<MasterSession*>( session ) );
        SyncWorker::Create( 3000,
                            [](SyncWorker* te)
                            {
                                return Protocal::MessageHub::Instance()->SendHeartBeat();
                            } ,
                            nullptr,
                            nullptr );
}

void MasterConnector::OnSessionClose( Session * session )
{
    std::cout << "MasterSession Close" << std::endl;
    Protocal::MessageHub::Instance()->Master( nullptr );

}
