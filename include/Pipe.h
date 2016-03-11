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

class Pipe
{
public:

    void  AddEnvironment( string key , string value );

    void  AddEnvironment( string pattern );


    void AddPathBind( string localPath , string dockerPath )
    {
        binds_.push_back( localPath + ":" + dockerPath );
    }

    string  DockerDaemon()                { return docker_daemon_;   }
    void    DockerDaemon( string daemon ) { docker_daemon_ = daemon; }
    string  DockerImage()                 { return docker_image_;    }
    void    DockerImage( string image )   { docker_image_ = image;   }
    void    SetPipeExit( ExitCodeHandler onExit ) { PipeExit = onExit; }

    void Run()
    {
        //DockerHelper::Instance()->Pull(docker_daemon_, docker_image_ );
        DockerHelper::Instance()->BindExitCodeHandler( PipeExit );
        DockerHelper::Instance()->Run(  docker_daemon_ , docker_image_ , binds_ , environments_ );
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