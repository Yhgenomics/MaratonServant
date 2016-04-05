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

#ifndef PIPE_PARAMETER_HANDLER_SET_H_
#define PIPE_PARAMETER_HANDLER_SET_H_

#include "WorkManager.h"
#include "MRT.h"
#include <iostream>

NS_SERVANT_BEGIN

namespace PipeParameterHandler
{

    // return the sub task ID of current task
    std::string SubTaskID()
    {
        return WorkManager::Instance()->SubtaskID();
    }

    // return the main task ID of current task
    std::string MainTaskID()
    {
        return WorkManager::Instance()->MainTaskID();
    }

    // return the pipeline ID of current task
    std::string PipelineID()
    {
        return WorkManager::Instance()->PipelineID();
    }

    // return the core number of servant's cpu
    std::string Core()
    {
        return WorkManager::Instance()->Core();
    }

    // return the servant's free memory size.
    std::string Memory()
    {
        return WorkManager::Instance()->Memory();
    }
}
NS_SERVANT_END

#endif // !PIPE_PARAMETER_HANDLER_SET_H_
