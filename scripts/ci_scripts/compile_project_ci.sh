#!/bin/bash
cd /builds/marcinwozniak0/RemoteControlVehicle/CMake
mkdir build
git clone -b v1.25.0 https://github.com/grpc/grpc
cd grpc
git submodule update --init
cd ../build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
make -j8
