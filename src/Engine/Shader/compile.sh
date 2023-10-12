#!/bin/bash

../extern/shader/glslc ../src/Engine/Shader/$1/glsl/$2.vert -o ../src/Engine/Shader/$1/spir/$2.spv
../extern/shader/glslc ../src/Engine/Shader/$1/glsl/$3.frag -o ../src/Engine/Shader/$1/spir/$3.spv
