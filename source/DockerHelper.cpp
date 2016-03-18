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

#include "DockerHelper.h"
#include "json.hpp"
#include <string>
#include <iostream>
#include <vector>

NS_SERVANT_BEGIN

using std::string;
using json = nlohmann::json;
using std::cout;
using std::endl;
using MRT::WebClient;
using MRT::HTTPResponse;

// Pull one docker image from registry 
// @dest    : The docker daemon such as http://127.0.0.1:1234
// @image   : The docker image's name 
size_t DockerHelper::Pull( const string& dest ,
                           const string& image )
{
    WebClient myWebClient;
    myWebClient.Post( GetPullString( dest , image ) ,
                      kEmptyString ,
                      [] ( uptr<HTTPResponse> response )
                      {
                          Logger::Log("image pulled");
                      }
    );

    return 0;
}

// Create one docker container
// @dest        : The docker daemon such as http://127.0.0.1:1234
// @image       : The docker image's name
// @binds       : The path binds from local path to docker path
// @environment : The variables and their values in container
// @note        : The container's ID is in the response message. 
size_t DockerHelper::Create( const string &dest ,
                             const string &image ,
                             const vector< string > &binds ,
                             const vector< string > &environment )
{
    json postJson;
    json hostConfig;

    postJson   [ kImageKey      ] = image;
    postJson   [ kEvironmentKey ] = environment;
    hostConfig [ kBindsKey      ] = binds;
    postJson   [ kHostKey       ] = hostConfig;

    bool nextMove                 = is_run_mode_;

    WebClient myWebClient;
    myWebClient.Header( kDockerHeaderKey , kDockerHeaderValue );
    myWebClient.Post( GetCreateString(dest) ,
                      postJson.dump() ,
                      [ nextMove , dest , this ] ( uptr<HTTPResponse> response )
                      {
                          string  rawJson     = string( response->Content()->Data() ,
                                                        response->Content()->Size() );
                      
                          auto    oneResponse = json::parse( rawJson );
                          string  containerID;
                      
                          if ( oneResponse.find( kContainerIDKey ) != oneResponse.end() )
                          {
                              containerID                    = oneResponse[ kContainerIDKey ].get<string>();
                              contianer_list_[ containerID ] = "created";
                          }
                      
                          if ( nextMove )
                          {
                             Start( dest , containerID );
                          }
                      }
    );

    return 0;
}

// Start a docker container
// @dest        : The docker daemon such as http://127.0.0.1:1234
// @containerID : The ID of a container
// @note        : container ID is given at the response message for Creating
size_t DockerHelper::Start( const string &dest , 
                            const string &containerID )
{ 
    bool nextMove                  = is_run_mode_;
    contianer_list_[ containerID ] = "started";

    WebClient myWebClient;
    myWebClient.Post( GetStartString( dest , containerID ) ,
                      kEmptyString ,
                      [ dest , containerID , nextMove , this ] ( uptr<MRT::HTTPResponse> response )
                      {
                          contianer_list_[ containerID ] = "start OK";

                          if ( nextMove )
                          {
                              Wait( dest , containerID );
                          }
                      }
    );

    return 0;
}

// Wait a docker container's exit code
// @dest        : The docker daemon such as http://127.0.0.1:1234
// @containerID : The ID of a container
size_t DockerHelper::Wait( const string &dest , 
                           const string &containerID )
{
    bool nextMove                  = is_run_mode_;
    contianer_list_[ containerID ] = "waiting";

    WebClient myWebClient;
    myWebClient.Post( GetWaitString( dest , containerID ) ,
                      kEmptyString ,
                      [ dest , containerID , nextMove , this ] ( uptr<MRT::HTTPResponse> response )
                      {
                          string  rawJson                = string( response->Content()->Data() ,
                                                                   response->Content()->Size() );
                          auto    oneResult              = json::parse( rawJson );
                          int     exit_code              = oneResult[ kExitCodeKey ].get<int>();
                          contianer_list_[ containerID ] = "exit";
                      
                          Logger::Log("Wait exit : %", rawJson);
                      
                          if ( nullptr != exit_code_delegate_ )
                          {
                              exit_code_delegate_( exit_code );
                          }
                      }
    );

    return 0;
}

// Run equals to Pull => Create => Start => Wait
// @dest        : The docker daemon such as http://127.0.0.1:1234
// @image       : The docker image's name
// @binds       : The path binds from local path to docker path
// @environment : The variables and their values in container
size_t DockerHelper::Run( const string &dest ,
                          const string &image ,
                          const vector< string > &binds ,
                          const vector< string >  &environment )
{
    is_run_mode_ = true;

    WebClient myWebClient;
    myWebClient.Post( GetPullString( dest , image ) ,
                      kEmptyString ,
                      [ dest , image , binds , environment , this ] ( uptr<HTTPResponse> response )
                      {
                          Create( dest , image , binds , environment );
                      }
    );
    
    return 0;
}
NS_SERVANT_END
