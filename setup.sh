#!/bin/bash
echo "Initializing the project..."
git submodule init
git submodule update
./run.sh
