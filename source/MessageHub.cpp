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
* Date          : 2016/3/12
* Modifed       : When      | Who       | What
***********************************************************************************/

#include "MessageHub.h"
#include "WorkManager.h"
#include "SystemInfoAgent.h"
#include "MessageTaskLogsUpdate.pb.h"
#include "MRT.h"
#include "json.hpp"
#include <fstream>


using std::string;
using nlohmann::json;
using NS_SERVANT::SystemInfoAgent;

namespace Protocal
{
    // Add one handler to the Hub
    // @oneHandler : one message handler in unique pointer.
    bool MessageHub::AddHandler( uptr<MessageHandler> oneHandler )
    {
        // The handler's method cannot be empty
        if ( oneHandler->Method == nullptr )
        {
            return false;
        }

        bool result;
        size_t messageID = HashName( oneHandler->MessageType() );

        // New handler
        if ( handler_map_.find( messageID ) == handler_map_.end() )
        {
            handler_map_[ messageID ] = std::move( oneHandler );
            result = true;
        }

        // Do not allow binding different handlers for same message
        else
        {
            result = false;
        }

        return result;
    }

    // Handle one message arcoding to the handler map
    // @session : The source of the message.
    // @pData   : The content of the message.
    // @length  : The size of message.
    // @note    : Just get the messageID in this function, the translation from the pData
    //            to message should be done at certain MessageHandler.
    int MessageHub::Handle( GeneralSession* session ,
                            const void* pData ,
                            size_t length )
    {
        size_t  messageID = 0;
        char*   data      = ( char* )pData;
        messageID = *( ( size_t* )data );

        handler_map_[ messageID ]->Method( session , pData , length );

        return 0;
    }

    // Build the protobuf message to buffer
    // @message : protobuf message in unique pointer
    uptr<MRT::Buffer> MessageHub::Build( uptr<::google::protobuf::Message> message )
    {
        size_t            message_id = HashName( message->GetTypeName() );
        string            body       = message->SerializeAsString();
        uptr<MRT::Buffer> buffer     = make_uptr( MRT::Buffer , 
                                                  body.size() + sizeof( size_t ) );

        char*             pbuf       = buffer->Data();
        *( ( size_t* )pbuf )         = message_id;

        pbuf      += sizeof( size_t );

#if _WIN32
        memcpy_s( pbuf , body.size() , body.c_str() , body.size() );
#else
        memcpy( pbuf , body.c_str() , body.size() );
#endif

        return move_ptr( buffer );
    }

    // Heartbeat message will refresh Servant session at Master
    // and avoiding be kicked off.
    bool MessageHub::SendHeartBeat()
    {
        if ( nullptr != master_session_ )
        {
            auto msg = make_uptr( MessageHeartBeat );
            msg->set_code( 161 );
            
            // Add system info for monitor

            msg->set_memtotal  = SystemInfoAgent::Instance()->Query( "MEM_TOTAL"  );
            msg->set_memuesed  = SystemInfoAgent::Instance()->Query( "MEM_UESED"  );
            msg->set_cpunum    = SystemInfoAgent::Instance()->Query( "CPU_NUM"    );
            msg->set_cpuuser   = SystemInfoAgent::Instance()->Query( "CPU_USER"   );
            msg->set_cpusys    = SystemInfoAgent::Instance()->Query( "CPU_SYS"    );
            msg->set_load1min  = SystemInfoAgent::Instance()->Query( "LOAD_1MIN"  );
            msg->set_load5min  = SystemInfoAgent::Instance()->Query( "LOAD_5MIN"  );
            msg->set_load15min = SystemInfoAgent::Instance()->Query( "LOAD_15MIN" );

            master_session_->SendOut( move_ptr( msg ) );
            return false;
        }

        else
            return true;
    }

    // Send the log update for one ceratin subtask
    // @mainTaskID : task ID for a main task(from the business layer).
    // @subTaskID  : task ID for a subtask(from the master layer).
    bool MessageHub::SendLogUpdate( const string & mainTaskID , const string & subTaskID )
    {
        Logger::Log( "SendLogUpdate in " );
        string logContent = "";
        bool   logExsit   = GetSubtaskLog( mainTaskID , subTaskID , logContent );

        //[TODO] find out the log content's increment

        //make a update message.
        auto msg = make_uptr( MessageTaskLogsUpdate );

        if ( logExsit )
        {
            msg->set_errormark( ( int )ErrorCode::kNoError );
        }

        else
        {
            msg->set_errormark( ( int )ErrorCode::kLogNotFound );
            Logger::Log("log not found!");
        }

        msg->set_taskid( mainTaskID );
        msg->set_subtaskid( subTaskID );
        msg->set_servantid( NS_SERVANT::WorkManager::Instance()->ServantID() );
        msg->set_content( logContent );

        if ( nullptr != master_session_ )
        {
            master_session_->SendOut( move_ptr( msg ) );
        }

        Logger::Log( "SendLogUpdate out " );

        return true;
    }

    // Send update message only contains task status
    // @status  : Status for current task.
    // @note    : Used any status except the successful finishing
    bool MessageHub::SendTaskUpdate( const TaskStatus::Code& status )
    {
        auto msg    = make_uptr( MessageTaskUpdate );
        msg->set_status( status );
        if ( nullptr != master_session_ )
        {
            master_session_->SendOut( move_ptr( msg ) );
        }

        return true;
    }

    // Send update message contains task status and output information
    // @status  : Status for current task.
    // @outputs : Output files generated by current task.
    // @note    : Used when a task/pipeline finishing without any error
    bool MessageHub::SendTaskUpdate( const TaskStatus::Code& status , 
                                     const vector<string>& outputs )
    {
        auto msg    = make_uptr( MessageTaskUpdate );
        msg->set_status( status );

        for ( auto const& item : outputs )
        {
            msg->add_output( item );
        }

        if ( nullptr != master_session_ )
        {
            master_session_->SendOut( move_ptr( msg ) );
        }
        
        return true;
    }

    // Send update message contains Servant status
    // @status  : Status for this servant.
    bool MessageHub::SendServantUpdate( const ServantStatus::Code& status )
    {
        auto msg    = make_uptr( MessageServantUpdate );
        msg->set_status( (int)status );

        if ( nullptr != master_session_ )
        {
            master_session_->SendOut( move_ptr( msg ) );
        }
        return true;
    }

    // Hash the name of a message
    // @messageType : message name's string
    // @note        : When sending this hash code will be packaged to the buffer
    size_t MessageHub::HashName( const std::string& messageType )
    {
        size_t result = 0;

        for ( int i = 0; i < messageType.length(); i++ )
        {
            char    b         = ( char )messageType[ i ];
            size_t  v         = ( ( ( size_t )b << ( ( i % ( char )8 ) * ( char )8 ) ) | i );
            result   |= ( size_t )( v );
        }

        return result;
    }

    // Gather all exsit logs for a main(original) task.
    // Return true and put all logs in JSON string
    // Return false if the task is not running at this servant
    // @maintaskID : ID of the main(original) task.
    bool MessageHub::GatherTaskLog( const string & maintaskID , string & allLogContent )
    {
        bool   result         = false;

        string taskRoot       = NS_SERVANT::Pipeline::Instance()->TaskRoot();
        string MainLogName    = NS_SERVANT::Pipeline::Instance()->MainLogName();

        std::ifstream fin;
        fin.open( taskRoot + maintaskID + "/" + MainLogName );

        // task has run in this servant
        if ( fin.is_open() )
        {
            result = true;
            // gather each subtask's log creat a content
            string logContent;
            string subtaskID;
            json   allLogs;
            json   oneLog;
            int    order = 0 ; // order of the subtasks start from 0
            while ( getline( fin , subtaskID ) )
            {
                subtaskID.erase( subtaskID.find_last_not_of( "\r" ) + 1 );
                oneLog.clear();
                oneLog[ "subtaskID" ] = subtaskID;
                oneLog[ "order" ] = order;
                order++;

                if ( GetSubtaskLog( maintaskID , subtaskID , logContent ) )
                {
                    oneLog[ "content" ] = logContent;
                }

                else
                {
                    oneLog[ "content" ] = "No Runtime LOGs yet!";
                }
                allLogs.push_back( oneLog );
            }

            std::cout << allLogs.dump( 4 ) << std::endl;
            allLogContent = allLogs.dump();
            fin.close();
        }

        // task not run in this servant
        else
        {
            result = false;
        }

        return result;
    }

    // Get a copy of current log file's content
    // Return true and put the content in the third's parameters
    // Return false when the log file doesn't exsit.
    // @maintaskID : ID of the main(original) task
    // @subtaskID  : ID of a subtask
    bool MessageHub::GetSubtaskLog( const string & maintaskID , const string & subtaskID , string & logContent )//;
    {
        bool   result         = false;

        string taskRoot       = NS_SERVANT::Pipeline::Instance()->TaskRoot();
        string runtimeLogName = NS_SERVANT::Pipeline::Instance()->RuntimeLogName();

        std::ifstream fin;
        fin.open( taskRoot + maintaskID + "/" + subtaskID + "/" + runtimeLogName );

        // sub task has log file
        if ( fin.is_open() )
        {
            result = true;
            fin.seekg(0,std::ios::end);
            logContent.resize( fin.tellg() );
            fin.seekg( 0 , std::ios::beg );
            fin.read( &logContent[ 0 ] , logContent.size() );
            fin.close();
            logContent.push_back('\0');
        }

        // sub task not have a log file yet
        else
        {
            result = false;
        }
        return result;
    }

}
