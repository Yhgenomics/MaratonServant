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
* Description   : Gloable marco and tpye-defines.
* Creator       : Ke Yang(keyang@yhgenomics.com)
* Date          : 2016/3/7
* Modifed       : When      | Who       | What
***********************************************************************************/
#ifndef SERVANT_GLOABLE_H_
#define SERVANT_GLOABLE_H_

#include <functional>
#include <string>

#define NS_SERVANT       MaratonServant
#define NS_SERVANT_BEGIN namespace NS_SERVANT {
#define NS_SERVANT_END }

NS_SERVANT_BEGIN
using std::function;
using std::string;

typedef function<void( const int& )>                     ExitCodeHandler;

typedef function<void( const string& )>                  ExceptionHandler;
typedef function<void( const string& , const string& )>  LogHandler;
NS_SERVANT_END

#endif // !SERVANT_GLOABLE_H_