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
//size_t DockerHelper::Pull( const string& dest ,
//                           const string& image )
//size_t DockerHelper::Pull()
//{
//    WebClient myWebClient;
//    myWebClient.Post( GetPullString( current_dest_ , current_image_ ) ,
//                      kEmptyString ,
//                      [] ( uptr<HTTPResponse> response )
//                      {
//                          Logger::Log( "image pulled" );
//                      }
//    );
//
//    return 0;
//}

// Create one docker container
// @dest        : The docker daemon such as http://127.0.0.1:1234
// @image       : The docker image's name
// @binds       : The path binds from local path to docker path
// @environment : The variables and their values in container
// @note        : The container's ID is in the response message. 
//size_t DockerHelper::Create( const string &dest ,
//                             const string &image ,
//                             const vector< string > &binds ,
//                             const vector< string > &environment )
size_t DockerHelper::Create()
{
    Logger::Log("Docker creaste begin");
    json postJson;
    json hostConfig;

    postJson   [ kImageKey      ] = current_image_;
    postJson   [ kEvironmentKey ] = current_environment_;
    hostConfig [ kBindsKey      ] = current_binds_;
    postJson   [ kHostKey       ] = hostConfig;

    /*bool nextMove                 = is_run_mode_;*/

    WebClient myWebClient;
    myWebClient.Header( kDockerHeaderKey , kDockerHeaderValue );
    myWebClient.Post( GetCreateString( current_dest_ ) ,
                      postJson.dump() ,
                      //[ nextMove , dest , this ] ( uptr<HTTPResponse> response )
                      [ this ] ( uptr<HTTPResponse> response )
                      {
                          Logger::Log("Docker create end");
                          if( nullptr == response->Content() )
                          {
                              Logger::Log( "Response Content is NULL!Why!" );
                          }


                          string  rawJson     = string( response->Content()->Data() ,
                                                        response->Content()->Size() );
                      
                          auto    oneResponse = json::parse( rawJson );
                          //string  containerID;
                      
                          if ( oneResponse.find( kContainerIDKey ) != oneResponse.end() )
                          {
                             /* containerID                    = oneResponse[ kContainerIDKey ].get<string>();
                              contianer_list_[ containerID ] = "created";*/
                              current_container_                    = oneResponse[ kContainerIDKey ].get<string>();
                              contianer_list_[ current_container_ ] = "created";
                          }
                      
                          if ( is_run_mode_ )
                          {
                             Start();
                          }
                      }
    );

    return 0;
}

// Start a docker container
// @dest        : The docker daemon such as http://127.0.0.1:1234
// @containerID : The ID of a container
// @note        : container ID is given at the response message for Creating
//size_t DockerHelper::Start( const string &dest , 
//                            const string &containerID )
size_t DockerHelper::Start()
{ 
    Logger::Log("Docker start begin");
   /* bool nextMove                         = is_run_mode_;*/
    contianer_list_[ current_container_ ] = "started";

    WebClient myWebClient;
    myWebClient.Post( GetStartString( current_dest_ , current_container_ ) ,
                      kEmptyString ,
                      [  this ] ( uptr<MRT::HTTPResponse> response )
                      {
                          Logger::Log("Docker start end");
                          contianer_list_[ current_container_ ] = "start OK";

                          if ( is_run_mode_ )
                          {
                              Wait();
                          }
                      }
    );

    return 0;
}

// Wait a docker container's exit code
// @dest        : The docker daemon such as http://127.0.0.1:1234
// @containerID : The ID of a container
//size_t DockerHelper::Wait( const string &dest , 
//                           const string &containerID )
size_t DockerHelper::Wait()
{
    Logger::Log("Docker wait begin");
    //bool nextMove                  = is_run_mode_;
    contianer_list_[ current_container_ ] = "waiting";

    WebClient myWebClient;
    myWebClient.Post( GetWaitString( current_dest_ , current_container_ ) ,
                      kEmptyString ,
                      //[ dest , containerID , nextMove , this ] ( uptr<MRT::HTTPResponse> response )
                      [ this ]( uptr<MRT::HTTPResponse> response )
                      {
                          Logger::Log("Docker wait end");
                          
                          if( nullptr == response->Content() )
                          {
                              Logger::Log( "Response Content is NULL!Why!" );
                          }

                          string  rawJson                = string( response->Content()->Data() ,
                                                                   response->Content()->Size() );
                          auto    oneResult              = json::parse( rawJson );
                          //int     exit_code              = oneResult[ kExitCodeKey ].get<int>();
                          exit_code_                     = oneResult[ kExitCodeKey ].get<int>();
                          contianer_list_[ current_container_ ] = "exit";
                      
                          Logger::Log("Pipe in [ % ] exit with : %", current_container_ , rawJson);
                      
                          if ( nullptr != exit_code_delegate_ )
                          {
                             //exit_code_delegate_( exit_code );
                              exit_code_delegate_( exit_code_ );
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
                          const vector< string > &environment )
{
    Logger::Log("Docker Run begin");
    is_run_mode_         = true;
    current_dest_.clear();
    current_image_.clear();
    current_binds_.clear();
    current_environment_.clear();

    current_dest_        = GetCopiedString(dest);
    current_image_       = GetCopiedString(image);
    for(auto item : binds)
    {
        current_binds_.push_back( GetCopiedString(item) );
    }
    //current_binds_       = binds;
    for(auto item: environment)
    {
        current_environment_.push_back( GetCopiedString( item ) );
    }
    //current_environment_ = environment;
    
    current_container_   = "";
    exit_code_           = ErrorCode::kDefaultExit;

    WebClient myWebClient;
    myWebClient.Post( GetPullString( current_dest_ , current_image_ ) ,
                      kEmptyString ,
                      [ /*dest , image , binds , environment , */this ] ( uptr<HTTPResponse> response )
                      {
                          Logger::Log("Docker pull end");
                          //Create( current_dest_ , current_image_ , current_binds_ , current_environment_ );
                          Create();
                      }
    );
    
    return 0;
}
NS_SERVANT_END
