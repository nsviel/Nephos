#version 450

//Input
layout(location = 0) in vec3 in_xyz;
layout(location = 1) in vec3 in_rgb;
layout(location = 2) in vec2 in_uv;

//Ouput
layout(location = 0) out vec3 frag_rgb;
layout(location = 1) out vec2 frag_uv;

//Uniform
layout(binding = 0) uniform MVP{
  mat4 model;
  mat4 view;
  mat4 projection;
} uniform_mvp;


void main(){
  //---------------------------

  gl_Position = uniform_mvp.projection * uniform_mvp.view * uniform_mvp.model * vec4(in_xyz, 1.0);
  frag_rgb = in_rgb;
  frag_uv = in_uv;

  //---------------------------
}
