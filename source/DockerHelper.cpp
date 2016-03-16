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
using MRT::WebClient;
using MRT::HTTPResponse;

size_t DockerHelper::Pull( const string& dest ,
                           const string& image )
{
    WebClient myWebClient;
    myWebClient.Post( GetPullString( dest , image ) ,
                      kEmptyString ,
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
                      
                          cout << rawJson << endl;
                      
                          if ( nullptr != exit_code_delegate_ )
                          {
                              exit_code_delegate_( exit_code );
                          }
                      }
    );
    return 0;
}

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
