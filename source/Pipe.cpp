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
#include "PipeParamterPattern.h"

NS_SERVANT_BEGIN

void Pipe::AddEnvironment( string key , string value )
{
    environments_.push_back( key + "=" + value );
}

void Pipe::AddEnvironment( string pattern )
{
   /* ParameterPattern::Instance()->Replace( pattern );*/

   string temp="$taskid$";
   if ( pattern.find( temp ) != string::npos )
       pattern.replace( pattern.find( temp ) ,
                        temp.size() ,
                        WorkManager::Instance()->TaskID() );

   temp="$core$";
   if ( pattern.find( temp ) != string::npos )
       pattern.replace( pattern.find( temp ) ,
                        temp.size() ,
                        WorkManager::Instance()->Core() );

   environments_.push_back( pattern );


}
NS_SERVANT_END
