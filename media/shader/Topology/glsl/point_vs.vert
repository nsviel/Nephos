#version 450
#extension GL_EXT_debug_printf : enable

//Input
layout(location = 0) in vec3 in_xyz;
layout(location = 1) in vec3 in_rgb;

//Ouput
layout(location = 0) out vec3 frag_xyz;
layout(location = 1) out vec3 frag_rgb;

//Uniform
layout(binding = 0) uniform MVP{mat4 value;} uniform_mvp;
layout(binding = 1) uniform SIZE{float value;} uniform_size;


void main(){
  //---------------------------

  gl_Position = uniform_mvp.value * vec4(in_xyz, 1.0);
  gl_PointSize = 5;//uniform_size.value;
  frag_rgb = in_rgb;

  //---------------------------
}
