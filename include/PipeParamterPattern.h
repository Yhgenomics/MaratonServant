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

#ifndef PIPE_PARAMETER_PATTERN_H_
#define PIPE_PARAMETER_PATTERN_H_

#include "PipePatternHandlerSet.h"
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

// @Description : Pipe's parameter may contains some pattern from upper layer
//                for description local environments or values. Such Marcos
//                must be translated to the right string that a docker 
//                container can use.
class ParameterPattern :public MRT::Singleton<ParameterPattern>
{
    
    // delegate to replace a string pattern to the right value
    typedef std::function<string()> ReplaceDelegate;

public:

    ParameterPattern()
    {
        code_book_.push_back( tuple<string , ReplaceDelegate>
                              ( "$taskid$" ,
                              PipeParameterHandler::TaskID ) );

        code_book_.push_back( tuple<string , ReplaceDelegate>
                              ( "$pipelineid$" ,
                              PipeParameterHandler::PipelineID ) );

        code_book_.push_back( tuple<string , ReplaceDelegate>
                              ( "$pipeid$" ,
                              nullptr ) );

        code_book_.push_back( tuple<string , ReplaceDelegate>
                              ( "$core$" ,
                              PipeParameterHandler::Core ) );

        code_book_.push_back( tuple<string , ReplaceDelegate>
                              ( "$memory$" ,
                              PipeParameterHandler::Memory ) );
    }

    // Replace any patterns in a string by the rules in code_book_
    bool Replace( string& str )
    {
        for ( const auto& item : code_book_ )
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

    // Rules on pattern string and the delegate for it
    vector<tuple<string , ReplaceDelegate >> code_book_;

private:
    friend MRT::Singleton<ParameterPattern>;

};

NS_SERVANT_END

#endif // !PIPE_PARAMETER_PATTERN_H_