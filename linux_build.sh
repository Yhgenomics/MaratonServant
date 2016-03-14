#!/bin/sh
rm -rf cmakebuild
CMaker project:maraton-servant compiler:clang++ head:*.h src:*.cpp,*.c,*.cc,*.hpp lib:/usr/local/lib/libprotobuf.a,./lib/libmaraton.a,./lib/libuv.a
cd cmakebuild
cmake ./
make -j 5
