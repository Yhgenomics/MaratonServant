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
* Description   : Add all System Info Handler.
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/2/25
* Modifed       : When      | Who       | What
***********************************************************************************/

#include "SystemInfoAgent.h"

NS_SERVANT_BEGIN
    bool SystemInfoAgent::AddAllHandler()
    {

        AddHandler( "MEM_TOTAL"  , [ this ] () { return Query( R"(free -m | grep Mem | awk '{print $2}')"      ); } );
        AddHandler( "MEM_UESED"  , [ this ] () { return Query( R"(free -m | grep cache: | awk '{print $3}')"   ); } );

        AddHandler( "CPU_NUM"    , [ this ] () { return Query( R"(cat /proc/cpuinfo| grep "processor"| wc -l)" ); } );
        
        AddHandler( "CPU_USER"   , [ this ] () { return Query( R"(top -n 1 | grep Cpu | awk '{print $2}')"     ); } );
        AddHandler( "CPU_SYS"    , [ this ] () { return Query( R"(top -n 1 | grep Cpu | awk '{print $4}')"     ); } );

        AddHandler( "LOAD_1MIN"  , [ this ] () { return Query( R"(uptime | cut -d : -f 5 | cut -d , -f 1 | awk '{print $1}')" ); } );
        AddHandler( "LOAD_5MIN"  , [ this ] () { return Query( R"(uptime | cut -d : -f 5 | cut -d , -f 2 | awk '{print $1}')" ); } );
        AddHandler( "LOAD_15MIN" , [ this ] () { return Query( R"(uptime | cut -d : -f 5 | cut -d , -f 3 | awk '{print $1}')" ); } );

        return true;
    }
NS_SERVANT_END