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
* Description   : Message hub for all message session receive.
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/3/2
* Modifed       : When      | Who       | What
***********************************************************************************/

#ifndef MESSAGE_HUB_H_
#define MESSAGE_HUB_H_

#include "MessageHandler.h"
#include "GeneralSession.h"
#include "MasterSession.h"
#include "MessageHeartBeat.pb.h"
#include "MRT.h"
#include <string>
#include <map>
#include <iostream>
#include <functional>
#include <google/protobuf/message.h>


namespace Protocal
{
    class MessageHub : public MRT::Singleton<MessageHub>
    {
    public:
        MessageHub()  {};
        ~MessageHub() {};

        bool AddHandler( uptr<MessageHandler> oneHandler )
        {
            if ( oneHandler->Method == nullptr )
            {
                return false;
            }

            bool result;
            size_t messageID = HashName( oneHandler->MessageType() );

            if ( handler_map_.find( messageID ) == handler_map_.end() )
            {
                handler_map_[ messageID ] = std::move( oneHandler );
                result = true;
            }

            else
            {
                result = false;
            }

            return result;
        };

        bool AddAllHandlers();

        int Handle( GeneralSession* session , const void* pData , size_t length )
        {
            size_t messageID = 0;
            char* data = ( char* )pData;
            messageID = *( ( size_t* )data );
            handler_map_[ messageID ]->Method( session , pData , length );
            return 0;
        }

        uptr<MRT::Buffer> Build( uptr<::google::protobuf::Message> message )
        {
            size_t message_id = HashName( message->GetTypeName() );
            std::string body = message->SerializeAsString();
            uptr<MRT::Buffer> buffer = make_uptr( MRT::Buffer , body.size() + sizeof( size_t ) );

            char* pbuf = buffer->Data();
            *( ( size_t* )pbuf ) = message_id;
            pbuf += sizeof( size_t );
            memcpy( pbuf , body.c_str() , body.size() );
            return move_ptr( buffer );
        }
        
        MasterSession*  Master()            { return master_session_;  }
        void Master( MasterSession* value ) { master_session_ = value; }

        bool SendHeartBeat()
        {
            if ( master_session_ )
            {
                auto msg = make_uptr( MessageHeartBeat );
                msg->set_code( 161 );
                master_session_->SendOut( move_ptr( msg ) );
                return false;
            }
            else
                return true;
        }
    private:
        std::map<size_t , uptr<MessageHandler> > handler_map_;

        size_t HashName( std::string messageType )
        {
            size_t result = 0;
            for ( int i = 0; i < messageType.length(); i++ )
            {
                char b = ( char )messageType[ i ];
                size_t v = ( ( ( size_t )b << ( ( i % ( char )8 ) * ( char )8 ) ) | i );
                result |= ( size_t )( v );
            }
            return result;
        }
        
        MasterSession * master_session_ = nullptr;

        friend MRT::Singleton<MessageHub>;
    };

}
#endif // !MESSAGE_HUB_H_