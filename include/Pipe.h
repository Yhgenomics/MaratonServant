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
* Description   : One round of docker container.
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/3/8
* Modifed       : When      | Who       | What
***********************************************************************************/

#ifndef PIPE_H_
#define PIPE_H_

#include "ServantGloable.h"
#include "DockerHelper.h"
#include <vector>
#include <string>

NS_SERVANT_BEGIN

// @Description : One Pipe will call one docker container, is one step in a pipeline.
class Pipe
{
public:

    // Add the enviroment by key and value
    // @key   : Key string of an environment.
    // @value : Value string of an enviroment.
    // @note  : Under the constrains from Docker's REST API
    //          the enviroment format is "key=value"   
    void  AddEnvironment( const string& key , const string& value );

    // Add the enviroment by patterns
    // @patter  : String may contains a pattern
    // @note    : this parameter is not const cause pattern always need to be translated
    void  AddEnvironment( string& pattern );

    // Add one local-to-docker Path bind
    // @localPath  : Local path.
    // @dockerPath : Logical path in docker.
    void AddPathBind( const string& localPath , const string& dockerPath );

    // Getter and Setter for Docker Daemon
    // @note    : A docker daemon is like http://127.0.0.1:1234
    string  DockerDaemon()                     { return docker_daemon_;   }
    void DockerDaemon( const string& daemon )  { docker_daemon_ = daemon; }
                                               
    // Getter and Setter for Docker Image Name 
    string  DockerImage()                      { return docker_image_;    }
    void DockerImage( const string& image )    { docker_image_ = image;   }

    // Set the exit handler to pipe's docker exit code handler
    // @onExit  : Exit code handler.
    void SetPipeExit( ExitCodeHandler onExit ) { PipeExit = onExit;       }

    // Run the Pipe
    void Run();

    // Constructor
    Pipe()
    {
        Init();
    }
    
    // Destructor
    ~Pipe()  {}

    // Initialization
    void Init()
    {
        docker_image_="";
        docker_contianer_id_="";
        docker_daemon_="";
        environments_.clear();
        binds_.clear();
        PipeExit = nullptr;
    }

private: 

    string          docker_image_;
    string          docker_contianer_id_;
    string          docker_daemon_;
    vector<string>  environments_;
    vector<string>  binds_;
    ExitCodeHandler PipeExit;

};

NS_SERVANT_END

#endif // £¡PIPE_H_