#version 450
#extension GL_EXT_debug_printf : enable

//Input
layout(location = 0) in vec3 in_xyz;
layout(location = 1) in vec3 in_rgb;

//Ouput
layout(location = 0) out vec3 frag_xyz;
layout(location = 1) out vec3 frag_rgb;

//Uniform
layout(binding = 0) uniform mat4 mvp;
layout(binding = 1) uniform float point_size;


void main(){
  //---------------------------

  // Apply MVP transformation to the vertex position
  gl_Position = mvp * vec4(in_xyz, 1.0);

  // Set point size for rendering points
  gl_PointSize = point_size;

  // Pass color and position to fragment shader
  frag_rgb = in_rgb;
  //frag_xyz = in_xyz;

  //---------------------------
}
