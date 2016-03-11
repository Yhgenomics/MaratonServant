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
* Description   : Code book
.
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/3/2
* Modifed       : When      | Who       | What
***********************************************************************************/

#include "WorkManager.h"
#include "ServantGloable.h"
#include "MRT.h"
#include <vector>
#include <string>
#include <functional>
#include <tuple>

NS_SERVANT_BEGIN
using std::vector;
using std::string;
using std::tuple;

class ParameterPattern :public MRT::Singleton<ParameterPattern>
{
    typedef std::function<string()> ReplaceDelegate;
public:
    ParameterPattern()
    {
        /*code_book_.push_back( tuple<string , ReplaceDelegate>
                              ( "$taskid$" ,
                              WorkManager::Instance()->TaskID ) );

        code_book_.push_back( tuple<string , ReplaceDelegate>
                              ( "$pipelineid$" ,
                              WorkManager::Instance()->PipelineID ) );

        code_book_.push_back( tuple<string , ReplaceDelegate>
                              ( "$pipeid$" ,
                              nullptr ) );

        code_book_.push_back( tuple<string , ReplaceDelegate>
                              ( "$core$" ,
                              WorkManager::Instance()->Core ) );

        code_book_.push_back( tuple<string , ReplaceDelegate>
                              ( "$memory$" ,
                              WorkManager::Instance()->Memory ) );*/
    }

    bool Replace( string& str )
    {
        for ( auto item : code_book_ )
        {
            while ( str.find( std::get<0>( item ) ) != string::npos )
            {
                if ( nullptr == std::get<1>( item ) )
                {
                    // not bind yet
                    return false;
                }
                str.replace( str.find( std::get<0>( item ) ) , std::get<0>( item ).size() , std::get<1>( item )( ) );
            }
        }
        return true;
    }

    vector<tuple<string , ReplaceDelegate >> code_book_;
private:
    friend MRT::Singleton<ParameterPattern>;
};
NS_SERVANT_END