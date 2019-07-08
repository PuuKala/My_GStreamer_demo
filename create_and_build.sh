#!/bin/bash
echo -- Creating build folder --
mkdir -p build
cd build

echo -- Creating project files --
cmake -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" ..

echo -- Building --
cmake --build . -- -j3

echo -- Done. --
cd ..
exit 0