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

#include "Pipe.h"
#include "PipeParameterPattern.h"

NS_SERVANT_BEGIN

// Add the enviroment by key and value
// @key   : Key string of an environment.
// @value : Value string of an enviroment.
// @note  : Under the constrains from Docker's REST API
//          the enviroment format is "key=value"   
void Pipe::AddEnvironment( const string& key , const string& value )
{
    environments_.push_back( key + "=" + value );
}

// Add the enviroment by patterns
// @patter  : String may contains a pattern
// @note    : this parameter is not const cause pattern always need to be translated
void Pipe::AddEnvironment( string& pattern )
{
    ParameterPattern::Instance()->Replace( pattern );
    environments_.push_back( pattern );
}

// Add one local-to-docker Path bind
// @localPath  : Local path.
// @dockerPath : Logical path in docker.
void Pipe::AddPathBind( const string& localPath , const string& dockerPath )
{
    binds_.push_back( localPath + ":" + dockerPath );
}

// Run the Pipe
void Pipe::Run()
{
    DockerHelper::Instance()->BindExitCodeHandler( PipeExit );
    DockerHelper::Instance()->Run( docker_daemon_ , docker_image_ , binds_ , environments_ );
}
NS_SERVANT_END
