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
* Description   : Handler with Docker Daemon.
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/3/7
* Modifed       : When      | Who       | What
***********************************************************************************/

#ifndef DOCKERHELPER_H_
#define DOCKERHELPER_H_

#include "ServantGloable.h"
#include "MRT.h"
#include <string>

using std::string;
using std::vector;
using std::map;
using MRT::Singleton;

NS_SERVANT_BEGIN

// @Description : Use Docker via the REST API            
// @Example     : A docker container can be searched, pulled, create, run and 
//                waited for it's exit code.
//                The REST API does not cantain the docker run command, so here with DockerHelper,
//                just bind the exit code handler and use it's Run function.                   
//                {
//                    DockerHelper::Instance()->BindExitCodeHandler( someExitHandler );
//                    DockerHelper::Instance()->Run( daemon , image , binds , environments );
//                }                
// @Note        : the ExitCode Handler should be bind before the docker start to run  
class DockerHelper :public Singleton<DockerHelper>
{
public:
    
    // Pull one docker image from registry 
    // @dest    : The docker daemon such as http://127.0.0.1:1234
    // @image   : The docker image's name 
    virtual size_t    Pull  ( const string &dest , const string &image );

    // Create one docker container
    // @dest        : The docker daemon such as http://127.0.0.1:1234
    // @image       : The docker image's name
    // @binds       : The path binds from local path to docker path
    // @environment : The variables and their values in container
    // @note        : The container's ID is in the response message. 
    virtual size_t    Create( const string           &dest  ,
                              const string           &image ,
                              const vector< string > &binds ,
                              const vector< string > &environment );

    // Start a docker container
    // @dest        : The docker daemon such as http://127.0.0.1:1234
    // @containerID : The ID of a container
    // @note        : container ID is given at the response message for Creating
    virtual size_t    Start ( const string &dest , const string &containerID );

    // Wait a docker container's exit code
    // @dest        : The docker daemon such as http://127.0.0.1:1234
    // @containerID : The ID of a container
    virtual size_t    Wait  ( const string &dest , const string &containerID );

    // Run equals to Pull => Create => Start => Wait
    // @dest        : The docker daemon such as http://127.0.0.1:1234
    // @image       : The docker image's name
    // @binds       : The path binds from local path to docker path
    // @environment : The variables and their values in container
    virtual size_t    Run   ( const string &dest ,
                              const string &image ,
                              const vector< string > &binds ,
                              const vector< string >  &environment );

    // Bind handler for a docker's exit code 
    virtual void      BindExitCodeHandler( ExitCodeHandler  one_handler )
    {
        exit_code_delegate_ = one_handler;
    }
    
    // Bind handler for exceptions
    virtual void      BindExceptionHandler( ExceptionHandler one_handler )
    {
        exception_delegate_ = one_handler;
    }

    // Bind handler from upper layer logger system .
    virtual void      BindLogHandler( LogHandler       one_handler )
    {
        log_delegate_       = one_handler;
    }

    // true when need to trigger the next action
    bool              is_run_mode_          = false;
    
    ExitCodeHandler   exit_code_delegate_   = nullptr;
    ExceptionHandler  exception_delegate_   = nullptr;
    LogHandler        log_delegate_         = nullptr;

private:

    // Get string for post a pull command
    // @dest    : dest is the docker daemon such as http://127.0.0.1:1234
    // @image   : image is the docker image's name
    string GetPullString( const string& dest , const string& image )
    {
        return dest + kCreateImage + kParamsToken + kFromImage + image;
    }

    // Get string for post a create command
    // @dest    : dest is the docker daemon such as http://127.0.0.1:1234
    string GetCreateString( const string& dest )
    {
        return dest + kCreateContainer;
    }

    // Get string for post a start command
    // @dest        : dest is the docker daemon such as http://127.0.0.1:1234
    // @containerID : containerID is the ID of a container
    string GetStartString( const string &dest , const string &containerID )
    {
        return dest + KContainers + containerID + kStartContainer;
    }
    
    // Get string for post a wait command
    // @dest        : dest is the docker daemon such as http://127.0.0.1:1234
    // @containerID : containerID is the ID of a container
    string GetWaitString( const string &dest , const string &containerID )
    {
        return dest + KContainers + containerID + kWaitContainer;
    }

    // const values for docker REST API
    const string      kDockerHeaderKey   = "Content-Type";
    const string      kDockerHeaderValue = "application/json";  
    const string      kCreateContainer   = "/containers/create";
    const string      KContainers        = "/containers/";
    const string      kStartContainer    = "/start";
    const string      kWaitContainer     = "/wait";
    const string      kCreateImage       = "/images/create";
    const string      kParamsToken       = "?";   
    const string      kFromImage         = "fromImage=";

    // values not used for latter use
    //const string      kListContianers    = "/containers/json";
    //const string      kFromSource        = "fromSrc=";

    // const values for docker Create JSON keys
    const string      kImageKey          = "Image";
    const string      kEvironmentKey     = "Env";
    const string      kBindsKey          = "Binds";
    const string      kHostKey           = "HostConfig";

    // const valudes for HTTPResponse under docker REST API
    const string      kContainerIDKey    = "Id";
    const string      kExitCodeKey       = "StatusCode";
    const string      kEmptyString       = "";

    // container ID and status record
    // @note    : For latter usage of docker contianer management 
    map<string , string> contianer_list_;
    
    friend Singleton<DockerHelper>;

};

NS_SERVANT_END

#endif // !DOCKERHELPER_H_
