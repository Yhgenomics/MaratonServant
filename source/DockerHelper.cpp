#include "DockerHelper.h"

#include <string>
#include <iostream>
#include <vector>
#include "json.hpp"

NS_SERVANT_BEGIN

using std::string;
using json = nlohmann::json;
using std::cout;
using std::endl;

size_t DockerHelper::Pull( const string &dest ,
                           const string& source )
{
    WebClient myWebClient;
    myWebClient.Post( dest
                      + kCreateImage
                      + kParamsToken
                      + kFromImage
                      + source ,
                      "" ,
                      [] ( uptr<HTTPResponse> response )
                      {
                          cout << "image pulled" << endl;
                      }
    );

    return 0;
}


size_t DockerHelper::Create( const string &dest ,
                             const string &image ,
                             const vector< string > &binds ,
                             const vector< string > &environment )
{
    json postJson;
    json hostConfig;

    postJson   [ "Image"      ] = image;
    postJson   [ "Env"        ] = environment;
    hostConfig [ "Binds"      ] = binds;
    postJson   [ "HostConfig" ] = hostConfig;

    bool nextMove               = is_run_mode_;

    WebClient myWebClient;
    myWebClient.Header( "Content-Type" , "application/json" );
    myWebClient.Post( dest
                      + kCreateContianer ,
                      postJson.dump() ,
                      [ nextMove , dest , this ] ( uptr<HTTPResponse> response )
    {
        string  rawJson     = string( response->Content()->Data() ,
                                      response->Content()->Size() );

        auto    oneResponse = json::parse( rawJson );
        string  containerID;

        if ( oneResponse.find( "Id" ) != oneResponse.end() )
        {
            containerID                    = oneResponse[ "Id" ].get<string>();
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

size_t DockerHelper::Start( const string &dest , 
                            const string &containerID )
{ 
    bool nextMove                  = is_run_mode_;
    contianer_list_[ containerID ] = "started";

    WebClient myWebClient;
    myWebClient.Post( dest
                      + "/containers/"
                      + containerID
                      + "/start" ,
                      "" ,
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

size_t DockerHelper::Wait( const string &dest , 
                           const string &containerID )
{
    bool nextMove                  = is_run_mode_;
    contianer_list_[ containerID ] = "waiting";

    WebClient myWebClient;
    myWebClient.Post( dest
                      + "/containers/"
                      + containerID
                      + "/wait" ,
                      "" ,
                      [ dest , containerID , nextMove , this ] ( uptr<MRT::HTTPResponse> response )
                      {
                          string  rawJson                = string( response->Content()->Data() ,
                                                                   response->Content()->Size() );
                          auto    oneResult              = json::parse( rawJson );
                          int     exit_code              = oneResult[ "StatusCode" ].get<int>();
                          contianer_list_[ containerID ] = "exit";
                      
                          cout << rawJson << endl;
                      
                          if ( nullptr != exit_code_delegate_ )
                          {
                              exit_code_delegate_( exit_code );
                          }
                      }
    );
    return 0;
}

size_t DockerHelper::Watch( const string &dest , 
                            const string &containerID )
{
    return 0;
}

size_t DockerHelper::Run( const string &dest ,
                          const string &image ,
                          const vector< string > &binds ,
                          const vector< string >  &environment )
{
    is_run_mode_ = true;

    WebClient myWebClient;
    myWebClient.Post( dest
                      + kCreateImage
                      + kParamsToken
                      + kFromImage
                      + image ,
                      "" ,
                      [ dest , image , binds , environment , this ] ( uptr<HTTPResponse> response )
                      {
                          cout << "image pulled" << endl;
                          Create( dest , image , binds , environment );
                      }
    );
    
    return 0;
}
NS_SERVANT_END
