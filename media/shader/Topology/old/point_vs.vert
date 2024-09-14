#version 450
#extension GL_EXT_debug_printf : enable

//Input
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_color;

//Ouput
layout(location = 0) out vec3 frag_position;
layout(location = 1) out vec3 frag_color;

//Uniform
layout(binding = 0) uniform mat4 mvp;
layout(binding = 1) uniform float point_size;


void main(){
  //---------------------------

  // Apply MVP transformation to the vertex position
  gl_Position = mvp * vec4(in_position, 1.0);

  // Set point size for rendering points
  gl_PointSize = point_size;

  // Pass color and position to fragment shader
  frag_color = in_color;
  //frag_position = in_position;

  //---------------------------
}
