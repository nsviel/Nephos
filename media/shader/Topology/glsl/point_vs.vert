#version 450
#extension GL_EXT_debug_printf : enable

//Input
layout(location = 0) in vec3 in_xyz;
layout(location = 1) in vec3 in_rgb;

//Ouput
layout(location = 0) out vec3 frag_rgb;

//Uniform
layout(binding = 0) uniform MVP{
  mat4 model;
  mat4 view;
  mat4 projection;
} uniform_mvp;
layout(binding = 1) uniform SIZE{float value;} uniform_size;


void main(){
  //---------------------------

  gl_Position = uniform_mvp.projection * uniform_mvp.view * uniform_mvp.model * vec4(in_xyz, 1.0);
  gl_PointSize = uniform_size.value;
  frag_rgb = in_rgb;

  //---------------------------
}
