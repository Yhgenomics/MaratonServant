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
* Description   : Maraton Servant main logic.
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/3/8
* Modifed       : When      | Who       | What
***********************************************************************************/

#include "ServantGloable.h"
#include "MasterConnector.h"
#include "MessageHub.h"
#include "MRT.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace MRT;
using namespace NS_SERVANT;

int main( int argc , char* argv[] )
{
    Protocal::MessageHub::Instance()->AddAllHandlers();

    //std::string  ip   = string( argv[ 1 ] );
    //std::sstream portStream;
    //portStream << string( argv[2] );
    //int prot;
    //portStream >> prot;

    // check input parameters here

    while(true)
    {
        std::cout << "try connect" << std::endl;

        //Maraton::Instance()->Regist( make_uptr( MasterConnector , ip , port ) );
        Maraton::Instance()->Regist( make_uptr( MasterConnector , "10.0.0.219" , 90 ) );
        Maraton::Instance()->Run();
    }

    return 0;
}
