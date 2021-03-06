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
#include "MessageServantUpdate.pb.h"
#include "MessageTaskUpdate.pb.h"
#include "ServantGloable.h"
#include "MRT.h"
#include <string>
#include <map>
#include <iostream>
#include <functional>
#include <vector>
#include <google/protobuf/message.h>

using std::vector;
using std::string;

namespace Protocal
{
    // @Description : Basic Class for kinds of message handler used by MessageHub 
    //                automaticly after be add to the MessageHub.Check MessageHub
    //                for more details.
    // @Example     : namespace Protocal
    //                {
    //                    class SomeMessageHandler : public MessageHandler
    //                    {
    //                    public:
    //                        MessageGreetingHandler()
    //                        {
    //                            MessageType("SomeMessage");
    //                            Method = []( GeneralSession* session , 
    //                                         const void* pData , 
    //                                         size_t length )     
    //                            {
    //                                //TODO add your codes here
    //                                return true;
    //                            };
    //                        }
    //                    };
    //                }              
    // @Note        : Add the derived class to MessageHub to handle message automaticly.
    //                the message is in pData,it can be a protobuf message, or any
    //                other type determined by the original sender.
    class MessageHub : public MRT::Singleton<MessageHub>
    {
    public:

        // Constructor
        MessageHub()  {};

        // Destructor
        ~MessageHub() {};

        // Add one handler to the Hub
        // @oneHandler : one message handler in unique pointer.
        bool AddHandler( uptr<MessageHandler> oneHandler );        

        // Gloable Message handlers management
        // @note    : Implement in AddAllHandler.cpp seprately.
        bool AddAllHandlers();

        // Handle one message arcoding to the handler map
        // @session : The source of the message.
        // @pData   : The content of the message.
        // @length  : The size of message.
        // @note    : Just get the messageID in this function, the translation from the pData
        //            to message should be done at certain MessageHandler.
        int Handle( GeneralSession* session , const void* pData , size_t length );
       
        // Build the protobuf message to buffer
        // @message : protobuf message in unique pointer
        uptr<MRT::Buffer> Build( uptr<::google::protobuf::Message> message );
       
        // Getter and Setter for Master seesion's pointer.
        // @note    : Record the Master session
        MasterSession*  Master()            { return master_session_;  }
        void Master( MasterSession* value ) { master_session_ = value; }

        // Heartbeat message will refresh Servant session at Master
        // and avoiding be kicked off.
        bool SendHeartBeat();

        // Send the log update for one ceratin subtask
        // @mainTaskID : task ID for a main task(from the business layer).
        // @subTaskID  : task ID for a subtask(from the master layer).
        bool SendLogUpdate( const string& mainTaskID , const string& subTaskID );

        // Send all logs asscoiated to a ceratin main task
        bool SendLogs( const string& mainTaskID){ return true;}

        // Send update message only contains task status
        // @status  : Status for current task.
        // @note    : Used any status except the successful finishing
        bool SendTaskUpdate( const TaskStatus::Code&  status );

        // Send update message contains task status and output information
        // @status  : Status for current task.
        // @outputs : Output files generated by current task.
        // @note    : Used when a task/pipeline finishing without any error
        bool SendTaskUpdate( const TaskStatus::Code&  status , 
                             const vector<string>& outputs );

        // Send update message contains Servant status
        // @status  : Status for this servant.
        bool SendServantUpdate( const ServantStatus::Code& status );

        // Gather all exsit logs for a main(original) task.
        // Return true and put all logs in JSON string
        // Return false if the task is not running at this servant
        // @maintaskID : ID of the main(original) task.
        bool GatherTaskLog( const string& maintaskID,
                            string& allLogContent );

        // Get a copy of current log file's content
        // Return true and put the content in the third's parameters
        // Return false when the log file doesn't exsit.
        // @maintaskID : ID of the main(original) task
        // @subtaskID  : ID of a subtask
        bool GetSubtaskLog( const string& maintaskID,
                            const string& subtaskID,
                            string& logContent );

    private:

        // Handler map keep the messageID and Handler in a 1:1 relationship
        std::map<size_t , uptr<MessageHandler> > handler_map_;

        // Hash the name of a message
        // @messageType : message name's string
        // @note        : When sending this hash code will be packaged to the buffer
        size_t HashName( const std::string& messageType );        
        
        // the only Master session for this Servant
        MasterSession * master_session_ = nullptr;

        friend MRT::Singleton<MessageHub>;

    }; 
} //  end of namespace Protocal

#endif // !MESSAGE_HUB_H_