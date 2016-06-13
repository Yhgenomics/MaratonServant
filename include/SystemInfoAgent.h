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
* Description   : A singleton class for quering kinds of system information, such as 
                  CPU , memory.
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/6/13
* Modifed       : When      | Who       | What
***********************************************************************************/
#ifndef SYSTEM_INFO_AGENT_H
#define SYSTEM_INFO_AGENT_H

#include "ServantGloable.h"
#include "MRT.h"
#include <string>
#include <memory>
#include "stdlib.h"

using std::string;

NS_SERVANT_BEGIN
#define MAX_CMD_BUFFER 512
// @Description : Quering kinds of system information.            
// @Example     :
//                NS_SERVANT::SystemInfoAgent::Instance()->AddPipeline( move_ptr( msg ) );
//                 
class SystemInfoAgent : public MRT::Singleton<SystemInfoAgent>
{
public:
    // Query a element by a mark
    // and the right method will be called and return the value in a string.
    // @note : return an empty string when the element can not be handled. 
    string Query( const string& element )
    {
        if ( handler_map_.find( element ) != handler_map_.end() )
        {
            return handler_map_[ element ]();
        }

        else return "";
    }

    // Type of the Info, the concrete method depends on the element binds to it. 
    typedef std::function< string( void )> InfoGetter;

    // Handler map keep the element name and InforGetter in a 1:1 relationship
    std::map< string , InfoGetter > handler_map_;

    bool AddAllHandlers();

    // Add one handler to the SystemInfo
    // @element    : the name of the element.
    // @infoGetter : the method to get a result in string.
    // @note       : this method is a tiny different from the one in MessageHub
    //             : which is in considering of a tradeoff to avoid increasing class types
    //             : and this SystemInfoAgent will be called more frequently than MessageHub. 
    bool AddHandler( string element , InfoGetter infoGetter )
    {
        // The info getter cannot be empty
        if ( infoGetter == nullptr )
        {
            return false;
        }

        bool result;

        // New handler
        if ( handler_map_.find( element ) == handler_map_.end() )
        {
            handler_map_[ element ] = infoGetter;
            result = true;
        }

        // Do not allow binding different handlers for same message
        else
        {
            result = false;
        }

        return result;
    }

protected:

    // Constructor
    SystemInfoAgent() {};

    // Desctructor
    ~SystemInfoAgent() {};

    // initialization
    void Init();

    // process a command line 
    // @note : the result is strongly recommanded to be parsed by the command line, thus tick out the
    //         uesful message.
    string GetCommandResult( const char* command )
    {
        char             buffer[ MAX_CMD_BUFFER ] = { '\0' }   ;
        string           result                   = { ""   }   ;

        shared_ptr<FILE> pipe( popen( command , "r" ), pclose );

        if( !pipe )
        {
            Logger::Error( "The following command cannot be processed: %" , string( command , strlen( command ) ) );
            return "";
        }

        while ( !feof( pipe.get() ) )
        {
            if ( nullptr != fgets( buffer , sizeof( buffer ) , pipe.get() ) )
            {
                result += buffer;
            }
        }

        // remove \n mark at the tail
        if( '\n' == *result.rbegin() ) result.erase( result.end() - 1 );
        return result;

    }

private:

    friend MRT::Singleton<SystemInfoAgent>;
    
};

NS_SERVANT_END

#endif // !SYSTEM_INFO_AGENT_H