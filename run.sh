#!/bin/bash
if [ -d "out" ]
then
    cd out/
else 
    mkdir out
fi

cmake ..
cmake --build .
./OpenGLSetup