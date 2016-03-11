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
* Description   : Serial pipes make a pipeline.
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/3/8
* Modifed       : When      | Who       | What
***********************************************************************************/

#ifndef PIPELINE_H_
#define PIPELINE_H_

#include "ServantGloable.h"
#include "Pipe.h"
#include "MessageTaskDeliver.pb.h"
#include <vector>
#include <string>
#include <memory>

NS_SERVANT_BEGIN

class Pipeline:public Singleton<Pipeline>
{
public:

    void  AddPipe( uptr<Pipe> pipe )
    {
        pipe_list_.push_back( std::move( pipe ) );
    }
    
    void AddPipe()
    {

    }

    void ParseFromMessage( uptr<MessageTaskDeliver> orignalMessage );

    void Run()
    {
        RunNext(0);
    }

    void RunNext(const int& lastExitCode)
    {
        if(lastExitCode != 0)
            OnException(lastExitCode);

        GetNextPipe();

        if( pipe_list_.size() == 0 )
            OnFinish();
        else
            {
            auto currentPipe = std::move(pipe_list_[0]);
            pipe_list_.erase(pipe_list_.begin());
            currentPipe->Run();
            }
    }

    void GetNextPipe();

    void OnFinish()
    {
        std::cout << "pipeline finished" << endl;
    }

    void OnException(const int& lastExitCode)
    {
        std::cout << "Exception happended code "<< lastExitCode << endl;
    }

private:
    vector<uptr<Pipe>>  pipe_list_;
    friend Singleton<Pipeline>;
};


NS_SERVANT_END

#endif // ��PIPELINE_H_