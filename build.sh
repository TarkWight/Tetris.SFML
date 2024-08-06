#!/bin/bash

# build.sh

BUILD_DIR="Build"
GENERATOR="Unix Makefiles"

if [ ! -d "$BUILD_DIR" ]; then
  mkdir $BUILD_DIR
fi

cd $BUILD_DIR

cmake -G "$GENERATOR" ..
cmake --build .

cd ..

echo "Build completed. The project is located in the $BUILD_DIR directory."
