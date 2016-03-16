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

using MRT::Connector;
using MRT::Session;

// @Description : Connector to a Master session given by IP addresss and port.         
// @Example     : Set first, and work after the Maraton be un.
//                while( true )
//                {
//                    ...
//                    Maraton::Instance()->Regist( make_uptr( MasterConnector , ip , port ) );
//                    ...
//                    Maraton::Instance()->Run();
//                }
// @Note        : As a Connector, three interfaces must be override is the CreatSession
//                OnSessionOpen and the OnSessionClose.
//                Do not use a smart pointer on the session as a constrain from
//                the Maraton framewrok. 
class MasterConnector : public Connector
{
public:

    // Constructor
    MasterConnector( const std::string& addr , const int& port ) : Connector( addr , port ) {};
    
    // Desctrucotr
    ~MasterConnector(){}

    // Callback when the business session is connected.
    virtual Session *   CreateSession  () override;
    
    // Callback when the business session opening.
    // @param   : session is the pointer to the session and can be cast to 
    //            the pointer to MasterSession by static cast.
    virtual void        OnSessionOpen  ( Session * session ) override;
    
    // Callback when the business session closing.
    // @param   : session is the pointer to the session and can be cast to 
    //            the pointer to MasterSession by static cast. 
    virtual void        OnSessionClose ( Session * session ) override;
};

#endif //!MASTER_CONNECTOR_H_