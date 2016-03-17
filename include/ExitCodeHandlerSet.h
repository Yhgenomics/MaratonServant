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
* Description   : Kinds of predefine exit code handler. Just for convenience.
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/3/8
* Modifed       : When      | Who       | What
***********************************************************************************/

#ifndef EXIT_CODE_HANDLER_SET_H_
#define EXIT_CODE_HANDLER_SET_H_

#include "Pipeline.h"
#include <iostream>
        
NS_SERVANT_BEGIN

// Show the exit code and do notheing
// @exitCode   : The exit code get by the Wait command from a container
void DefalutExit( const int& exitCode )
{
    std::cout << "upper level exit code handler received : " << exitCode << std::endl;
}

// For pipeline to call next pipe
// @exitCode   : The exit code get by the Wait command from a container
void NextPipe( const int& exitCode )
{
    Pipeline::Instance()->RunNext( exitCode );
}

NS_SERVANT_END

#endif // !EXIT_CODE_HANDLER_SET_H_
