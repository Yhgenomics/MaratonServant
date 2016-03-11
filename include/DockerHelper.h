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
* Description   : Handler with Docker Daemon.
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/3/7
* Modifed       : When      | Who       | What
***********************************************************************************/

#ifndef DOCKERHELPER_H_
#define DOCKERHELPER_H_

#include "MRT.h"
#include "ServantGloable.h"
#include <string>

using namespace std;
using namespace MRT;

NS_SERVANT_BEGIN

class DockerHelper :public Singleton<DockerHelper>
{
public:
    // Docker Controler 
    virtual size_t    Search() { return 0; };
    virtual size_t    Pull  ( const string &dest , const string &source );

    virtual size_t    Create( const string           &dest  ,
                              const string           &image ,
                              const vector< string > &binds ,
                              const vector< string > &environment );

    virtual size_t    Start ( const string &dest , const string &containerID );

    virtual size_t    Wait  ( const string &dest , const string &containerID );

    virtual size_t    Run   ( const string &dest ,
                              const string &image ,
                              const vector< string > &binds ,
                              const vector< string >  &environment );

    virtual size_t    Stop  () { return 0; };

    virtual size_t    Watch ( const string &dest , const string &containerID );

    // Handler Binder
    virtual void      BindExitCodeHandler( ExitCodeHandler  one_handler )
    {
        exit_code_delegate_ = one_handler;
    }

    virtual void      BindExceptionHandler( ExceptionHandler one_handler )
    {
        exception_delegate_ = one_handler;
    }

    virtual void      BindLogHandler( LogHandler       one_handler )
    {
        log_delegate_       = one_handler;
    }

    bool              is_run_mode_          = false;
    //pull_handler      pull_result          = nullptr;
    ExitCodeHandler   exit_code_delegate_   = nullptr;
    ExceptionHandler  exception_delegate_   = nullptr;
    LogHandler        log_delegate_         = nullptr;

private:

    const string      kDockerHeader        = "Content-Type: application/json";
    const string      kListContianers      = "/containers/json";
    const string      kCreateContianer     = "/containers/create";
    const string      kStartContianer      = "/containers/(id)/start";
    const string      kCreateImage         = "/images/create";
    const string      kParamsToken         = "?";
    const string      kFromSource          = "fromSrc=";
    const string      kFromImage           = "fromImage=";

    map<string,string> contianer_list_;
    friend Singleton<DockerHelper>;
};

NS_SERVANT_END

#endif // !I_DOCKERHELPER_H_
