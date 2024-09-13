#version 450

//Input
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_color;
layout(location = 2) in vec2 in_uv;

//Ouput
layout(location = 0) out vec3 frag_color;
layout(location = 1) out vec2 frag_uv;

//Uniform
layout(binding = 0) uniform MVP{
    mat4 mvp;
}ubo;


void main(){
  //---------------------------

  gl_Position = ubo.mvp * vec4(in_position, 1.0);
  frag_color = in_color;

  //---------------------------
}
