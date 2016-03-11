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
* Description   : Connect to Master.
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/3/7
* Modifed       : When      | Who       | What
***********************************************************************************/

#ifndef MASTER_CONNECTOR_H_
#define MASTER_CONNECTOR_H_

#include "MRT.h"
using namespace MRT;

class MasterConnector : public Connector
{
public:
    MasterConnector( std::string addr , int port ) : Connector( addr , port ) {};
    ~MasterConnector(){
    //Maraton::Instance()->Regist( make_uptr( MasterConnector , "10.0.0.219" , 90 ) );
    }

    virtual Session *   CreateSession  () override;
    virtual void        OnSessionOpen  ( Session * session ) override;
    virtual void        OnSessionClose ( Session * session ) override;
};

#endif //!MASTER_CONNECTOR_H_