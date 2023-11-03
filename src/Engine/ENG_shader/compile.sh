#!/bin/bash

../extern/shader/glslc ../src/Engine/ENG_shader/$1/glsl/$2.vert -o ../src/Engine/ENG_shader/$1/spir/$2.spv
../extern/shader/glslc ../src/Engine/ENG_shader/$1/glsl/$3.frag -o ../src/Engine/ENG_shader/$1/spir/$3.spv
