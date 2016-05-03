#!/bin/sh
rm -rf cmakebuild
CMaker project:maraton-servant compiler:clang++ head:*.h src:*.cpp,*.c,*.cc,*.hpp lib:/usr/local/lib/libprotobuf.a,./lib/libMaratonFramework.a,./lib/libuv.a debug:true
cd cmakebuild
cmake ./
make -j 5
cp maraton-servant ../
