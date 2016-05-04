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
#include "json.hpp"
#include <sstream>
#include <string>
#include <fstream>

using nlohmann::json;
NS_SERVANT_BEGIN

// Constructor
WorkManager::WorkManager()
{
    self_status_ = ServantStatus::kStandby;

    std::stringstream strStream;

    strStream << MRT::SystemInfo::CPUNum();
    strStream >> core_;
    strStream.clear();

    strStream << (MRT::SystemInfo::MemoryFreeSize() / MEM_SIZE_FACTOR_MB );
    strStream >> memory_;
}

// Add one pipeline from a message
// @message : message from the Maraton Master
void WorkManager::AddPipeline( uptr<MessageTaskDeliver> message )
{
    main_task_id_ = message->originalid();
    subtask_id_   = message->id();
    pipeline_id_  = message->pipeline().id();

    Pipeline::Instance()->ParseFromMessage( move_ptr( message ) );
}

// Start the task
void WorkManager::StartWork()
{
    Logger::Log( "Task ID [ % ] Subtask ID [ % ] Start." , main_task_id_ , subtask_id_ );
    self_status_ = ServantStatus::kWorking;
    
    ReportSelfStatus();

    Pipeline::Instance()->Run();
}

// Finish the task
void WorkManager::FinishWork()
{
    self_status_ = ServantStatus::kStandby;

    ReportSelfStatus();

    Logger::Log( "Task ID [ % ] Subtask ID [ % ] Finished." , main_task_id_ , subtask_id_ );
}

// Report self status to master
inline void WorkManager::ReportSelfStatus()
{
    Protocal::MessageHub::Instance()->SendServantUpdate( self_status_ );
}

// Gather all exsit logs for a main(original) task.
// Return true and put all logs in JSON string
// Return false if the task is not running at this servant
// @maintaskID : ID of the main(original) task.
bool WorkManager::GatherTaskLog( const string & maintaskID , string & allLogContent )
{
    bool result = false;
    //TODO set this strings to right place
    //string taskRoot    = "/data/mrttask/";
    string taskRoot       = "g:/logtest/";
    string MainLogName    = "subtasklist.log";
    string runtimeLogName = "runtime.log";
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
bool WorkManager::GetSubtaskLog( const string & maintaskID , const string & subtaskID , string & logContent )//;
{
    bool result = false;
    //TODO set this strings to right place
    //string taskRoot    = "/data/mrttask/";
    string taskRoot       = "g:/logtest/";
    string MainLogName    = "subtasklist.log";
    string runtimeLogName = "runtime.log";
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
    }

    // sub task not have a log file yet
    else
    {
        result = false;
    }
    return result;
}

NS_SERVANT_END